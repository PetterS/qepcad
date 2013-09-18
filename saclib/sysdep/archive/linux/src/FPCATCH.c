/*======================================================================
                      FPCATCH()

Floating-point catch.

Side Effects
  This function:
  1)  Sets FPHAND as the exception handling funciton for floating-
      point exceptions.
  2)  Sets overflow, underflow, and divide-by-zero as errors which
      result in traps.
  3)  Sets FPFLAG, a global variable that indicates whether a
      floating-point error has occured, to zero --- i.e. no error.
======================================================================*/
#include "saclib.h"
#include <fpu_control.h>
#include <signal.h>
#include <ucontext.h>

void FPCATCH() 
{ 
     fpu_control_t cw;
     struct sigaction *p;

Step1: /* Set FPHAND as the handler for floating point exceptions. */
     p = (struct sigaction *)malloc(sizeof(struct sigaction));
     p->sa_handler = FPHAND;
     sigemptyset(&(p->sa_mask));
     p->sa_flags = SA_ONESHOT | SA_SIGINFO;
     sigaction(SIGFPE,p,NULL);

Step2: /* Set exceptions that actually cause traps. This must include
overflow and underflow. */
     _FPU_GETCW(cw);
     cw &= ~(_FPU_MASK_IM | _FPU_MASK_DM | _FPU_MASK_ZM | 
	     _FPU_MASK_OM | _FPU_MASK_UM);
     _FPU_SETCW(cw);

Step3: /* Set error flag to zero. */
      FPFLAG = 0; 
     
Return: /* Prepare to return. */
      return;
}
