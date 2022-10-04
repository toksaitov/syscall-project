long ish_read(
        int file_descriptor,
        void *buffer,
        unsigned long buffer_size
     )
{
    return -1;
}

int ish_chdir(const char *path)
{
    return -1;
}

void ish_exit(int status)
{
}

int ish_stat(const char *path, void *stat_result)
{
    return -1;
}

int ish_open(const char *path, int flags)
{
    return -1;
}

int ish_creat(const char *path, unsigned int mode)
{
    return -1;
}

int ish_pipe(int file_descriptors[2])
{
    return -1;
}

int ish_dup2(int old_file_descriptor, int new_file_descriptor)
{
    return -1;
}

int ish_close(int file_descriptor)
{
    return -1;
}

int ish_fork()
{
    return -1;
}

int ish_execve(
        const char *path,
        char *const arguments[],
        char *const environment[]
    )
{
    return -1;
}

int ish_waitpid(int pid, int *status, int options)
{
    return -1;
}

long ish_write(
        int file_descriptor,
        const void *buffer,
        unsigned long buffer_size
     )
{
    return -1;
}
