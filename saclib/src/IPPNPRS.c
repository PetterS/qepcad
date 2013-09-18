/*===========================================================================
			     S <- IPPNPRS(A,B)

Integral polynomial primitive negative polynomial remainder sequence.

Inputs
 A,B : in Z[x], deg(A) > 0, deg(A) >= deg(B).

Outputs
  L : a list (A_1,A_2,A_3,...,A_r), where A_i is an element of Z[x] and
      A_1 = A and A_2 = B.  L is the primitive Sturm sequence of A and B.
===========================================================================*/
#include "saclib.h"

Word IPPNPRS(A,B)
       Word A,B;
{
       Word L,A1,A2,A3,n1,n2,n3;

Step1: /* Initialize. */
       A1 = A;
       A2 = B;
       n1 = PDEG(A1);
       n2 = PDEG(A2);
       L = LIST2(A2,A1);

Step2: /* Compute pseudo-remainder. */
       A3 = IPPSR(1,A1,A2);
       if (A3 == 0) {
	  L = INV(L);
	  goto Return; }

Step3: /* Make primitive and negative and update. */
       A3 = IPIPP(1,A3);
       n3 = PDEG(A3);
       if (IPSIGN(1,A2) > 0 || EVEN(n1 - n2 + 1))
	  A3 = IPNEG(1,A3);
       L = COMP(A3,L);
       A1 = A2;
       n1 = n2;
       A2 = A3;
       n2 = n3;
       goto Step2;

Return: /* Prepare for return. */
       return(L);
}
