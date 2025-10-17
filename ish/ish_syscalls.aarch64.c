

static inline long __syscall0(long n) {
    register long x8 asm("x8") = n;
    register long x0 asm("x0");
    asm volatile("svc 0"
                 : "=r"(x0)
                 : "r"(x8)
                 : "memory","cc");
    return x0;
}

static inline long __syscall1(long n, long a0) {
    register long x8 asm("x8") = n;
    register long x0 asm("x0") = a0;
    asm volatile("svc 0"
                 : "+r"(x0)
                 : "r"(x8)
                 : "memory","cc");
    return x0;
}

static inline long __syscall2(long n, long a0, long a1) {
    register long x8 asm("x8") = n;
    register long x0 asm("x0") = a0;
    register long x1 asm("x1") = a1;
    asm volatile("svc 0"
                 : "+r"(x0)
                 : "r"(x8), "r"(x1)
                 : "memory","cc");
    return x0;
}

static inline long __syscall3(long n, long a0, long a1, long a2) {
    register long x8 asm("x8") = n;
    register long x0 asm("x0") = a0;
    register long x1 asm("x1") = a1;
    register long x2 asm("x2") = a2;
    asm volatile("svc 0"
                 : "+r"(x0)
                 : "r"(x8), "r"(x1), "r"(x2)
                 : "memory","cc");
    return x0;
}

static inline long __syscall4(long n, long a0, long a1, long a2, long a3) {
    register long x8 asm("x8") = n;
    register long x0 asm("x0") = a0;
    register long x1 asm("x1") = a1;
    register long x2 asm("x2") = a2;
    register long x3 asm("x3") = a3;
    asm volatile("svc 0"
                 : "+r"(x0)
                 : "r"(x8), "r"(x1), "r"(x2), "r"(x3)
                 : "memory","cc");
    return x0;
}

static inline long __syscall5(long n, long a0, long a1, long a2, long a3, long a4) {
    register long x8 asm("x8") = n;
    register long x0 asm("x0") = a0;
    register long x1 asm("x1") = a1;
    register long x2 asm("x2") = a2;
    register long x3 asm("x3") = a3;
    register long x4 asm("x4") = a4;
    asm volatile("svc 0"
                 : "+r"(x0)
                 : "r"(x8), "r"(x1), "r"(x2), "r"(x3), "r"(x4)
                 : "memory","cc");
    return x0;
}


enum {
    __NR_read        = 63,
    __NR_write       = 64,
    __NR_openat      = 56,
    __NR_close       = 57,
    __NR_chdir       = 49,
    __NR_dup3        = 24,
    __NR_clone       = 220,
    __NR_execve      = 221,
    __NR_wait4       = 260,
    __NR_exit        = 93,
    __NR_exit_group  = 94,
    __NR_newfstatat  = 79
};

#define AT_FDCWD   (-100)
#define O_WRONLY   0000001
#define O_CREAT    0000100
#define O_TRUNC    0001000
#define O_RDONLY   0000000
#define CLONE_CHILD_CLEARTID 0x00200000
#define CLONE_CHILD_SETTID   0x01000000
#define SIGCHLD               17

long ish_read(int fd, void *buf, unsigned long n) {
    return __syscall3(__NR_read, fd, (long)buf, n);
}

int ish_chdir(const char *path) {
    return (int)__syscall1(__NR_chdir, (long)path);
}

void ish_exit(int status) {
    
    __syscall1(__NR_exit_group, status);
    for(;;) {}
}

int ish_stat(const char *path, void *stat_result) {
   
    return (int)__syscall4(__NR_newfstatat, AT_FDCWD, (long)path, (long)stat_result, 0);
}

int ish_open(const char *path, int flags) {
   
    return (int)__syscall4(__NR_openat, AT_FDCWD, (long)path, flags, 0);
}

int ish_creat(const char *path, unsigned int mode) {
   
    return (int)__syscall4(__NR_openat, AT_FDCWD, (long)path, O_WRONLY|O_CREAT|O_TRUNC, mode);
}

int ish_dup2(int oldfd, int newfd) {
  
    return (int)__syscall3(__NR_dup3, oldfd, newfd, 0);
}

int ish_close(int fd) {
    return (int)__syscall1(__NR_close, fd);
}

int ish_fork(void) {
  
    return (int)__syscall5(__NR_clone,
                           SIGCHLD | CLONE_CHILD_CLEARTID | CLONE_CHILD_SETTID,
                           0, 0, 0, 0);
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
