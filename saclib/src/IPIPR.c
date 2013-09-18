/*======================================================================
                      C <- IPIPR(r,D,A,B)

Integral polynomial mod ideal product.

Inputs
  D   :  a list (d1,...,d_{r-1}) of non-negative BETA-digits.
  r   : a BETA-digit, r >= 1.
  A,B : in Z[X1,...,X_{r-1},Y]/(X1^d1,...,X_{r-1}^d_{r-1}).

Outputs
  C   : in Z[X1,...,X_{r-1},Y]/(X1^d1,...,X_{r-1}^d_{r-1}),
        C = A * B.
======================================================================*/
#include "saclib.h"

Word IPIPR(r,D,A,B)
       Word r,D,A,B;
{
       Word Ap,As,Bs,C,C1,a,b,c,e,f,rp;
       /* hide a,b,e,f,rp; */

Step1: /* A or B zero. */
       if (A == 0 || B == 0)
         {
         C = 0;
         goto Return;
         }

Step2: /* General case. */
       As = CINV(A);
       Bs = CINV(B);
       C = 0;
       rp = r - 1;
       do
         {
         ADV2(Bs,&b,&f,&Bs);
         Ap = As;
         C1 = NIL;
         do
           {
           ADV2(Ap,&a,&e,&Ap);
           if (rp == 0)
             c = IPROD(a,b);
           else
             c = IPTPR(rp,D,a,b);
           if (c != 0)
             C1 = COMP2(e + f,c,C1);
           }
         while (!(Ap == NIL));
         if (C1 != NIL)
           C = IPSUM(r,C,C1);
         }
       while (!(Bs == NIL));

Return: /* Prepare for return. */
       return(C);
}
