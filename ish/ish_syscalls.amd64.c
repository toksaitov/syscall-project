

static inline long __syscall0(long n) {
    register long rax asm("rax") = n;
    asm volatile("syscall"
                 : "+r"(rax)
                 : 
                 : "rcx","r11","memory");
    return rax;
}

static inline long __syscall1(long n, long a1) {
    register long rax asm("rax") = n;
    register long rdi asm("rdi") = a1;
    asm volatile("syscall"
                 : "+r"(rax)
                 : "r"(rdi)
                 : "rcx","r11","memory");
    return rax;
}

static inline long __syscall2(long n, long a1, long a2) {
    register long rax asm("rax") = n;
    register long rdi asm("rdi") = a1;
    register long rsi asm("rsi") = a2;
    asm volatile("syscall"
                 : "+r"(rax)
                 : "r"(rdi), "r"(rsi)
                 : "rcx","r11","memory");
    return rax;
}

static inline long __syscall3(long n, long a1, long a2, long a3) {
    register long rax asm("rax") = n;
    register long rdi asm("rdi") = a1;
    register long rsi asm("rsi") = a2;
    register long rdx asm("rdx") = a3;
    asm volatile("syscall"
                 : "+r"(rax)
                 : "r"(rdi), "r"(rsi), "r"(rdx)
                 : "rcx","r11","memory");
    return rax;
}

static inline long __syscall4(long n, long a1, long a2, long a3, long a4) {
    register long rax asm("rax") = n;
    register long rdi asm("rdi") = a1;
    register long rsi asm("rsi") = a2;
    register long rdx asm("rdx") = a3;
    register long r10 asm("r10") = a4;
    asm volatile("syscall"
                 : "+r"(rax)
                 : "r"(rdi), "r"(rsi), "r"(rdx), "r"(r10)
                 : "rcx","r11","memory");
    return rax;
}

static inline long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    register long rax asm("rax") = n;
    register long rdi asm("rdi") = a1;
    register long rsi asm("rsi") = a2;
    register long rdx asm("rdx") = a3;
    register long r10 asm("r10") = a4;
    register long r8  asm("r8")  = a5;
    register long r9  asm("r9")  = a6;
    asm volatile("syscall"
                 : "+r"(rax)
                 : "r"(rdi), "r"(rsi), "r"(rdx), "r"(r10), "r"(r8), "r"(r9)
                 : "rcx","r11","memory");
    return rax;
}


enum {
    __NR_read   = 0,
    __NR_write  = 1,
    __NR_open   = 2,
    __NR_close  = 3,
    __NR_stat   = 4,
    __NR_fork   = 57,
    __NR_execve = 59,
    __NR_wait4  = 61,
    __NR_chdir  = 80,
    __NR_dup2   = 33,
    __NR_creat  = 85,
    __NR_exit   = 60
};

long ish_read(int fd, void *buf, unsigned long n) {
    return __syscall3(__NR_read, fd, (long)buf, n);
}

int ish_chdir(const char *path) {
    return (int)__syscall1(__NR_chdir, (long)path);
}

void ish_exit(int status) {
    __syscall1(__NR_exit, status);
    for(;;) {}
}

int ish_stat(const char *path, void *stat_result) {
    return (int)__syscall2(__NR_stat, (long)path, (long)stat_result);
}

int ish_open(const char *path, int flags) {
    return (int)__syscall2(__NR_open, (long)path, (long)flags);
}

int ish_creat(const char *path, unsigned int mode) {
    return (int)__syscall2(__NR_creat, (long)path, mode);
}

int ish_dup2(int oldfd, int newfd) {
    return (int)__syscall2(__NR_dup2, oldfd, newfd);
}

int ish_close(int fd) {
    return (int)__syscall1(__NR_close, fd);
}

int ish_fork(void) {
    return (int)__syscall0(__NR_fork);
}

int ish_execve(const char *path, char *const argv[], char *const envp[]) {
    return (int)__syscall3(__NR_execve, (long)path, (long)argv, (long)envp);
}

int ish_waitpid(int pid, int *status, int options) {
   
    return (int)__syscall4(__NR_wait4, pid, (long)status, options, 0);
}

long ish_write(int fd, const void *buf, unsigned long n) {
    return __syscall3(__NR_write, fd, (long)buf, n);
}
