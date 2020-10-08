### COM-341, Operating Systems
# Project #1, Part #1, Debian for AMD64 CPUs

## Installing Debian

Follow the steps to install the 64-bit AMD64 Debian Linux in QEMU.

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

3. Move into the directory `./debian/amd64`.

        cd 'debian/amd64/'

4. Download the Debian installation disk.

        ./utilities/download_debian.sh

5. Download the UEFI image for QEMU.

        ./utilities/download_uefi.sh

6. Create a new hard drive image file to store the installed system.

        ./utilities/create_disk_image.sh

7. Start the emulator and the installation process.

        ./start_installation.sh

8. Select the `Install` option, NOT the `Graphical Install` option in the
   bootloader. Use `Arrow`-keys or `Backspace` to select items on the screen.
   Follow the steps below to install the system. Note that it is recommended to
   close QEMU after the first successful reboot during the installation process
   and boot Debian for the first time with the `./start.sh` script.

![Step 1](https://i.imgur.com/lCeaTXs.png)
![Step 2](https://i.imgur.com/DBF9IWb.png)
![Step 3](https://i.imgur.com/js1RyDm.png)
![Step 4](https://i.imgur.com/9Y3nvGd.png)
![Step 5](https://i.imgur.com/GUMJbAk.png)
![Step 6](https://i.imgur.com/gT6pc0n.png)
![Step 7](https://i.imgur.com/e0FkqAq.png)
![Step 8](https://i.imgur.com/96R3bnt.png)
![Step 9](https://i.imgur.com/sIFMoJI.png)
![Step 10](https://i.imgur.com/PN2lb5G.png)
![Step 11](https://i.imgur.com/fHGbL4K.png)
![Step 12](https://i.imgur.com/FsGD6sr.png)
![Step 13](https://i.imgur.com/dR0OIR6.png)
![Step 14](https://i.imgur.com/D4SFyOc.png)
![Step 15](https://i.imgur.com/UicmrIP.png)
![Step 16](https://i.imgur.com/W1t7TPA.png)
![Step 17](https://i.imgur.com/WkQrLSQ.png)
![Step 18](https://i.imgur.com/u5OAK4A.png)
![Step 19](https://i.imgur.com/leU3INr.png)
![Step 20](https://i.imgur.com/NEgf6VD.png)
![Step 21](https://i.imgur.com/woGnVTu.png)
![Step 22](https://i.imgur.com/rriDTMU.png)
![Step 23](https://i.imgur.com/tvqFeV1.png)
![Step 24](https://i.imgur.com/Ds5Yha7.png)
![Step 25](https://i.imgur.com/uNXfljW.png)
![Step 26](https://i.imgur.com/QvCRPDU.png)
![Step 27](https://i.imgur.com/a57Y9zK.png)
![Step 28](https://i.imgur.com/3Llnuf8.png)
![Step 29](https://i.imgur.com/LxMDXMD.png)
![Step 30](https://i.imgur.com/kbfGTIO.png)

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

# If the QEMU directory is not there, from `debian/amd64/` execute
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

2. Remove the old disk image.

        ./utilities/remove_old_files.sh
