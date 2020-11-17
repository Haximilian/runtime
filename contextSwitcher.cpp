#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "runtime.hpp"

int contextSwitcher(Process_t* process) {
    runtimeStackPointer = process->stackPointer;

    // if you remove this line or replace it another syscall such as sleep,
    // you'll receive a stack_not_16_byte_aligned_error
    printf("context switch\n");

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
	    mov _runtimeStackPointer@GOTPCREL(%%rip), %%rax \n\
        mov (%%rax), %%rbx \n\
        mov %%rsp, (%%rax) \n\
        mov %%rbx, %%rsp \n\
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
        ret \n\
        .global runtimeEntryPoint \n\
        runtimeEntryPoint: \n\
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
        mov %%rsp, %%rbx \n\
	    mov _runtimeStackPointer@GOTPCREL(%%rip), %%rax \n\
        mov (%%rax), %%rsp \n\
        mov %%rbx, (%%rax) \n\
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
        :
        :
        : "rax", "rbx"
    );

    process->stackPointer = runtimeStackPointer;

    return 0;
}