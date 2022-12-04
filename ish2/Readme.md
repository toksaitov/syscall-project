COM 341, Operating Systems
==========================
# Project #1 Part #3: Pipes

### Initial Steps

1. Move into the directory with the Debian hard drive image.

        cd 'syscall-project/debian/amd64'

2. Start Debian Linux in QEMU.

        ./start.sh

3. Start a new shell instance.

4. Copy the `ish2` directory from your machine to the emulated system with `scp` or git.

5. Login into the Debian system through SSH. Use the login that you have specified during the installation process.

        ssh -p 2222 <login>@127.0.0.1

6. Go into the directory `ish2`.

   In this task, you will have to follow the TODO comments in the main `ish.c` file to add support for piping to the second version of our shell.

   Find the first comment in the `ish.c` file from the top and follow the instructions.

   In the end, compile the program by running `make` and test that you can pipe data from one program to another. Not all the programs will work in a pipe in our shell due to the simplicity of our implementation. Use the provided examples below to test your implementation.

### Managing Sources and Executables

* Build or rebuild the shell.

        make

* Test the shell by typing built-in commands such as `cd` and `exit`. Try to start various system programs such as `ls` or `date` with an absolute path to the executable or without it, with parameters or without them. Try redirecting standard input or output streams with `<` and `>` operators. Try to pipe the output of one program into another one.

        ./ish
        /bin/ls
        /bin/ls -l /etc

  press `CTRL+C` to exit

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
        echo hello < out1.txt | cat > out2.txt
        cat < out1.txt
        cat < out2.txt
        exit 1
        echo $? # in the parent shell

  Note that we have a toy shell that does not know how to do a lot of things. You will not be able to edit your input. Autocomplete of commands is not available here.

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

* [C Books and Guides](https://github.com/auca/com.341/blob/master/Labs/Labs.md#links)
