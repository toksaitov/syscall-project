#include "ish_syscalls.h"

/*
    Function Calling Convention

    On x86 (Linux, BSD, Mac OS X) arguments are passed on the stack and pushed
    from right to left.

        buffer_size is pushed first
        the buffer pointer is pushed next
        file_descriptor is pushed last

    Result is returned in the eax register.

    On x86-64 (Linux, BSD, Mac OS X) the first six integer or pointer
    arguments are passed in registers rdi, rsi, rdx, rcx, r8, and r9.

       file_descriptor goes to rdi
       the buffer pointer goes to rsi
       buffer_size goes to rdx

    Result is returned in the rax register.

    On ARM (A32) (Linux, BSD, Mac OS X) the first four integer or pointer
    arguments are passed in registers r0 through r3. The same registers are
    used to return values.

       file_descriptor goes to r0
       the buffer pointer goes to r1
       buffer_size goes to r2

    Result is returned in the r0 register.

    On ARM (A64) (Linux, BSD, Mac OS X) the first eight integer or pointer
    arguments are passed in registers x0 through x7. The same registers are
    used to return values.

       file_descriptor goes to x0
       the buffer pointer goes to x1
       buffer_size goes to x2

    Result is returned in the x0 register.

    You will have to find the calling conventions for MIPS and RISC-V on your
    own.

    ---
    Kernel Calling Convention

    Refer to slides from Practice #2
*/

#if defined __x86_64__ && __LP64__
   #include "ish_syscalls.amd64.c"
#elif defined __aarch64__ && __LP64__
   #include "ish_syscalls.aarch64.c"
#elif defined __mips__ && _MIPSEL && _MIPS_SIM==_ABI64
   #include "ish_syscalls.mips64el.c"
#elif defined __riscv && __riscv_xlen==64
   #include "ish_syscalls.riscv64.c"
#else
   #error "Unknown CPU architecture"
#endif
