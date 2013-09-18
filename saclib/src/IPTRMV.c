/*======================================================================
                      B <- IPTRMV(r,A,h)

Integral polynomial translation, main variable.

Inputs
   A : in Z[x_1,...,x_r].
   r : a BETA-digit, r >= 1, the number of variables.
   h : in Z.

Output
   B : in Z[X1,...,Xr], B = A(x_1,...,x_{r-1},x_r + h).
======================================================================*/
#include "saclib.h"

Word IPTRMV(r,A,h)
        Word r,A,h;
{
        Word Ap,B,B1,B2,a,ab,e,ep,i;

Step1: /* A = 0 or h = 0. */
       if (A == 0 || h == 0) {
          B = A;
          goto Return; }

Step2: /* General case. */
        ADV2(A,&e,&a,&Ap);
        B = LIST2(0,a);
        do {
           if (Ap == NIL)
              ep = 0;
           else
              ep = FIRST(Ap);
           for (i = 1; i <= e - ep; i++) {
              B1 = PMPMV(B,1);
              B2 = IPIP(r,h,B);
              B = IPSUM(r,B1,B2); }
           if (Ap == NIL)
              goto Return;
           ADV2(Ap,&e,&a,&Ap);
           ab = LIST2(0,a);
           B = IPSUM(r,B,ab); }
        while (1);

Return: /* Return B. */
        return(B);
}
