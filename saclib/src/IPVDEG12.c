/*===========================================================================
                         IPVDEG12(r,A; k,B)

Integral polynomial variable of degree 1 or 2.

Inputs
  r : a BETA-digit, the number of variables, r >= 1.
  A : in Z[x_1,...,x_r], A non-zero.

Outputs
  k : a BETA-digit.  If there is an i, 1 <= i < r, such that the degree
      of A in x_i is 1 or 2, then k = the largest such i.
      Otherwise, k = 0.
  B : in Z[x_1,...,x_r].  If k > 0 then
      B(x_1,...,x_r) = A(x_1,...,x_{k-1},x_{k+1},...,x_r,x_k),
      otherwise B = 0.
===========================================================================*/
#include "saclib.h"

void IPVDEG12(r,A, k_,B_)
       Word r,A, *k_,*B_;
{
       Word k,B,V,d;

Step1: /* Initialize. */
       k = B = 0;

Step2: /* Get degree vector. */
       V = PDEGV(r,A);

Step3: /* Search for minor variable of degree 1 or 2. */
       k = r;
       V = RED(V);
       while (V != NIL) {
	 ADV(V,&d,&V); k--;
	 if (d == 1 || d == 2) {
	   B = PICPV(r,A,k,r);
	   goto Return; } }
       k = 0;

Return: /* Prepare for return. */
       *k_ = k;
       *B_ = B;
       return;
}
