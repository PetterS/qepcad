/*======================================================================
                           GC()

Garbage collection entry-point.

This is a system- and compiler-dependent function which ensures that all
registers get pushed onto the stack. This is necessary since the GC-proper
GCSI() assumes that all GC roots are either located on the stack or in the
global variables.
======================================================================*/

#include "saclib.h"

static int gc_dummy();

void GC(void)
{

     Word top_of_stack;
#define r(R) register int R = gc_dummy()
     r(r1); r(r2); r(r3); r(r4); r(r5); r(r6); r(r7); r(r8); 
     r(r9); r(r10); r(r11); r(r12); r(r13); r(r14); r(r15); r(r16);
     r1 = gc_dummy(r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16);

     GCSI(sizeof(Word),(char *)&top_of_stack);
}


static int gc_dummy()
{
	return 1;
}
