/*======================================================================
                      Bs <- IPSFBA(r,A,B)

Integral polynomial squarefree basis augmentation.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[X1,...,Xr], A primitive, positive, squarefree, and of positive
      degree in its main variable.
  B : a list (B1,...,Bs), s >= 0, of polynomials in Z[X1,...,Xr].
      B is a squarefree basis.

Outputs
  Bs : a list of polynomials in Z[X1,...,Xr], a coarsest squarefree basis
       for (A,B1,...,Bs).
======================================================================*/
#include "saclib.h"

Word IPSFBA(r,A,B)
       Word r,A,B;
{
       Word Abp,Ap,B1,Bb1,Bp,Bs,C;
       /* hide B1,Bp; */

Step1: /* Compute. */
       Ap = A;
       Bp = B;
       Bs = NIL;
       while (Bp != NIL && PDEG(Ap) > 0)
         {
         ADV(Bp,&B1,&Bp);
         IPGCDC(r,Ap,B1,&C,&Abp,&Bb1);
         if (PDEG(C) > 0)
           Bs = COMP(C,Bs);
         if (PDEG(Bb1) > 0)
           Bs = COMP(Bb1,Bs);
         Ap = Abp;
         }
       if (PDEG(Ap) > 0)
         Bs = COMP(Ap,Bs);
       while (Bp != NIL)
         {
         ADV(Bp,&B1,&Bp);
         Bs = COMP(B1,Bs);
         }

Return: /* Prepare for return. */
       return(Bs);
}
