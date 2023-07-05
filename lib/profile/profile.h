#ifndef PROFILE_LIBRARY_H
#define PROFILE_LIBRARY_H

#define INLINE __attribute__((__always_inline__))
#define NO_INLINE __attribute__((__noinline__))

void profile_start_rdtsc(void);
void profile_end_rdtsc(char *);
void profile_reset_rdtsc(void);
void profile_flush_rdtsc(void *);

void profile_start_jmp(void);
void profile_end_jmp(void);
void profile_reset_jmp(void);
void profile_flush_jmp(void *);

#define NOP0
#define NOP1   NOP0; nop
#define NOP2   NOP1; nop
#define NOP3   NOP2; nop
#define NOP4   NOP3; nop
#define NOP5   NOP4; nop
#define NOP6   NOP5; nop
#define NOP7   NOP6; nop
#define NOP8   NOP7; nop
#define NOP9   NOP8; nop

#define NOP00
#define NOP10  NOP9; nop
#define NOP20  NOP10; NOP10
#define NOP30  NOP20; NOP10
#define NOP40  NOP30; NOP10
#define NOP50  NOP40; NOP10
#define NOP60  NOP50; NOP10
#define NOP70  NOP60; NOP10
#define NOP80  NOP70; NOP10
#define NOP90  NOP80; NOP10

#define NOP000
#define NOP100  NOP90; NOP10
#define NOP200  NOP100; NOP100
#define NOP300  NOP200; NOP100
#define NOP400  NOP300; NOP100
#define NOP500  NOP400; NOP100
#define NOP600  NOP500; NOP100
#define NOP700  NOP600; NOP100
#define NOP800  NOP700; NOP100
#define NOP900  NOP800; NOP100

#define NOPS(m, n, k) \
    NOP##m##00;       \
    NOP##n##0;        \
    NOP##k
#define STR(s) #s
#define _INSERT_NOPS(c) asm volatile(STR(c))
#define INSERT_NOPS(m, n, k) _INSERT_NOPS(NOPS(m, n, k))

#endif