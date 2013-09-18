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
#include <ieeefp.h>
#include <sys/ucontext.h>

void FPCATCH() 
{
      struct sigaction *p;
  
Step1: /* Set hand as the handler for floating point exceptions. */
      p = (struct sigaction *)malloc(sizeof(struct sigaction));
      p->sa_handler = NULL;
      p->sa_sigaction = FPHAND;
      sigemptyset(&(p->sa_mask));
      p->sa_flags = SA_SIGINFO;
      sigaction(SIGFPE,p,NULL);

Step2: /* Set exceptions that actually cause traps. */
      fpsetmask(FP_X_OFL | FP_X_UFL | FP_X_DZ);

Step3: /* Set error flag to zero. */
      FPFLAG = 0; 
     
Return: /* Prepare to return. */
      return;
}

