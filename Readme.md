### COM 341, Operating Systems
# Project #1

![ish](http://i.imgur.com/hUwm2PG.gif)

Our infamous instructor [Sergei Rachmiroff](https://i.imgur.com/hLHngQQ.jpg) is building a hobby operating system. His system needs a shell to allow users to start their programs. Sergei has a toy shell that he wrote ten thousand years ago, but unfortunately, the shell uses the C standard library to do its job, and Sergei's hobby operating system does NOT have the C standard library ported yet. To make matters worse, the instructor is shy about his OS code and does not want to share it with others. The good news is that his OS has the same low-level system call interface as GNU/Linux, which means you can help our instructor port the shell to his OS just by ensuring his shell works on GNU/Linux without the C standard library. His OS targets most modern CPU architectures such as x86-64, AArch64, and RISC-V 64, which means without a C library, one will have to make calls to the OS for all those architectures differently. Sergei is proud of his old shell code (though he should probably not with that weird code style) and agrees to give it to you with the condition that you will also help him add a pipeline mechanism for inter-process communication to it (what a git!). Help him as much as possible, as it will determine your grades for the project.

In this work, we hope you will

* Find various ways to run multiple operating systems on a computer through virtualization technologies, emulation, and containerization.
* Understand the difference between virtualization, emulation, and containerization.
* Install an operating system on a computer at least once.
* Learn the basics of using the Unix systems through a terminal.
* Learn how a simple command line shell works.
* Learn about the concept of system calls.
* Learn about the most common system calls on Unix platforms.
* Learn how a user space application performs a system call in a low-level language.
* Learn about hidden costs associated with system calls.
* Learn why a direct use of system calls without standard libraries makes your program less portable.
* Learn to work with various sources of information such as man pages, books, the kernel source code, and disassembled code in a debugger to get the necessary information.
* Learn about fundamental I/O abstractions such as Standard Streams.
* Learn how redirection to and from files works on Unix platforms.
* Learn how piping works on Unix platforms.

## Required Tools

On your host machine, you will need a Unix shell with essential Unix command line utilities and an SSH client to connect to virtualized, emulated, and containerized systems. You may also find the `scp` program useful to transfer files between host and guest operating systems. On Windows, you can get all the necessary things by installing Git from its official [Website](https://git-scm.com). On macOS, you can get everything by installing Command Line Tools for Xcode with the `xcode-select --install` command. Finally, you may also use our lab computers. Lab machines have all the necessary software for this task.

You may also have to install [Docker Desktop](https://www.docker.com/products/docker-desktop) on your host system. The Docker Desktop installation could be pretty challenging on some operating systems. Do your best by following the official documentation on the Docker [Website](https://docs.docker.com/desktop). Even though Docker is available on our server and some lab computers, it is only available to instructors. However, we provide some workarounds for people who would like to work on lab machines or failed to install Docker successfully. Follow the Readme file from Part #1 in the `platforms/riscv64/` directory to find out more.

## Part #1

The goal of the first task is to prepare execution environments for the second and third parts of the project on various CPU architectures, such as x86-64, ARMv8, and RISC-V on a GNU/Linux operating system.

1. First, create an x86-64 GNU/Linux environment by installing the Debian distribution of GNU/Linux inside the QEMU virtualization environment. Follow the `platforms/amd64/` Readme for more info.

2. Second, create an ARMv8 GNU/Linux environment by installing the Debian distribution of GNU/Linux inside the QEMU hardware emulation environment. Follow the `platforms/arm64/` Readme for more info.

3. Finally, create a RISC-V environment by downloading a `linux/riscv64` image of the Ubuntu distribution of GNU/Linux with the help of the Docker containerization platform. You will find the Readme file from `platforms/riscv64/` directory useful, especially if you can't access Docker for some reason.

### What to Submit

1. Ensure that during the installation process of the `amd64` and `arm64` versions of Debian, you have specified your first and last name as your full name (e.g., `Dmitrii Toksaitov`). Ensure that you have also provided your `auca.space` login as a login and password. You will have to replace the underscore character in your login with a dash to continue the installation process (e.g., `toksaitov-d`, NOT `toksaitov_d`). The password should not be manipulated in any way (e.g., `toksaitov_d` should be used as a password as is).

    Incorrect data specified during the installation process of the `amd64` and `arm64` versions of Debian will give you the wrong files to submit and zero points for the part. Due to that reason, please, provide a correct full name, login, and password.

2. In your private course repository given to you by the instructor during the lecture, create the path `project-01/part-01/`.

3. Put the `/etc/shadow` file from the x86-64, ARMv8, and RISC-V environments into the `project-01/part-01/` directory under the name `<arch>-shadow`. You should get the following files there

    * `amd64-shadow`
    * `arm64-shadow`
    * `riscv64-shadow`

4. Put the output of `dmesg` from from the x86-64, ARMv8, and RISC-V environments into the `project-01/part-01/` directory under the name `<arch>-dmesg`. You should get and submit the following additional files

    * `amd64-dmesg`
    * `arm64-dmesg`
    * `riscv64-dmesg`

6. Commit and push your repository through Git. Submit a URL to the last commit on GitHub to Canvas before the deadline.

## Part #2

The goal of the second task is to implement system calls on all three platforms from part #1 in our toy shell. Refer to the Readme file in the `ish` directory for more info.

### What to Submit

1. In your private course repository given to you by the instructor during the lecture, create the path `project-01/part-02/`.

2. Put the `ish_syscalls.amd64.c`, `ish_syscalls.aarch64.c`, `ish_syscalls.riscv64.c` into the `project-01/part-02/` directory.

3. Commit and push your repository through Git. Submit a URL to the last commit on GitHub to Canvas before the deadline.

## Part #3

The goal of the third and final task is to add piping support to our toy shell. Refer to the Readme file in the `ish2` directory for more info.

### What to Submit

1. In your private course repository given to you by the instructor during the lecture, create the path `project-01/part-03/`.

2. Put the `ish.c` file into that directory.

3. Commit and push your repository through Git. Submit a URL to the last commit on GitHub to Canvas before the deadline.

### Deadline

Check Canvas for information about the deadlines.
