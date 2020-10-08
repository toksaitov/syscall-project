### COM-341, Operating Systems
# Project #1, Part #1, Debian for ARMv8 CPUs

## Installing Debian

Follow the steps to install the 64-bit ARM Debian Linux in QEMU.

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

        cd 'debian/arm64/'

4. Download the Debian installation disk.

        ./utilities/download_debian.sh

5. Download the UEFI image for QEMU.

        ./utilities/download_uefi.sh

6. Create a new hard drive image file to store the installed system.

        ./utilities/create_disk_image.sh

7. Start the emulator and the installation process.

        ./start_installation.sh

8. On Windows, switch to the serial console by pressing `CTRL+ALT+2` in QEMU.
   Select the `Install` option in the bootloader.  Use `Arrow`-keys or
   `Backspace` to select items on the screen.  Follow the steps below to install
   the system. Note that it is recommended to close QEMU after the first
   successful reboot during the installation process and boot Debian for the
   first time with the `./start.sh` script.

![Step 1](https://i.imgur.com/StvLIoc.png)
![Step 2](https://i.imgur.com/kqbbdoC.png)
![Step 3](https://i.imgur.com/kLAZai3.png)
![Step 4](https://i.imgur.com/AnPBFQ9.png)
![Step 5](https://i.imgur.com/upEtoa6.png)
![Step 6](https://i.imgur.com/2alzMWR.png)
![Step 7](https://i.imgur.com/ZshrQGg.png)
![Step 8](https://i.imgur.com/gykJ8ih.png)
![Step 9](https://i.imgur.com/EyBWGFV.png)
![Step 10](https://i.imgur.com/LBnMvIe.png)
![Step 11](https://i.imgur.com/Hykmojn.png)
![Step 12](https://i.imgur.com/5oaY3ME.png)
![Step 13](https://i.imgur.com/UCL8JwT.png)
![Step 14](https://i.imgur.com/WwAa4qX.png)
![Step 15](https://i.imgur.com/EoBDxLl.png)
![Step 16](https://i.imgur.com/UzltsBc.png)
![Step 17](https://i.imgur.com/JwVjw8Z.png)
![Step 18](https://i.imgur.com/oJAFv9U.png)
![Step 19](https://i.imgur.com/nuG1fFe.png)
![Step 20](https://i.imgur.com/e7QoSdK.png)
![Step 21](https://i.imgur.com/TJ6fiYI.png)
![Step 22](https://i.imgur.com/0MABUKh.png)
![Step 23](https://i.imgur.com/vxEvNE5.png)
![Step 24](https://i.imgur.com/eAsF7cf.png)
![Step 25](https://i.imgur.com/GluKM7U.png)
![Step 26](https://i.imgur.com/ljM6u9X.png)
![Step 27](https://i.imgur.com/sldiY11.png)

## Starting and Stopping the System

If the system is not running, you can start the QEMU emulator and Debian with
the following command

```bash
./start.sh
```

If you can not start the emulator on Windows, ensure the QEMU executable
location is in the $PATH environment variable.

```bash
echo $PATH

# If the QEMU directory is not there, from `debian/arm64/` execute
export PATH=$PATH:`cd ../../qemu; pwd`
```

To shut down the system and exit from QEMU

```bash
# After you have started the system and logged-in with the user name
# and password specified during the installation process
sudo systemctl poweroff
```

## Installing Additional Software

1. Start the system and log in.

2. Install the GNU C compiler, the GNU Make build system, the GNU Debugger, and
   the Git version control system.

        sudo apt-get update
        sudo apt-get install gcc make gdb git

3. Shut down the system.

## Fixing Networking Issues [Optional]

1. If you experience connectivity issues in the emulated environment, try
   disabling the IPv6 support in the kernel.

        sudo nano /etc/default/grub

2. Append `ipv6.disable=1` to the `GRUB_CMDLINE_LINUX` variable and save the
   file.

3. Update the GRUB boot loader.

        sudo update-grub

4. Restart the system.

        sudo systemctl reboot

## Cleanup [Optional]

1. Compress the hard drive image file.

        ./utilities/compress_disk_image.sh

2. Remove the old uncompressed disk image.

        ./utilities/remove_old_files.sh
