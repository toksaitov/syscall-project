COM-341, Operating Systems
==========================
# Project #1, Part #1: Debian for RISC-V 64-bit CPUs

## Installing Debian

First, install the [Docker Desktop](https://www.docker.com/products/docker-desktop) containerization platform on your computer. Installing Docker Desktop can be challenging on certain operating systems. Follow the official documentation on the Docker [Website](https://docs.docker.com/desktop). If successful, you can set up a RISC-V 64 environment using the following command:

        docker run --interactive --tty riscv64/debian:rc-buggy

To restart, use:

        docker start -i <container ID>

Here, `<container ID>` can be identified using the `docker ps -a` command.

If successful, proceed to the `Installing Additional Software` section.

If unsuccessful, you'll need to use QEMU and Debian. Follow the steps below to set up the emulation environment:

1. Navigate to the project directory `./syscall-project/`.

        cd 'syscall-project/'

2. Download the QEMU hardware emulator for your operating system.

        # On Windows (using the Bash shell bundled with Git)
        ./utilities/download_qemu_win64.sh

        # On macOS with [Homebrew](http://brew.sh)
        brew install qemu

        # On Ubuntu Linux
        sudo apt install curl qemu-system

3. Navigate to the directory `./platforms/riscv64/`.

        cd 'platforms/riscv64/'

4. Download the Debian disk image. Note that the RISC-V CPU architecture is less popular than x86 and Arm, so we won't install the system directly as installers are not available. Instead, use a prebuilt image from <https://people.debian.org/~gio/dqib>, created by [Giovanni Mascellani](https://wiki.debian.org/GiovanniMascellani).

        ./utilities/download_debian.sh

## Starting and Stopping the System

To start the QEMU emulator and Debian when the system is not running, use:

```bash
./start.sh
```

For Windows, switch to the serial console in QEMU by pressing `CTRL+ALT+2`. Login as the privileged user using `root` for both username and password.

![Qemu](https://i.imgur.com/WD8RVzq.png)

If you encounter issues starting the emulator on Windows, ensure the QEMU executable path is in the `$PATH` environment variable.

```bash
echo $PATH

# If the QEMU directory is missing in $PATH, from `platforms/arm64/`, execute:
export PATH=$PATH:`cd ../../qemu; pwd`
```

To shut down the system and exit QEMU:

```bash
# After starting the system and logging in with the specified credentials during installation:
systemctl poweroff
```

## Installing Additional Software

1. Start the system and log in.

2. Install the GNU C compiler, the GNU Make build system, the GNU Debugger, the Git version control system, and the program to search and view documentation.

        apt-get update
        apt-get install gcc make gdb git man

## Cleanup [Optional]

1. Compress the virtual hard drive image file to save space on your computer.

        ./utilities/compress_disk_image.sh

2. Remove the old uncompressed disk image.

        ./utilities/remove_old_files.sh
