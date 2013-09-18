/*======================================================================
                      B <- IPCSFB(r,A)

Integral polynomial coarsest squarefree basis.

Inputs
  r : a BETA-digit, r > 0.
  A : a list of positive primitive polynomials in Z[X1,...,Xr] 
      each of which is of positive degree in its main variable.
      A may be the empty list.

Outputs
  B : a list of polynomials in Z[X1,...,Xr], 
      a coarsest squarefree basis for A.
======================================================================*/
#include "saclib.h"

Word IPCSFB(r,A)
       Word r,A;
{
       Word A1,Ap,Ap1,As,B,L,L1;
       /* hide A1,Ap; */

Step1: /* Compute. */
       As = NIL;
       Ap = A;
       while (Ap != NIL)
         {
         ADV(Ap,&A1,&Ap);
         L = IPSF(r,A1);
         do
           {
           ADV(L,&L1,&L);
           Ap1 = SECOND(L1);
           As = COMP(Ap1,As);
           }
         while (L != NIL);
         }
       B = ISPSFB(r,As);

Return: /* Prepare for return. */
       return(B);
}
