/*======================================================================
                      B <- AFPEMV(r,M,A,a)

Algebraic number field polynomial evaluation of main variable.

Inputs
  r : a BETA-integer, r >= 1.
  M : in Z[x], the minimal polynomial of an algebraic number alpha.
  A : an element of Q(alpha)[X1,...,Xr].
  a : in Q(alpha).  

Outputs
  B : in Q(alpha)[X1,...,X_{r-1}], B(X1,...,X_{r-1}) = A(X_1,...,X_{r-1},a).
======================================================================*/
#include "saclib.h"

Word AFPEMV(r,M,A,a)
       Word r,M,A,a;
{
       Word A2,Ap,B,e1,e2,i,rp;
       /* hide A2,Ap,e1,e2,i,rp; */

Step1: /* A = 0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* Apply Horner's method. */
       ADV2(A,&e1,&B,&Ap);
       rp = r - 1;
       while (Ap != NIL)
         {
         ADV2(Ap,&e2,&A2,&Ap);
         for (i = 1; i <= e1 - e2; i++) 
           if (rp == 0)
             B = AFPROD(M,a,B);
           else
             B = AFPAFP(rp,M,a,B);
         if (rp == 0)
           B = AFSUM(B,A2);
         else
           B = AFPSUM(rp,B,A2);
         e1 = e2;
         }
       for (i = 1; i <= e1; i++) 
         if (rp == 0)
           B = AFPROD(M,a,B);
         else
           B = AFPAFP(rp,M,a,B);

Return: /* Prepare for return. */
       return(B);
}
