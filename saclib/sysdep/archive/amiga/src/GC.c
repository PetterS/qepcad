/*======================================================================
                           GC()

Garbage collection entry-point.

This is a system- and compiler-dependent function which ensures that all
registers get pushed onto the stack. This is necessary since the GC-proper
GCSI() assumes that all GC roots are either located on the stack or in the
global variables.
======================================================================*/
#include "saclib.h"

void GC()
{
     Word num_registers, top_of_stack, register_buff[40];
     extern void GETREGSTR();

     GETREGSTR(register_buff, &num_registers, &top_of_stack);
     GCSI(sizeof(Word),(char *)&top_of_stack);
}

