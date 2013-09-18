/*======================================================================
                      FPHAND(i,sip,uap)

Floating-point handler.

Inputs
  i,sip,uap: Look at the man pages for "sigaction".
  
Side Effects
  This function is the exception handler for floating point exceptions.
  It sets the global flag FPFLAG to 1 to indicate error.  Also, it
  turns off *all* floating-point traps, so no floating-point operation
  causes a trap.  This function is system dependent:  for SunOS 5.6.
======================================================================*/
#include "saclib.h"

void FPHAND(i,sip,uap)
       int i;
       siginfo_t* sip;
       void* uap;
{
       struct ucontext *p;

Step1: /* Set floating-point state register mask for 
enabling traps. (bits 23 - 27 on this architecture) */
       p = (struct ucontext*)uap; 
       p->uc_mcontext.fpregs.fpu_fsr &= 
	 (~(
	    (FP_X_INV | FP_X_OFL | FP_X_UFL | 
	     FP_X_DZ | FP_X_IMP) << 23)
	  ); 

Step2: /* Set error flag. */
       FPFLAG = 1;

Return: /* Prepare to return. */
       return;
}
