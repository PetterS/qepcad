/*======================================================================
                      C <- DMPPRD(r,m,A,B)

Dense modular polynomial product.

Inputs
  r : a BETA-digit, r >= 0, the number of variables.
  A , B : in Z/(m)[X1,...,Xr].
  m  : BETA-digit. 

Outputs
  C  : in Z/(m)[X1,...,Xr], the product of A and B.
======================================================================*/
#include "saclib.h"

Word DMPPRD(r,m,A,B)
       Word r,m,A,B;
{
       Word Ap,As,Bp,Bs,C,C1,a,b,c,e,f,i,j,n,rp;
       /* hide a,i,j,n,rp; */

Step1: /* A or B zero. */
       if (A == 0 || B == 0)
         {
         C = 0;
         goto Return;
         }

Step2: /* r=0. */
       if (r == 0)
         {
         C = MDPROD(m,A,B);
         goto Return;
         }

Step3: /* General case. */
       ADV(A,&e,&Ap);
       ADV(B,&f,&Bp);
       As = CINV(Ap);
       Bs = CINV(Bp);
       C = 0;
       rp = r - 1;
       for (i = 0; i <= f; i++)
         {
         C1 = NIL;
         for (j = 1; j <= i; j++)
           C1 = COMP(0,C1);
         Ap = As;
         ADV(Bs,&b,&Bs);
         for (j = 0; j <= e; j++)
           {
           ADV(Ap,&a,&Ap);
           if (rp == 0)
             c = MDPROD(m,a,b);
           else
             c = DMPPRD(rp,m,a,b);
           C1 = COMP(c,C1);
           }
         n = e + i;
         while (C1 != NIL && FIRST(C1) == 0)
           {
           n = n - 1;
           C1 = RED(C1);
           }
         if (C1 != NIL)
           {
           C1 = COMP(n,C1);
           C = DMPSUM(r,m,C1,C);
           }
         }

Return: /* Prepare for return. */
       return(C);
}
