#include "ish_syscalls.h"

/*
    Function Calling Convention

    On x86-64 (Linux, BSD, Mac OS X) the first six integer or pointer
    arguments are passed in registers rdi, rsi, rdx, rcx, r8, and r9.

       file_descriptor goes to rdi
       the buffer pointer goes to rsi
       buffer_size goes to rdx

    Result is returned in the rax register.

    On ARM (A64) (Linux, BSD, Mac OS X) the first eight integer or pointer
    arguments are passed in registers x0 through x7. The same registers are
    used to return values.

       file_descriptor goes to x0
       the buffer pointer goes to x1
       buffer_size goes to x2

    Result is returned in the x0 register.

    ---
    Kernel Calling Convention

    Refer to slides from Practice #2
*/

/*
   // AT&T/UNIX GCC Inline Assembly Sample

   static const char Argument[] =                   // C constants
      "some data";
   static const unsigned long Another_Argument =
      sizeof(Argument);

   long result;                                     // a C variable

   // x86, x86-64

   __asm__ __volatile__ (
      "op-code<length suffix> %%src_register, %%dest_register\n\t"
      "op-code<length suffix> $immediate, %%dest_register\n\t"
      // ...
      "op-code<length suffix> %<argument number>, %%dest_register\n\t"
      "op-code"
      : "=a" (result)                              // output argument/s
      : "D" ((unsigned long) file_descriptor),     // input arguments
         "S" (buffer),
         "d" (buffer_size),
         "r" (Argument), "r" (Another_Argument)
      : "%used register", "%another used register" // clobbered registers
   );

   // The ARM assembly syntax uses the `#` symbol for constants and NOT
   // the `$` symbol. Registers `r` or `x` (for the 32-bit or 64-bit
   // architecture) do not need a `%%` prefix.

   // `__asm__` and `__volatile__` could also be written as
   // `asm`     and `volatile`.

   // The `volatile` modifier tells the compiler not to remove or reorder
   // the inlined assembly block during the compiler optimization step.

   // <length suffixes>
   //     'b'    'w'     's'     'l'     'q'
   //      8 bit  16 bit  16 bit  32 bit  64 bit  integers
   //                     32 bit  64 bit          floating point numbers
   //
   // Length suffixes are not required for the ARM assembly syntax.

   // Argument numbers go from top to bottom, from left to right
   // starting from zero.
   //
   //     result           : %<argument number> = %0
   //     file_descriptor  : ...                = %1
   //     buffer           :                    = %2
   //     buffer_size      :                    = %3
   //     Argument         :                    = %4
   //     Another_Argument :                    = %5

   // The first quoted letter before the argument in brackets is a
   // register constraint. It tells the compiler to provide the
   // argument through that register.
   //
   // On X86/-64 the following register constraints are possible
   // +---+--------------------------+
   // | r :   any register           |
   // +---+--------------------------+
   // | a :   %rax, %eax, %ax, %al   |
   // | b :   %rbx, %ebx, %bx, %bl   |
   // | c :   %rcx, %ecx, %cx, %cl   |
   // | d :   %rdx, %edx, %dx, %dl   |
   // | S :   %rsi, %esi, %si        |
   // | D :   %rdi, %edi, %di        |
   // +---+--------------------------+
   //
   // On ARM, the `r` constraint will work for all general purpose
   // registers. The input variable's register can be specified after the
   // variable's declaration wrapped in quotes and parentheses.
   //
   //     register long result asm("r7"); // 32-bit ARM
   //     register long result asm("x0"); // 64-bit ARM
   //
   // All registers used as input or output arguments should not be
   // listed as clobbered.
   //
   // https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
*/

#if defined __x86_64__ && __LP64__
   #include "ish_syscalls.amd64.c"
#elif defined __aarch64__ && __LP64__
   #include "ish_syscalls.aarch64.c"
#else
   #error "Unknown CPU architecture"
#endif
