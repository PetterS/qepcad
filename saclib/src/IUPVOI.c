/*======================================================================
                      v <- IUPVOI(A,I)

Integral univariate polynomial, variations for open interval.

Inputs
  A : in Z[X], non-zero.
  I : an open interval (a,b) with a and b binary rational numbers
      such that a < b.  Let T(z) be the transformation mapping
      the right half-plane onto the circle having I as diameter.
      Let B(x) = A(T(x)).

Outputs
  v : the number of sign variations in the coefficients of B.
======================================================================*/
#include "saclib.h"

Word IUPVOI(A,I)
       Word A,I;
{
       Word B,C,D,a,b,d,k,m,n,v;
       /* hide a,b,k,v; */

Step1: /* Compute m,n, and k such that a = m * 2^k,b = n * 2^k. */
       FIRST2(I,&a,&b);
       RNBCR(a,b,&m,&n,&k);

Step2: /* Transform and count variations. */
       if (k != 0)
         B = IUPBHT(A,k);
       else
         B = A;
       if (m != 0)
         C = IUPTR(B,m);
       else
         C = B;
       d = IDIF(n,m);
       D = IUPIHT(C,d);
       v = IPVCHT(D);

Return: /* Prepare for return. */
       return(v);
}
