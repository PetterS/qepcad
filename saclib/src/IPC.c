/*======================================================================
                      C <- IPC(r,A)

Integral polynomial content.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[X1,...,Xr]

Outputs
  C : in Z[X1,...,X_{r-1}], the content of A.
======================================================================*/
#include "saclib.h"

Word IPC(r,A)
       Word r,A;
{
       Word Ap,C,C1,Cp,Cp1,rp;
       /* hide Ap,C1,Cp,Cp1,rp; */

Step1: /* A equal 0. */
       if (A == 0)
         {
         C = 0;
         goto Return;
         }

Step2: /* A not equal 0. */
       Ap = RED(A);
       ADV(Ap,&C,&Ap);
       rp = r - 1;
       while (Ap != NIL)
         {
         Ap = RED(Ap);
         ADV(Ap,&C1,&Ap);
         IPGCDC(rp,C,C1,&C,&Cp,&Cp1);
         if (IPONE(rp,C) == 1)
           goto Return;
         }
       C = IPABS(rp,C);

Return: /* Prepare for return. */
       return(C);
}
