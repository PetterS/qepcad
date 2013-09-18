/*======================================================================
                      B <- IPFSFB(r,A)

Integral polynomial finest squarefree basis.

Inputs
  r : a BETA-digit, r >= 1.
  A : a list (A1,...,An), n >= 0, Ai in Z[X1,...,Xr], Ai positive,
      primitive, and of positive degree in its main variable.

Outputs
  B : a list of polynomials in Z[X1,...,Xr], a finest squarefree basis
      for A.
======================================================================*/
#include "saclib.h"

Word IPFSFB(r,A)
       Word r,A;
{
       Word B,B1,Bs,L;

Step1: /* Get coarsest squarefree basis for A. */
       Bs = IPCSFB(r,A);

Step2: /* Factor each basis element. */
       B = NIL;
       while (Bs != NIL)
         {
         ADV(Bs,&B1,&Bs);
         L = ISFPF(r,B1);
         B = CONC(L,B);
         }

Return: /* Prepare for return. */
       return(B);
}
