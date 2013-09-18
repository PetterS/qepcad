/*======================================================================
                      L <- IPSRMS(A,I)

Integral polynomial strong real root isolation, modified Uspensky
method, standard interval.

Inputs
  A : in Z[X], with no multiple real roots and with no real roots
      in common with A''.
  I : a standard interval.

Outputs
  L : a list (I1,...,Ir) of isolating intervals for the roots of A in I.
      The intervals Ij contain no roots of A' or A'', are left-open
      and right-closed, have binary rational endpoints, are subintervals
      of I, and satisfy I1 < I2 < ... < Ir.
======================================================================*/
#include "saclib.h"

Word IPSRMS(A,I)
       Word A,I;
{
       Word Ap,App,Apps,Appsp,Aps,Apsp,L,Lp,Lpp;

Step1: /* A=0. */
       if (A == 0)
         {
         L = NIL;
         goto Return;
         }

Step2: /* Isolate roots of A. */
       Ap = IPDMV(1,A);
       L = IPRIMS(A,Ap,I);

Step3: /* Remove roots of A'. */
       Aps = IPPGSD(1,Ap);
       Apsp = IPDMV(1,Aps);
       Lp = IPRIMS(Aps,Apsp,I);
       IPRRLS(A,Aps,L,Lp,&L,&Lp);

Step4: /* Remove roots of A''. */
       App = IPDMV(1,Ap);
       Apps = IPPGSD(1,App);
       Appsp = IPDMV(1,Apps);
       Lpp = IPRIMS(Apps,Appsp,I);
       IPRRLS(A,Apps,L,Lpp,&L,&Lpp);

Return: /* Prepare for return. */
       return(L);
}
