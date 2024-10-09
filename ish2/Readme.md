COM 341, Operating Systems
==========================
# Project #1 Part #3: Pipes

### Initial Steps

1. Navigate to the directory containing the Debian hard drive image. Use the one that you can use in virtualization mode.

        cd 'syscall-project/debian/amd64' # or 'syscall-project/debian/arm64' if you are on ARM host

2. Launch Debian Linux in QEMU.

        ./start.sh

3. Start a new shell instance.

4. Copy the `ish2` directory from your machine to the emulated system using `scp` or Git.

5. Log into the Debian system through SSH using the credentials specified during the installation process.

        ssh -p 2222 <login>@127.0.0.1 # or ssh -p 2223 <login>@127.0.0.1

6. Change to the directory `ish2`.

   In this task, you will need to follow the TODO comments in the main `ish.c` file to add support for piping to the second version of our shell.

   Locate the first comment in the `ish.c` file from the top and follow the instructions.

   Finally, compile the program by running `make` and test that you can pipe data from one program to another. Note that not all programs will work with piping in our shell due to the simplicity of our implementation. Use the provided examples below to test your implementation.

### Managing Sources and Executables

* Build or rebuild the shell.

        make

* Test the shell by typing built-in commands such as `cd` and `exit`. Try launching various system programs such as `ls` or `date` either with an absolute path to the executable or without it, and with or without parameters. Experiment with redirecting standard input or output streams using the `<` and `>` operators. Try to pipe the output of one program into another.

        ./ish
        /bin/ls
        /bin/ls -l /etc

  Press `CTRL+C` to exit.

        ./ish
        cd
        ls
        exit

        ./ish
        date
        exit

        ./ish
        cd /tmp
        ls > listing.txt
        cat < listing.txt
        echo hello | cat
        echo hello | cat | less
        echo hello | cat > out1.txt
        cat < out1.txt | cat | cat > out2.txt
        cat < out1.txt
        cat < out2.txt
        exit 1
        echo $? # in the parent shell

  Note: This is a toy shell and does not support many features. You will not be able to edit your input, and command autocomplete is not available.

* Remove compiled files.

    make clean

### Documentation

    man 2 syscall
    man 2 syscalls

    man 2 openat
    man 2 pipe
    man 2 dup2
    man 2 close
    ...

### Reading

* [C Books and Guides](https://github.com/auca/com.341/blob/master/Practice_Tasks/Tasks.md)
