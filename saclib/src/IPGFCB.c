/*======================================================================
                      a <- IPGFCB(r,A)

Integral polynomial Gelfond factor coefficient bound.

Inputs
  r : a BETA-digit, r >= 1.
  A : in Z[x_1,...,x_r].

Outputs
  a : in Z.  Let d be the sum norm of A and let n_i be
      the degree of A in x_i.  Let h_i = 2 n_i - 1 if
      n_i > 0, 0 otherwise.  Let h be the sum of the
      h_i.  Let h' = floor((h + 1)/2).  Then a =
      2^h' * d.
======================================================================*/
#include "saclib.h"

Word IPGFCB(r,A)
       Word r,A;
{
       Word V,a,h,n;

Step1: /* Compute. */
       a = IPSUMN(r,A);
       V = PDEGV(r,A);
       h = 0;
       do
         {
         ADV(V,&n,&V);
         h = h + MAX(0,2 * n - 1);
         }
       while (V != NIL);
       h = (h + 1) / 2;
       a = IMP2(a,h);

Return: /* Prepare for return. */
       return(a);
}
