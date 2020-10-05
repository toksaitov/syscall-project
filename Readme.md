### COM 341, Operating Systems
# Project #1

![ish](http://i.imgur.com/hUwm2PG.gif)

## Required Tools

Ensure that you have the Bash shell with common Unix utilities (GNU coreutils or
any alternatives), and the Git version control system installed on your system.

* On Windows, you can get the official Git
  [distribution](https://git-scm.com/downloads) with everything you need in one
  package.

* On macOS, you can get Git by installing Xcode or the Command Line Tools
  [package](https://developer.apple.com/opensource) from Apple.

* On Ubuntu Linux, you can install Git through the system's package manager with
  the command `sudo apt install git`.

macOS and Ubuntu Linux have Bash and basic Unix programs installed by default.

## Part #1

The goal of the first task is to prepare execution environments for the second
part of the project.

* First, you need to set an execution environment on your personal computer
  (with an x86 or x86-64 CPU architecture) for specific CPU architectures such
  as `amd64`, `aarch64`, `mips64el`, and `riscv64`. To emulate the ARMv8, MIPS64
  LE, and RISC-V 64 CPUs, we will use the QEMU hardware emulator. Through QEMU,
  we will install and use the Debian Linux operating system. Refer to the Readme
  files in directories `debian/amd64/`, `debian/arm64/` , `debian/mips64/`, and
  `debian/riscv64/` for specific details on what to do to set up the \ systems.

### What to Submit

1. Ensure that during the installation process of the `amd64` and `arm64`
   versions of Debian, you have specified your first and last name as your full
   name (e.g., `Dmitrii Toksaitov`).  Ensure that you have also provided your
   `auca.space` login as a login and password. You will have to replace the
   underscore character with a dash to continue the installation process (e.g.,
   `toksaitov-d`, NOT `toksaitov_d`). Incorrect data specified during the
   installation process will give you the wrong files to submit and zero points
   for the part as a result. Please, provide the correct full name, login, and
   password.

2. In your private course repository that was given to you by the instructor
   during the lecture, create the path `project-1/part-1/`.

3. Put the `/etc/shadow` file from each operating system into the directory
   under the name `<arch>-shadow` in the course repository. You should get the
   following four files

    * `amd64-shadow`
    * `arm64-shadow`
    * `mips64-shadow`
    * `riscv64-shadow`

4. Put the output of `dmesg` from each operating system into the directory under
   the name `<arch>-dmesg` in the course repository. You should get and submit the
   following additional four files

    * `amd64-dmesg`
    * `arm64-dmesg`
    * `mips64-dmesg`
    * `riscv64-dmesg`

5. Commit and push your repository through Git. Submit the last commit ID to Canvas
   before the deadline.

## Part #2

The goal of the second task is to implement system calls on all the four
platforms from part 1 in sources of a toy shell. Refer to the Readme file in the
`ish` directory for more info.

### What to Submit

1. In your private course repository that was given to you by the instructor
   during the lecture, create the path `project-1/part-2/`.

3. Put the `ish_syscalls.amd64.c`, `ish_syscalls.aarch64.c`,
   `ish_syscalls.mips64el.c`, and `ish_syscalls.riscv64.c`into the course
   repository.

5. Commit and push your repository through Git. Submit the last commit ID to
   Canvas before the deadline. You may get two deadlines. In that case, you
   should submit `ish_syscalls.amd64.c`, `ish_syscalls.aarch64.c` first, then
   the other two files as a separate submission.

### Deadline

Check Canvas for information about the deadlines.
