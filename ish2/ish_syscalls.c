#include "ish_syscalls.h"

#if defined __x86_64__ && __LP64__
   #include "ish_syscalls.amd64.c"
#elif defined __aarch64__ && __LP64__
   #include "ish_syscalls.aarch64.c"
#elif defined __riscv && __riscv_xlen==64
   #include "ish_syscalls.riscv64.c"
#else
   #error "Unknown CPU architecture"
#endif
