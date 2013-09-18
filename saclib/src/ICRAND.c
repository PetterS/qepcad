/*======================================================================
                      A <- ICRAND(n,s)

Integer, controlled random.

Inputs
  n : a positive BETA-integer.  
  s : 1 or -1, a BETA-integer.

Outputs
  A : a random integer whose bit length is exactly n and
      whose sign is s.
======================================================================*/
#include "saclib.h"

Word ICRAND(n,s)
       Word n,s;
{
       Word A,a,i,q,r;

Step1: /* Compute high-order BETA-digit. */
	QREM(n,ZETA,&q,&r);
	if (r == 0) {
           q = q - 1;
           r = ZETA; }
	a = ABS(DRAN());
	a = a >> (ZETA - r);
	a = a | (01 << (r - 1));
	if (s < 0)
	   a = - a;
	if (q == 0) {
           A = a;
           goto Return; }
	A = LIST1(a);

Step2: /* Compute remaining digits. */
	for (i = 1; i <= q; i++) {
           a = ABS(DRAN());
           if (s < 0)
              a = -a;
           A = COMP(a,A); }

Return: /* Prepare for return. */
       return(A);
}
