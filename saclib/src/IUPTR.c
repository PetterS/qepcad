/*======================================================================
                      B <- IUPTR(A,h)

Integral univariate polynomial translation.

Inputs
  A : in Z[X].
  h : in Z.

Outputs
  B : in Z[X], B(x) = A(x+h).
======================================================================*/
#include "saclib.h"

Word IUPTR(A,h)
       Word A,h;
{
       Word B,L,Lp,a,b,i,j,n;
       /* hide Lp,b,i,j,n; */

Step1: /* Degree zero. */
       n = PDEG(A);
       if (n == 0)
         {
         B = A;
         goto Return;
         }

Step2: /* Compute coefficient list. */
       L = PCL(A);

Step3: /* Apply synthetic division. */
       for (i = n; i >= 1; i--)
         {
         ADV(L,&a,&Lp);
         for (j = 1; j <= i; j++)
           {
           b = FIRST(Lp);
           a = IPROD(a,h);
           a = ISUM(a,b);
           SFIRST(Lp,a);
           Lp = RED(Lp);
           }
         }

Step4: /* Convert coefficient list to polynomial. */
       B = NIL;
       L = INV(L);
       for (i = 0; i <= n; i++)
         {
         ADV(L,&a,&L);
         if (a != 0)
           B = COMP2(i,a,B);
         }

Return: /* Prepare for return. */
       return(B);
}
