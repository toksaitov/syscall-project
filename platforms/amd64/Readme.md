COM-341, Operating Systems
==========================
# Project #1, Part #1, GNU/Linux on AMD64

## Getting Access to a GNU/Linux Machine

First, create an isolated x86-64 GNU/Linux environment using the QEMU virtualization and emulation system. It is preferable to run QEMU as virtualization software if you have an x86-64 host environment, or as an emulator otherwise.

If you have an x86-64 CPU and virtualization technologies are enabled in your firmware settings (BIOS, UEFI), modify the following files in `platforms/amd64`:

* `start.sh`
* `start_installation.sh`

In each file, replace the word `tcg` on line 17 or 23 with:

* `whpx,kernel-irqchip=off` if you are on Windows 10+ with Hyper-V [enabled](https://learn.microsoft.com/en-us/virtualization/hyper-v-on-windows/quick-start/enable-hyper-v)
* `hax` if you are on Windows 7+ with an Intel CPU and have [Intel HAXM](https://github.com/intel/haxm) hypervisor installed
* `hvf` if you are on macOS 10.10+
* `kvm` if you are on GNU/Linux and have the `qemu-kvm` package installed

If you cannot enable virtualization on your computer or are using lab machines, retain the `tcg` on line 17 or 23 in all the files. Note that QEMU will run as an emulator in this case, and the emulation process will be slower compared to virtualization. The steps below may consequently take more time.

Now, with or without virtualization, proceed with the steps below:

1. Navigate to the project directory `./syscall-project/`.

        cd 'syscall-project/'

2. Download the QEMU hardware emulator for your operating system.

        # On Windows (from the Bash shell bundled with Git)
        ./utilities/download_qemu_win64.sh

        # On macOS with [Homebrew](http://brew.sh)
        brew install qemu

        # On Ubuntu Linux
        sudo apt install curl qemu-system # Add `qemu-kvm` if virtualization is available

3. Change to the directory `./platforms/amd64`.

        cd 'platforms/amd64/'

4. Download the Debian installation disk.

        ./utilities/download_debian.sh

5. Download the UEFI image for QEMU.

        ./utilities/download_firmware.sh

6. Create a new hard drive image file to store the installed system.

        ./utilities/create_disk_image.sh

7. Launch the emulator and begin the installation process. It is advisable to use hardware virtualization for this step. Run the `start_installation.sh` script:

        ./start_installation.sh

8. Select the `Install` option (not the `Graphical Install` option) in the bootloader. Use `Arrow` keys or `Backspace` to navigate the screen. Follow the installation steps provided. It's recommended to close QEMU after the first successful reboot during the installation, and boot Debian for the first time using the `./start.sh` script.

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
![Step 11](https://i.imgur.com/D4SFyOc.png)
![Step 12](https://i.imgur.com/UicmrIP.png)
![Step 13](https://i.imgur.com/W1t7TPA.png)
![Step 14](https://i.imgur.com/WkQrLSQ.png)
![Step 15](https://i.imgur.com/u5OAK4A.png)
![Step 16](https://i.imgur.com/leU3INr.png)
![Step 17](https://i.imgur.com/NEgf6VD.png)
![Step 18](https://i.imgur.com/woGnVTu.png)
![Step 19](https://i.imgur.com/rriDTMU.png)
![Step 20](https://i.imgur.com/tvqFeV1.png)
![Step 21](https://i.imgur.com/Ds5Yha7.png)
![Step 22](https://i.imgur.com/uNXfljW.png)
![Step 23](https://i.imgur.com/QvCRPDU.png)
![Step 24](https://i.imgur.com/a57Y9zK.png)
![Step 25](https://i.imgur.com/3Llnuf8.png)
![Step 26](https://i.imgur.com/LxMDXMD.png)

You may not see the screen below and instead see a firmware error complaining that it failed to find a bootloader. In such a case, close the current QEMU instance and restart the emulator with `./start.sh`, click inside of the QEMU window to focus it, and press `ESC` quickly to enter the firmware settings. Manually configure the boot menu by removing all the existing entries and adding a new one pointing to the `grubx64.efi` file in the `EFI/debian` directory on the virtual hard drive. Save the changes and exit the firmware settings. The system should now boot into Debian.

![Step 30](https://i.imgur.com/kbfGTIO.png)

## Starting and Stopping the System

To start the QEMU emulator and Debian when the system is not running, use the following command:

```bash
./start.sh
```

If you encounter difficulties starting the emulator on Windows, ensure the QEMU executable location is added to the `$PATH` environment variable.

```bash
echo $PATH

# If the QEMU directory is not listed, from `platforms/amd64/` execute
export PATH=$PATH:`cd ../../qemu; pwd`
```

To power off the system and exit QEMU:

```bash
# After logging in with the username and password specified during installation
sudo systemctl poweroff
```

## Installing Additional Software

1. Start the system and log in.

2. Install the GNU C compiler, GNU Make build system, GNU Debugger, and Git version control system.

        sudo apt-get update
        sudo apt-get install gcc make gdb git

3. Shut down the system.

## Fixing Networking Issues [Optional]

1. If you encounter connectivity issues in the emulated environment, consider disabling IPv6 support in the kernel.

        sudo nano /etc/default/grub

2. Append `ipv6.disable=1` to the `GRUB_CMDLINE_LINUX` variable and save the file.

3. Update the GRUB boot loader.

        sudo update-grub

4. Restart the system.

        sudo systemctl reboot

## Cleanup [Optional]

1. Compress the virtual hard drive image file to conserve space on your computer.

        ./utilities/compress_disk_image.sh

2. Remove the old uncompressed disk image.

        ./utilities/remove_old_files.sh
