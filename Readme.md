COM-341, Operating Systems
==========================
# Project #1

![ish](http://i.imgur.com/hUwm2PG.gif)

Our esteemed instructor [Sergei Rachmiroff](https://i.imgur.com/hLHngQQ.jpg) is building a hobby operating system. This system needs a shell to allow users to start their programs. Sergei has a toy shell that he wrote many years ago, but unfortunately, the shell relies on the C standard library, which has not been ported to his hobby operating system yet. To make matters worse, Sergei is hesitant to share the code of his OS. The silver lining is that his OS shares the same low-level system call interface as GNU/Linux, which means you can assist in porting the shell to his OS by ensuring the shell operates on GNU/Linux without the C standard library. His OS targets most modern CPU architectures, such as x86-64 and AArch64, implying that without a C library, one will need to make calls to the OS differently for each architecture. Sergei is fond of his old shell code (though its quirky code style may raise eyebrows) and is willing to provide it to you on the condition that you also help add a pipeline mechanism for inter-process communication. Your assistance will significantly influence your grades for this project.

In this project, you will:

* Explore various methods to run multiple operating systems on a computer through virtualization technologies and emulation.
* Understand the differences between virtualization and emulation.
* Install an operating system on a computer.
* Learn the basics of using Unix systems through a terminal.
* Understand how a simple command-line shell operates.
* Learn about the concept of system calls.
* Discover the most common system calls on Unix platforms.
* Learn how a user-space application performs a system call in a low-level language.
* Learn about the hidden costs associated with system calls.
* Understand why direct usage of system calls without standard libraries reduces your program's portability.
* Work with various information sources such as man pages, books, kernel source code, and disassembled code in a debugger to gather necessary information.
* Learn about fundamental I/O abstractions such as Standard Streams.
* Understand how redirection to and from files operates on Unix platforms.
* Learn how piping operates on Unix platforms.

## Required Tools

On your host machine, you will need a GNU/Linux environment with basic Unix command-line utilities and an SSH client to connect to the emulated systems. You will also need the QEMU emulator packages installed. On the latest Ubuntu distributions, packages such as `qemu-system` and `qemu-utils` are necessary. You may also find the `scp` program useful for transferring files between host and guest operating systems.

## Part #1

The goal of the first task is to prepare execution environments for the second and third parts of the project on various CPU architectures, such as x86-64 and ARMv8, on a GNU/Linux operating system.

1. First, create an x86-64 GNU/Linux environment by installing the Debian distribution of GNU/Linux inside the QEMU hardware emulation environment. Follow the `platforms/amd64/` Readme for more info.

2. Second, create an ARMv8 GNU/Linux environment by installing the Debian distribution of GNU/Linux inside the QEMU hardware emulation environment. Follow the `platforms/arm64/` Readme for more info.

### What to Submit

1. Ensure that during the installation process of the x86-64 and ARMv8 versions of Debian, you have specified your first and last name as your full name (e.g., `Dmitrii Toksaitov`). Also, ensure you've provided your `@auca.kg` university email login as both login and password (e.g., `toksaitov_d`). The login and password should not be altered in any way (e.g., `toksaitov_d` should be used as is). You may get different instructions for a particular semester, but the login and password should always be the same.

    Incorrect data specified during the installation process of the x86-64 and ARMv8 versions of Debian will result in incorrect files for submission and zero points for this part. Hence, please provide accurate full name, login, and password.

2. Place the `/etc/shadow` file from the x86-64 and ARMv8 environments into the appropriate `platforms/<arch>/` directories under the name `shadow`. You should get the following new files in your repository:

    * `platforms/amd64/shadow`
    * `platforms/arm64/shadow`

3. Put the output of the `dmesg` command from the x86-64 and ARMv8 environments into the `platforms/<arch>/` directories under the name `dmesg`. You should acquire and submit the following additional files through your repository:

    * `platforms/amd64/dmesg`
    * `platforms/arm64/dmesg`

4. Commit and push your repository through Git. Ensure to pass all the CI tests for Part #1. Submit a URL to the last commit on GitHub that passes the Part #1 tests to Moodle before the deadline.

## Part #2

The goal of the second task is to implement system calls on both platforms from Part #1 in our toy shell. Refer to the Readme file in the `ish` directory for more info.

### What to Submit

Commit and push changes to the `Makefile` (removing `-D ISH_USE_STDLIB`), as well as to the `ish_syscalls.amd64.c` and `ish_syscalls.aarch64.c` files in the `ish` directory, to your repository via Git. Make no other changes—do not remove, alter, or add any other files. Ensure that all CI tests for Part #2 pass. Submit the URL of the last commit on GitHub that passes the Part #2 tests to Moodle before the deadline.

## Part #3

The goal of the third and final task is to add simple piping support to our toy shell. Refer to the Readme file in the `ish2` directory for more info.

### What to Submit

Commit and push changes to `ish.c` in the `ish2` directory to your repository through Git. Do not remove, alter, or add any other files. Ensure to pass all the CI tests. Submit a URL to the last commit on GitHub to Moodle before the deadline.

### Deadline

Check Moodle for information regarding the deadlines.
