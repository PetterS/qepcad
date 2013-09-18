/*======================================================================
                      L <- IPRIMW(A)

Integral polynomial real root isolation, modified Uspensky method, weakly
disjoint intervals.

Inputs
 A : in Z[X], non-zero, squarefree.

Outputs
  L : a list (I1,...,Ir) of standard open or one-point binary rational
      isolating intervals for all of the real roots of A.
      Let (aj,bj) denote the endpoints of Ij;
      then a1 <= b1 <= ... <= ar <= br.
======================================================================*/
#include "saclib.h"

Word IPRIMW(A)
       Word A;
{
       Word Ab,As,I,L,Ls,b,bs,h,k,n;
       /* hide h,k,n; */

Step1: /* Degree zero. */
       n = PDEG(A);
       L = NIL;
       if (n == 0)
         goto Return;

Step2: /* Compute positive roots. */
       Ab = PDBORD(A);
       b = IUPRB(Ab);
       RNFCL2(b,&h,&k);
       As = IUPBHT(Ab,k);
       Ls = IPRIMU(As);
       while (Ls != NIL)
         {
         ADV(Ls,&I,&Ls);
         I = RIRNP(I,b);
         L = COMP(I,L);
         }
       L = INV(L);

Step3: /* Zero root. */
       if (FIRST(Ab) < n)
         L = COMP(LIST2(0,0),L);

Step4: /* Compute negative roots. */
       As = IUPNT(As);
       Ls = IPRIMU(As);
       bs = RNNEG(b);
       while (Ls != NIL)
         {
         ADV(Ls,&I,&Ls);
         I = RIRNP(I,bs);
         L = COMP(I,L);
         }

Return: /* Prepare for return. */
       return(L);
}
