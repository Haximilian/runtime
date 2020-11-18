#pragma once
#include <string>
#include "queue.hpp"

#define CONCURENCY 32

#define STACKSIZE 4096

#define TRUE 1
#define FALSE 0

enum State {
    dead,
    ready
};

enum Operation {
    yeild,
    create,
    send,
    receive
};

typedef struct Process {
    int identifier;
    std::string processName;
    void* stackPointer;
    enum State state;
    struct Process* next;
    struct Process* prev;
} Process_t;

typedef struct Context {
    void* r15;
    void* r14;
    void* r13;
    void* r12;
    void* r11;   
    void* r10;
    void* r9;
    void* r8;   
    void* rsi;
    void* rdi;
    void* rbp;
    void* rdx;
    void* rcx;
    void* rbx;
    void* rax;
    void* eflags;
    void* instructionPointer;
} Context_t;

extern Queue_t readyQueue;

extern Process_t* finalFree;
extern Process_t* initialFree;

extern void* runtimeStackPointer;

extern void runtimeEntryPoint(void) asm("runtimeEntryPoint");

extern void yeildReturnPoint(void) asm("yeildReturnPoint");

int contextSwitcher(Process_t*);

void dispatcher(void);

void createProcess(void (*)(void), std::string);

void printProcess(void* process);

Process_t* dequeFree(void);

void enqueFree(Process_t*);

void yeildRuntime(void);