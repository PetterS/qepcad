/*======================================================================
                      C <- IPTPR(r,D,A,B)

Integral polynomial truncated product.

Inputs
  D   : a list (d_1,...,d_r) of non-negative
        BETA-digits.
  r   : a BETA-digit, r >= 1.
  A,B : in Z[X1,...,Xr]/(X1^d1,...,Xr^dr).

Outputs
  C   : in Z[X1,...,Xr]/(X1^d1,...,Xr^dr),
        C = A * B.
======================================================================*/
#include "saclib.h"

Word IPTPR(r,D,A,B)
       Word r,D,A,B;
{
       Word Ap,As,Bs,C,Cp,Dp,a,b,c,e,f,n,rp;
       /* hide rp; */

Step1: /* A or B zero. */
       if (A == 0 || B == 0)
         {
         C = 0;
         goto Return;
         }

Step2: /* Prepare general case. */
       Dp = CINV(D);
       ADV(Dp,&n,&Dp);
       Dp = INV(Dp);
       C = 0;
       if (n == 0)
         goto Return;
       As = CINV(A);
       Bs = CINV(B);
       rp = r - 1;

Step3: /* Multiply. */
       while (Bs != NIL && SECOND(Bs) < n)
         {
         ADV2(Bs,&b,&f,&Bs);
         Ap = As;
         Cp = NIL;
         while (Ap != NIL && SECOND(Ap) < n - f)
           {
           ADV2(Ap,&a,&e,&Ap);
           if (rp == 0)
             c = IPROD(a,b);
           else
             c = IPTPR(rp,Dp,a,b);
           if (c != 0)
             Cp = COMP2(e + f,c,Cp);
           }
         if (Cp != NIL)
           C = IPSUM(r,C,Cp);
         }

Return: /* Prepare for return. */
       return(C);
}
