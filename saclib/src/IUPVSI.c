/*======================================================================
                      v <- IUPVSI(A,I)

Integral univariate polynomial, variations for standard interval.

Inputs
  A : in Z[X], non-zero.
  I : a standard open interval.  Let T(z) be the transformation mapping the
      right half-plane onto the circle having I as a diameter.
      Let B(x)=A(T(x)).

Outputs
  v : the number of sign variations in the coefficients of B.
======================================================================*/
#include "saclib.h"

Word IUPVSI(A,I)
       Word A,I;
{
       Word B,C,a,b,d,h,k,kp,v;
       /* hide a,b,k,kp,v; */

Step1: /* Compute h and k such that I=(a,b), a=h * 2^k and b=(h+1)*2^k. */
       FIRST2(I,&a,&b);
       d = RNDIF(b,a);
       RNFCL2(d,&k,&kp);
       if (a != 0)
         {
         h = RNQ(a,d);
         h = FIRST(h);
         }
       else
         h = 0;

Step2: /* Transform and count variations. */
       if (k != 0)
         B = IUPBHT(A,k);
       else
         B = A;
       if (h != 0)
         C = IUPTR(B,h);
       else
         C = B;
       v = IPVCHT(C);

Return: /* Prepare for return. */
       return(v);
}
