/*======================================================================
                      C <- AFPAFQ(r,M,A,b)

Algebraic number field polynomial algebraic number field element
quotient.  

Inputs
  r : a BETA-digit, r >= 1, the number of variables.
  M : in Z[x], the minimal polynomial of an algebraic number alpha.  
  A : an element of Q(alpha)[X1,...,Xr].
  b : an element of Q(alpha), b not zero. 

Outputs
  C : an element Q(alpha)[X1,...,Xr], C = A/b.
======================================================================*/
#include "saclib.h"

Word AFPAFQ(r,M,A,b)
       Word r,M,A,b;
{
       Word Ap,C,a,c,e,rp;
       /* hide a,rp; */

Step1: /* A equal 0. */
       if (A == 0)
         {
         C = 0;
         goto Return;
         }

Step2: /* A not equal 0. */
       Ap = A;
       rp = r - 1;
       C = NIL;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         if (rp == 0)
           c = AFQ(M,a,b);
         else
           c = AFPAFQ(rp,M,a,b);
         C = COMP2(c,e,C);
         }
       while (Ap != NIL);
       C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
