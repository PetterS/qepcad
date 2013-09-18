/*======================================================================
                      B <- AFPINT(r,M,A,b)

Algebraic number field polynomial integration.  

Inputs
  r : a BETA-digit, r >= 1.
  M : in Z[x], the minimal polynomial of an algebraic number alpha.  
  A : in Q(alpha)[X1,...,Xr], A not zero. 
  b : in Q(alpha)[X1,...,X_{r-1}].

Outputs
  B :  in Q(alpha)[X1,...,Xr]. B(X1,...,Xr) is the integral 
       of A with respect to its main variable, such that 
       B(X1,...,X_{r-1},0) = b.
======================================================================*/
#include "saclib.h"

Word AFPINT(r,M,A,b)
       Word r,M,A,b;
{
       Word Ap,B,a,c,e,rp;
       /* hide Ap,a,e,rp; */

Step1:
       Ap = A;
       B = NIL;
       rp = r - 1;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         e = e + 1;
         if (r == 1)
           c = AFQ(M,a,AFFINT(e));
         else
           c = AFPAFQ(rp,M,a,AFFINT(e));
         B = COMP2(c,e,B);
         }
       while (!(Ap == NIL));
       if (b != 0)
         B = COMP2(b,0,B);
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
