#pragma once
#include <string>

#include "queue.hpp"
#include "runtimeCall.hpp"

#define CONCURENCY 32

#define STACKSIZE 4096

#define TRUE 1
#define FALSE 0

#define YEILD 0
#define CREATE 1
#define SEND 2
#define RECEIVE 3

typedef struct Process {
    int identifier;
    std::string processName;
    void* stackPointer;
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

extern RuntimeRequest_t* runtimeRequestStatic;

extern void runtimeEntryPoint(void) asm("runtimeEntryPoint");

extern void yeildReturnPoint(void) asm("yeildReturnPoint");

RuntimeRequest_t* contextSwitcher(Process_t*);

void dispatcher(void);

void createProcess(void (*)(void), std::string);

void printProcess(void* process);

Process_t* dequeFree(void);

void enqueFree(Process_t*);

void yeildRuntime(void);

void receiveMessage(std::string sender, char* receiveBuffer);

void sendMessage(std::string recipient, char* sendBuffer, int size);