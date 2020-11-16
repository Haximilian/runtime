#define CONCURENCY 32

#define STACKSIZE 4096

#define TRUE 1
#define FALSE 0

enum Operation {
    yeild,
    create,
    send,
    receive
};

typedef struct Process {
    int identifier;
    void* stackPointer;
    struct Process* next;
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

Process_t* finalReady;
Process_t* initialReady;
Process_t* finalFree;
Process_t* initialFree;

void* runtimeStackPointer;

extern void runtimeEntryPoint(void) asm("runtimeEntryPoint");

extern void yeildReturnPoint(void) asm("yeildReturnPoint");

int contextSwitcher(Process_t*);

void dispatcher(void);

void createProcess(void (*)(void));

Process_t* dequeReady(void);

void enqueReady(Process_t*);

void printReadyQueue(void);

Process_t* dequeFree(void);

void enqueFree(Process_t*);

void yeildRuntime(void);