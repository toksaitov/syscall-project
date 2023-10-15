COM-341, Operating Systems
==========================
# Project #1

![ish](http://i.imgur.com/hUwm2PG.gif)

Our esteemed instructor [Sergei Rachmiroff](https://i.imgur.com/hLHngQQ.jpg) is building a hobby operating system. This system needs a shell to allow users to start their programs. Sergei has a toy shell that he wrote many years ago, but unfortunately, the shell relies on the C standard library, which has not been ported to his hobby operating system yet. To make matters worse, Sergei is hesitant to share the code of his OS. The silver lining is that his OS shares the same low-level system call interface as GNU/Linux, which means you can assist in porting the shell to his OS by ensuring the shell operates on GNU/Linux without the C standard library. His OS targets most modern CPU architectures such as x86-64, AArch64, and RISC-V 64, implying that without a C library, one will need to make calls to the OS differently for each architecture. Sergei is fond of his old shell code (though its quirky code style may raise eyebrows) and is willing to provide it to you on the condition that you also help add a pipeline mechanism for inter-process communication (quite a character, isn't he?). Your assistance will significantly influence your grades for this project.

In this project, you will:

* Explore various methods to run multiple operating systems on a computer through virtualization technologies, emulation, and containerization.
* Understand the differences between virtualization, emulation, and containerization.
* Install an operating system on a computer at least once.
* Learn the basics of using Unix systems through a terminal.
* Understand how a simple command line shell operates.
* Learn about the concept of system calls.
* Discover the most common system calls on Unix platforms.
* Learn how a user space application performs a system call in a low-level language.
* Learn about the hidden costs associated with system calls.
* Understand why direct usage of system calls without standard libraries reduces your program's portability.
* Work with various information sources such as man pages, books, kernel source code, and disassembled code in a debugger to gather necessary information.
* Learn about fundamental I/O abstractions such as Standard Streams.
* Understand how redirection to and from files operates on Unix platforms.
* Learn how piping operates on Unix platforms.

## Required Tools

On your host machine, you will need a Unix shell with essential Unix command line utilities, and an SSH client to connect to virtualized, emulated, and containerized systems. You may also find the `scp` program useful for transferring files between host and guest operating systems. On Windows, you can obtain all necessary tools by installing Git from its official [website](https://git-scm.com). On macOS, everything can be acquired by installing Command Line Tools for Xcode with the `xcode-select --install` command. Alternatively, you may also use our lab computers, which have all the required software for this task.

You may also need to install [Docker Desktop](https://www.docker.com/products/docker-desktop) on your host system. Installation could be challenging on some operating systems; do your best by following the official documentation on the Docker [website](https://docs.docker.com/desktop). Although Docker is available on our server and some lab computers, it is only accessible to instructors. However, we provide some workarounds for those who prefer working on lab machines or have difficulty installing Docker successfully. Follow the Readme file from Part #1 in the `platforms/riscv64/` directory for more information.

## Part #1

The goal of the first task is to prepare execution environments for the second and third parts of the project on various CPU architectures, such as x86-64, ARMv8, and RISC-V, on a GNU/Linux operating system.

1. First, create an x86-64 GNU/Linux environment by installing the Debian distribution of GNU/Linux inside the QEMU virtualization environment. Follow the `platforms/amd64/` Readme for more info.

2. Second, create an ARMv8 GNU/Linux environment by installing the Debian distribution of GNU/Linux inside the QEMU hardware emulation environment. Follow the `platforms/arm64/` Readme for more info.

3. Finally, create a RISC-V environment by downloading a `linux/riscv64` image of the Ubuntu distribution of GNU/Linux with the help of the Docker containerization platform. You'll find the Readme file in the `platforms/riscv64/` directory useful, especially if you can't access Docker for some reason.

### What to Submit

1. Ensure that during the installation process of the `amd64` and `arm64` versions of Debian, you have specified your first and last name as your full name (e.g., `Dmitrii Toksaitov`). Also ensure you've provided your `auca.space` login as both login and password. The login and password should not be altered in any way (e.g., `toksaitov_d` should be used as is). You may get different instructions for a particular semester, but the login and password should always be the same.

    Incorrect data specified during the installation process of the `amd64` and `arm64` versions of Debian will result in incorrect files for submission and zero points for this part. Hence, please provide accurate full name, login, and password.

2. In your private course repository given to you by the instructor during the lecture, create the path `project-1/part-1/`.

3. Place the `/etc/shadow` file from the x86-64, ARMv8, and RISC-V environments into the `project-1/part-1/` directory under the name `<arch>-shadow`. You should get the following files there:

    * `amd64-shadow`
    * `arm64-shadow`
    * `riscv64-shadow`

4. Put the output of `dmesg` from the x86-64, ARMv8, and RISC-V environments into the `project-1/part-1/` directory under the name `<arch>-dmesg`. You should acquire and submit the following additional files:

    * `amd64-dmesg`
    * `arm64-dmesg`
    * `riscv64-dmesg`

5. Commit and push your repository through Git. Submit a URL to the last commit on GitHub to Canvas before the deadline.

## Part #2

The goal of the second task is to implement system calls on all three platforms from part #1 in our toy shell. Refer to the Readme file in the `ish` directory for more info.

### What to Submit

1. In your private course repository given to you by the instructor during the lecture, create the path `project-1/part-2/`.

2. Put the `ish_syscalls.amd64.c`, `ish_syscalls.aarch64.c`, `ish_syscalls.riscv64.c` into the `project-1/part-2/` directory.

3. Commit and push your repository through Git. Submit a URL to the last commit on GitHub to Canvas before the deadline.

## Part #3

The goal of the third and final task is to add piping support to our toy shell. Refer to the Readme file in the `ish2` directory for more info.

### What to Submit

1. In your private course repository given to you by the instructor during the lecture, create the path `project-1/part-3/`.

2. Put the `ish.c` file into that directory.

3. Commit and push your repository through Git. Submit a URL to the last commit on GitHub to Canvas before the deadline.

### Deadline

Check Canvas for information regarding the deadlines.
