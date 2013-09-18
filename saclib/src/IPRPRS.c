/*===========================================================================
			     S <- IPRPRS(r,A,B)

Integral polynomial reduced polynomial remainder sequence.

Inputs
   r : a BETA-digit, r > 0.
 A,B : in Z[x_1,...,x_r], A and non-zero, deg(A) >= deg(B).

Outputs
  S  : a list of elements in Z[x_1,...,x_r], 
       the reduced polynomial remainder sequence of A and B.
===========================================================================*/
#include "saclib.h"

Word IPRPRS(r,A,B)
       Word r,A,B;
{
       Word A1,A2,A3,S,a1,as1,d,i,n1,n2;

Step1: /* Compute. */
       A1 = A;
       A2 = B;
       S = LIST2(A2,A1);
       d = -1;
       do {
	  A3 = IPPSR(r,A1,A2);
	  if (A3 == 0) {
	     S = INV(S);
	     goto Return; }
	  if (d >= 0) {
	     a1 = PLDCF(A1);
	     as1 = a1;
	     for (i = 1; i <= d; i++)
		if (r == 1)
		   as1 = IPROD(as1,a1);
		else
		   as1 = IPPROD(r - 1,as1,a1);
	     as1 = PMON(as1,0);
	     A3 = IPEQ(r,A3,as1); }
	  S = COMP(A3,S);
	  n1 = PDEG(A1);
	  n2 = PDEG(A2);
	  d = n1 - n2;
	  A1 = A2;
	  A2 = A3; }
       while (1);

Return: /* Prepare for return. */
       return(S);
}
