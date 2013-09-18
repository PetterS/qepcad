/*======================================================================
                      v <- HIPSV(n,A)

Hardware interval polynomial sign variations.

Inputs
   n : a beta-digit, n >= 0.
   A : a hardware interval polynomial polynomial of degree n.

Output
   v : a beta-digit indicating the number of sign variations in A,
       as follows.  If v = 0 or v = 1, the number of variations is v.
       If v = 2, the number of variations is at least 2.  Otherwise
       v = -1, indicating that the program could not determine
       which of these three possibilities is the case.
======================================================================*/
#include "saclib.h"

Word HIPSV(n,A)
	BDigit n;
	interval *A;
{
	BDigit h,i,k,s,t,v;

Step1: /* Initialize. */
	h = 0;
	k = 0;
	i = 0;
	s = HISIGN(A[0]);
	if (s == 0) {
	   i = 1;
	   s = HISIGN(A[1]); }

Step2: /* Process one coefficient. */
	i = i + 1;
	if (i > n)
	   goto Step3;
	t = HISIGN(A[i]);
	if (t == 0)
	   goto Step2;
	if (t != NIL) {
	   if (s == t)
	      goto Step2;
	   if (s == -t)
	      h = h + 1; }
	k = k + 1;
	s = t;

Step3: /* Check for termination. */
	if (h >= 2) {
	   v = 2;
	   goto Return; }
	if (i < n)
	   goto Step2;
	if (h == k)
	   v = h;
	else
	   v = -1;

Return: /* Return v. */
	return(v);
}
