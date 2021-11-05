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
                // TODO: If we are in a pipe (check `is_pipe`), bail out (goto)
                //       to the `next_input` label to ignore the incorrect
                //       command. The `cd` command does not make much sense in
                //       our shell in a pipe sequence.
                // ?

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
                // TODO: If we are in a pipe (check `is_pipe`), bail out (goto)
                //       to the `next_input` label to ignore the incorrect
                //       command. The `exit` command does not make much sense in
                //       our shell in a pipe sequence.
                // ?

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
            // TODO: If `stdin_file` is present and we are in a pipe (check
            //       `is_pipe`) and we are not the first pipe member (check
            //       `pipe_member_index`), go to the `next_input` label to
            //       ignore the incorrect command. The only program in a pipe
            //       that can use STDIN redirection from a file should be the
            //       first program in a pipeline.
            // ?

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
            // TODO: If `stdout_file` is present and we are in a pipe (check
            //       `is_pipe`) and we are not the last pipe member (check
            //       `pipe_member_index` and `pipe_member_count`), go to the
            //       `next_input` label to ignore the incorrect command. The
            //       only program in a pipe that can use STDOUT redirection to
            //       a file should be the last program in a pipeline.
            // ?

            int stdout_descriptor =
                !stdout_file ?
                    -1 : creat(
                            stdout_file,
                            Standard_Output_File_Mode
                        );

            if (is_pipe) {
                if (pipe_member_index != pipe_member_count - 1) {
                    int pipe_descriptors[2];
                    // TODO: Create the pipe with the `pipe` system call. Such a
                    //       call should create two file descriptors in
                    //       `pipe_descriptors` where `pipe_descriptors[0]` is
                    //       the STDIN end of the new pipe for the consumer
                    //       process (the second process) and `pipe_descriptors[1]`
                    //       is the STDOUT end of the producer process (the
                    //       first process).
                    // ?

                    pipe_stdin_descriptors[pipe_member_index] =
                        pipe_descriptors[0];
                    pipe_stdout_descriptors[pipe_member_index] =
                        pipe_descriptors[1];
                }
            }

            int pid = fork();
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
                        // TODO: For every process that is not the first one,
                        //       STDIN connected to the terminal should be
                        //       replaced (`dup2`) with the pipe's STDIN stream
                        //       created in the PREVIOUS iteration. Select the
                        //       correct index to the `pipe_stdin_descriptors`
                        //       array here for `dup2` to replace the file
                        //       descriptor 0 of STDIN.
                        // ?

                        // TODO: You can close the pipe's file descriptors after
                        //       duplicating them onto the standard streams. You
                        //       can also close the unnecessary descriptors.
                        //       Remember only to close descriptors from the
                        //       PREVIOUS iteration here. Close both things in
                        //       `pipe_stdin_descriptors` and
                        //       `pipe_stdout_descriptors` for the correct
                        //       index.
                        // ?

                    }

                    if (pipe_member_index != pipe_member_count - 1) {
                        // TODO: For every process that is not the last one,
                        //       STDOUT connected to the terminal should be
                        //       replaced (`dup2`) with the pipe's STDOUT stream
                        //       created in the CURRENT iteration. Select the
                        //       correct index to the `pipe_stdout_descriptors`
                        //       array here for `dup2` to replace the file
                        //       descriptor 1 of STDOUT.
                        // ?

                        // TODO: You can close the pipe's file descriptors after
                        //       duplicating them onto the standard streams. You
                        //       can also close the unnecessary descriptors.
                        //       Remember only to close descriptors from the
                        //       CURRENT iteration here. Close both things in
                        //       `pipe_stdin_descriptors` and
                        //       `pipe_stdout_descriptors` for the correct
                        //       index.
                        // ?

                    }
                }

                execve(executable, arguments, envp);
                exit(-1);
            } else if (pid > 0) {
                pids[pipe_member_index] = pid;

                if (is_pipe) {
                    if (pipe_member_index > 0) {
                        // TODO: In the parent process, you should also close
                        //       all the pipe descriptors that have already been
                        //       used. It means, close `pipe_stdin_descriptors`
                        //       and `pipe_stdout_descriptors` from the previous
                        //       iteration, but leave the descriptors for the
                        //       current iteration still open as they will be
                        //       required by the child process in the next
                        //       iteration. For example, suppose you do not
                        //       close a file descriptor in the parent. In that
                        //       case, you may stall the pipe because some child
                        //       processes using the `dup`ped streams will never
                        //       get EOF or equivalent errors for the `read` or
                        //       `write` system calls to exit (that is how the
                        //       `yes` program exits from the infinite loop by
                        //       failing to do a `write` call).
                        // ?

                    }
                }
            } else {
                write(2, Fork_Error_Message, sizeof(Fork_Error_Message));

                goto next_input;
            }
        }

        if (is_pipe) {
            // TODO: Finish the process from the previous TODO by closing the
            //       `pipe_stdin_descriptors` and `pipe_stdout_descriptors` for
            //       the last pipe descriptors. They should be at index
            //       `pipe_member_count - 2` in `pipe_stdin_descriptors` and
            //       `pipe_stdout_descriptors` arrays.
            // ?

        }

        // TODO: Wait with the `waitpid` system call for all the child
        //       processes. You will have to call this function multiple times
        //       in a loop for all the pipe member indices for every positive
        //       process ID in the `pids` array (as we may have more than one
        //       process this time).
        // ?

next_input:;
    }

    return 0;
}
