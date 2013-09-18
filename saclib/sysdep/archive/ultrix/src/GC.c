/*======================================================================
                           GC()

Garbage collection entry-point.

Remarks 
  This is a system- and compiler-dependent function which ensures that
  all registers get pushed onto the stack. This is necessary since the
  GC-proper GCSI() assumes that all GC roots are either located on the
  stack or in the global variables.
======================================================================*/
#include "saclib.h"

void GC()
{
     Word num_registers,register_buff[400];
     char *EACSTACK;

     GETREGSTR(register_buff, &num_registers, &EACSTACK);
     GCSI(sizeof(Word),EACSTACK);
}
