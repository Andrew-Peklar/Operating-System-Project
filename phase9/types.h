// types.h, 159

#ifndef _TYPES_H_
#define _TYPES_H_

#define TIMER_EVENT       32    // IDT entry #32 has code addr for timer event (DOS IRQ0)

#define SYSCALL_EVENT    128
#define WRITE              4
#define GETPID           100    //the new stuff
#define SLEEP            101
#define MUTEX            102
#define STDOUT             1
#define LOCK               0
#define UNLOCK             1
#define LOOP         1666666    // handly loop limit exec asm("inb $0x80");
#define TIME_SLICE       200    // max timer count, then rotate process
#define PROC_NUM          20    // max number of processes
#define Q_SIZE            20    // queuing capacity
#define PROC_STACK_SIZE 4096    // process runtime stack in bytes


#define TERM1 		0x2f8	//phase4
#define TERM2 		0x3e8
#define GETCHAR		  103	//phase5
#define TERM1_EVENT	   35
#define TERM2_EVENT	   36

#define PUTCHAR 104

#define FORK 2            //phase 7
                               //phase 8
#define SIGNAL 48             // service # for Signal() call
#define SIGINT 2              // signal number when ctrl-c is 2

#define SIGCHLD  17          // Phase 9
#define EXIT       1
#define WAITPID    7


typedef void (*func_p_t)(void); // void-return function pointer type

typedef enum {READY, RUN, SLEEPING, WAIT,  WAITCHILD, ZOMBIE} state_t;
//phase 9 added WAITCHILD and ZOMBIE states

typedef struct {
   unsigned int EDI;
   unsigned int ESI;
   unsigned int EBP;
   unsigned int ESP;
   unsigned int EBX;
   unsigned int EDX;
   unsigned int ECX;
   unsigned int EAX;
   unsigned int event_type;
   unsigned int EIP;
   unsigned int CS;
   unsigned int EFL;
} proc_frame_t;

typedef struct {
   state_t state;            // state of process
   int ppid;		     // phase7: parent process id
   int run_time;             // CPU runtime this time
   int life_time;            // total CPU runtime
   int wake_time;            // total time until wake
   proc_frame_t *proc_frame_p; // points to saved process frame
   func_p_t sigint_handler;
   func_p_t sigchld_handler;  //phas 9
} pcb_t;

typedef struct {             // generic queue type
   int size;                 // size is also where the tail is for new data
   int q[Q_SIZE];            // integers are queued in q[] array
} q_t;
//////////////////////////////////
typedef struct {             //
   int lock;                 //
   q_t wait_q;            //
} mutex_t;
//////////////////////////////////
#endif // _TYPES_H_
