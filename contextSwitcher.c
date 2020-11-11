#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "runtime.h"

int contextSwitcher(Process_t* process) {
    void* processStackPointer = process->stackPointer;
    // ((uintptr_t) process->stackPointer + 15) & ~ (uintptr_t) 0x0F;

    // libdyld.dylib`stack_not_16_byte_aligned_error
    // so far, the solution to this error is to push the prior to jumping

    // the optional volatile qualifier has no effect
    // all basic asm blocks are implicitly volatile

    // pushf: push lower 16 bits of EFLAGS
    asm ("\
        pushf \n\
        push %%rax \n\
        push %%rbx \n\
        push %%rcx \n\
        push %%rdx \n\
        push %%rbp \n\
        push %%rdi \n\
        push %%rsi \n\
        push %%r8 \n\
        push %%r9 \n\
        push %%r10 \n\
        push %%r11 \n\
        push %%r12 \n\
        push %%r13 \n\
        push %%r14 \n\
        push %%r15 \n\
	    movq _runtimeStackPointer@GOTPCREL(%%rip), %%rax \n\
        mov %%rsp, (%%rax) \n\
        mov %0, %%rsp \n\
        pop %%r15 \n\
        pop %%r14 \n\
        pop %%r13 \n\
        pop %%r12 \n\
        pop %%r11 \n\
        pop %%r10 \n\
        pop %%r9 \n\
        pop %%r8 \n\
        pop %%rsi \n\
        pop %%rdi \n\
        pop %%rbp \n\
        pop %%rdx \n\
        pop %%rcx \n\
        pop %%rbx \n\
        pop %%rax \n\
        popf \n\
        jmp *(%%rbp) \n\
        .global runtimeEntryPoint \n\
        runtimeEntryPoint: \n\
	    movq _runtimeStackPointer@GOTPCREL(%%rip), %%rax \n\
        movq (%%rax), %%rsp \n\
        pop %%r15 \n\
        pop %%r14 \n\
        pop %%r13 \n\
        pop %%r12 \n\
        pop %%r11 \n\
        pop %%r10 \n\
        pop %%r9 \n\
        pop %%r8 \n\
        pop %%rsi \n\
        pop %%rdi \n\
        pop %%rbp \n\
        pop %%rdx \n\
        pop %%rcx \n\
        pop %%rbx \n\
        pop %%rax \n\
        popf \n\
        "
        : "+r" (processStackPointer)
        :
        : "rax"
    );

    printf("SURVIVER\n");

    // process->stackPointer = processStackPointer;

    return 0;
}