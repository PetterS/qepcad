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
     char *EACSTACK;

/* Flush register windows to the stack. */
    
     flush_windows();

/* Get top pointer to the top of the stack. */

     EACSTACK = (char *) get_frame_ptr();

     GCSI(sizeof(Word),EACSTACK);
}
