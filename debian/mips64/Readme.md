### COM 341, Operating Systems
# Project #1, Part #1, Debian for MIPS 64-bit (Little Endian) CPUs

## Installing Debian

Follow the steps to install the 64-bit MIPS Debian Linux in QEMU.

1. Move into the project directory `./syscall-project/`.

        cd 'syscall-project/'

2. Download the hardware emulator QEMU for your operating system.

        # On Windows (from the Bash shell bundled with Git)
        ./utilities/download_qemu_win64.sh # or download_qemu_win32.sh on a
                                           # 32-bit Windows

        # On macOS with [Homebrew](http://brew.sh)
        brew install qemu

        # On Ubuntu Linux
        sudo apt install curl qemu-system

3. Move into the directory `./debian/arm64`.

        cd 'debian/mips64/'

4. Download the Debian disk image. MIPS CPU architecture is less populare
   compared to x86 and Arm. That is why we will use prebuilt images from
   <https://people.debian.org/~gio/dqib> created weekly by
   [Giovanni Mascellani](https://wiki.debian.org/GiovanniMascellani).

        ./utilities/download_debian.sh

## Starting and Stopping the System

If the system is not running, you can start the QEMU emulator and Debian with
the following command

```bash
./start.sh
```

On Windows, switch to the serial console by pressing `CTRL+ALT+3` in QEMU. You
can login as a privileged user by using the login `root` with the password
`root`.

![Qemu](https://i.imgur.com/cmAbobQ.png)

If you can not start the emulator on Windows, ensure the path to the QEMU
executable is in the $PATH environment variable.

```bash
echo $PATH

# If the QEMU directory is not there, from `debian/arm64/` execute
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

2. Install the GNU C compiler, the GNU Make build system, the GNU Debugger, and
   the Git version control system with the program to search and open
   documentation.

        apt-get update
        apt-get install gcc make gdb git man

## Cleanup [Optional]

1. Compress the hard drive image file.

        ./utilities/compress_disk_image.sh

2. Remove the old uncompressed disk image.

        ./utilities/remove_old_files.sh
