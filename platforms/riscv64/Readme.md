### COM 341, Operating Systems
# Project #1, Part #1, Debian for RISC-V 64-bit CPUs

## Installing Debian

First, try to install the [Docker Desktop](https://www.docker.com/products/docker-desktop) containerization platform on your computer. The Docker Desktop installation could be pretty challenging on some operating systems. Do your best by following the official documentation on the Docker [Website](https://docs.docker.com/desktop). If you succeed, you will most likely be able to get a RISC-V 64 environment with just the following command:

        docker run --interactive --tty --platform linux/riscv64 ubuntu

...and restart it with

        docker start <container ID>

...where the `<container ID>` can be found with the `docker ps -a` command.

In case of success, jump straight to `Installing Additional Software` part of the document.

In case of failure, you will have to use QEMU and Debian again. Follow the steps below to set up the emulation environment.

1. Move into the project directory `./syscall-project/`.

        cd 'syscall-project/'

2. Download the hardware emulator QEMU for your operating system.

        # On Windows (from the Bash shell bundled with Git)
        ./utilities/download_qemu_win64.sh

        # On macOS with [Homebrew](http://brew.sh)
        brew install qemu

        # On Ubuntu Linux
        sudo apt install curl qemu-system

3. Move into the directory `./platforms/arm64`.

        cd 'platforms/riscv64/'

4. Download the Debian disk image.

   RISC-V CPU architecture is less populare compared to x86 and Arm. That is why we will not install the system as there are no installers available yet. Instead, we will use a prebuilt image from <https://people.debian.org/~gio/dqib> created by [Giovanni Mascellani](https://wiki.debian.org/GiovanniMascellani).

        ./utilities/download_debian.sh

## Starting and Stopping the System

If the system is not running, you can start the QEMU emulator and Debian with the following command

```bash
./start.sh
```

On Windows, switch to the serial console by pressing `CTRL+ALT+2` in QEMU. You can login as a privileged user by using the login `root` with the password `root`.

![Qemu](https://i.imgur.com/WD8RVzq.png)

If you can not start the emulator on Windows, ensure the path to the QEMU executable is in the `$PATH` environment variable.

```bash
echo $PATH

# If the QEMU directory is not there, from `platforms/arm64/` execute
export PATH=$PATH:`cd ../../qemu; pwd`
```

To shutdown the system and exit from QEMU

```bash
# After you have started the system and logged-in with the user name
# and password specified during the installation process
systemctl poweroff
```

## Installing Additional Software

1. Start the system and log in.

2. Install the GNU C compiler, the GNU Make build system, the GNU Debugger, and the Git version control system with the program to search and open documentation.

        apt-get update
        apt-get install gcc make gdb git man

## Cleanup [Optional]

1. Compress the virtual hard drive image file to save some space on your computer.

        ./utilities/compress_disk_image.sh

2. Remove the old uncompressed disk image.

        ./utilities/remove_old_files.sh
