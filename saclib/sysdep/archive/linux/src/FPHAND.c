/*======================================================================
                      FPHAND(i,sip,uap)

Floating-point handler.

Inputs
  i,sip,uap: Look at the man pages for "sigaction".
  
Side Effects
  This function is the exception handler for floating point exceptions.
  It sets the global flag FPFLAG to 1 to indicate error.  Also, it
  turns off *all* floating-point traps, so no floating-point operation
  causes a trap.  This function is system dependent: Linux kernel v2.2
======================================================================*/
#include "saclib.h"

void FPHAND(i,sip,uap)
       int i;
       siginfo_t* sip;
       void* uap;
{
      ucontext_t *p;

Step1: /* Set floating-point state register mask for 
enabling traps. (bits 23 - 27 on this architecture) */
      p = (ucontext_t*)uap;
      (p->uc_mcontext.fpregs)->cw 
	|= (_FPU_MASK_IM | _FPU_MASK_DM | _FPU_MASK_ZM | 
	    _FPU_MASK_OM | _FPU_MASK_UM);

Step2: /* Set error flag. */
       FPFLAG = 1;

Return: /* Prepare to return. */
       return;
}
