#ifdef ISH_USE_STDLIB
    #include <unistd.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <sys/wait.h>
    #include <sys/types.h>
#endif

#include "ish_cstring_utilities.h"
#include "ish_shell_utilities.h"
#include "ish_syscalls.h"

static const unsigned long Max_Input_String_Length = 255;
static const unsigned long Max_Pipe_Member_Count   = 255;
static const unsigned long Max_Argument_Count      = 255;
static const unsigned long Max_Executable_Path_Length = 1024;

static const char Environment_Variable_Home[] = "HOME";
static const char Environment_Variable_Path[] = "PATH";

static const char Builtin_Command_CD[] = "cd";
static const char Builtin_Command_Exit[] = "exit";

static const unsigned short Standard_Input_File_Flags = 00000;
static const unsigned short Standard_Output_File_Mode = 00644;

static const char Fork_Error_Message[] = "fork failure\n";

/*
    ish
    An incomplete shell that is silent and very primitive
*/
int main(int argc, char **argv, char **envp)
{
    char *home =
        ish_get_first_environment_variable(
            Environment_Variable_Home,
            sizeof(Environment_Variable_Home),
            envp
        );
    char *paths =
        ish_get_first_environment_variable(
            Environment_Variable_Path,
            sizeof(Environment_Variable_Path),
            envp
        );

    char input[Max_Input_String_Length + 1];
    input[Max_Input_String_Length] = '\0';

    while (read(0, input, Max_Input_String_Length) >= 0) {
        ish_replace_first_character_in_cstring(
            input, '\n', '\0'
        );

        char *pipe_members[Max_Pipe_Member_Count + 1];
        pipe_members[Max_Pipe_Member_Count] = 0;
        int pids[Max_Pipe_Member_Count];
        int pipe_stdin_descriptors[Max_Pipe_Member_Count];
        int pipe_stdout_descriptors[Max_Pipe_Member_Count];

        unsigned long pipe_member_count =
            ish_build_pipe_member_array_from_input(
                input,
                pipe_members,
                Max_Pipe_Member_Count
            );
        int is_pipe =
            pipe_member_count > 1;

        for (unsigned long pipe_member_index = 0;
                 pipe_member_index < pipe_member_count;
                    ++pipe_member_index) {
            char *pipe_member =
                pipe_members[pipe_member_index];

            char *arguments[Max_Argument_Count + 1];
            arguments[Max_Argument_Count] = 0;
            unsigned long argument_count =
                ish_build_argument_array_from_input(
                    pipe_member,
                    arguments,
                    Max_Argument_Count
                );

            const char *command = arguments[0];
            if (!command) {
                continue;
            }

            if (ish_are_cstrings_equal(
                    command,
                    Builtin_Command_CD
                )) {
                // TODO: if we are not in a pipe, bail (goto) out to `next_input`.

                char *directory = argument_count == 0 ?  home : arguments[1];
                if (directory) {
                    chdir(directory);
                }

                continue;
            }

            if (ish_are_cstrings_equal(
                    command,
                    Builtin_Command_Exit
                )) {
                // TODO: if we are not in a pipe, bail out (goto) to `next_input`.

                int exit_status =
                    argument_count == 0 ?
                        0 : ish_get_integer_from_cstring(
                                arguments[1]
                            );
                exit(exit_status);

                continue;
            }

            char *executable =
                arguments[0];

            char candidate[Max_Executable_Path_Length + 1];
            candidate[Max_Executable_Path_Length] = '\0';

            #ifdef ISH_USE_STDLIB
                struct stat stat_buffer;
                struct stat *stat_result =
                    &stat_buffer;
            #else
                char stat_result[1024];
            #endif
            if (stat(executable, stat_result) != 0) {
                executable = 0;
                for (char *cursor = paths; cursor && !executable; ) {
                    char *path =
                        ish_get_token_in_cstring(
                            cursor,
                            ish_is_path_separator,
                            &cursor
                        );

                    if (path) {
                        ish_combine_path_elements(
                            path,
                            arguments[0],
                            candidate,
                            Max_Executable_Path_Length
                        );

                        if (stat(candidate, stat_result) == 0) {
                            executable =
                                candidate;
                        }
                    }
                }
            }

            if (!executable) {
                continue;
            }

            char *stdin_file =
                ish_extract_last_stdin_redirection_file(
                    arguments
                );
            // TODO: if `stdin_file` is present and we are in a pipe and we
            //       are not the first member of pipe, bail out to `next_input`.
            int stdin_descriptor =
                !stdin_file ?
                    -1 : open(
                            stdin_file,
                            Standard_Input_File_Flags
                        );

            char *stdout_file =
                ish_extract_last_stdout_redirection_file(
                    arguments
                );
            // TODO: if `stdout_file` is present and we are in a pipe and we
            //       are not the last member of pipe, bail out to `next_input`.
            int stdout_descriptor =
                !stdout_file ?
                    -1 : creat(
                            stdout_file,
                            Standard_Output_File_Mode
                        );

            if (is_pipe) {
                if (pipe_member_index != pipe_member_count - 1) {
                    int pipe_descriptors[2];
                    // TODO: create the pipe file descriptors.

                    pipe_stdin_descriptors[pipe_member_index] = pipe_descriptors[0];
                    pipe_stdout_descriptors[pipe_member_index] = pipe_descriptors[1];
                }
            }

            int pid = fork(); // ~ typedef int pid_t
            if (pid == 0) {
                if (stdin_descriptor > 0) {
                    dup2(stdin_descriptor, 0);
                    close(stdin_descriptor);
                }

                if (stdout_descriptor > 1) {
                    dup2(stdout_descriptor, 1);
                    close(stdout_descriptor);
                }

                if (is_pipe) {
                    if (pipe_member_index != 0) {
                        // TODO: dup2 pipe stdin end of the previous iteration to child's stdin.
                        // TODO: close all the pipe ends of the previous iteration in the child.
                    }

                    if (pipe_member_index != pipe_member_count - 1) {
                        // TODO: dup2 pipe stdout end of the current iteration to stdout.
                        // TODO: close all the pipe ends of the current iteration in the child.
                    }
                }

                execve(executable, arguments, envp);
                exit(-1);
            } else if (pid > 0) {
                pids[pipe_member_index] = pid;

                if (is_pipe) {
                    if (pipe_member_index > 0) {
                        // TODO: close all the pipe ends of the previous iteration
                        //       in the parent if we are not processing the
                        //       first member of the pipe.
                    }
                }
            } else {
                write(2, Fork_Error_Message, sizeof(Fork_Error_Message));

                pids[pipe_member_index] = -1;
                goto next_input;
            }
        }

        if (is_pipe) {
            // TODO: close the last pipe ends (both stdin and stdout).
        }

        // TODO: wait for all the valid child processes in the pids array.
next_input:;
    }

    return 0;
}
