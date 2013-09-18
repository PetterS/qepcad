/*======================================================================
		   HIPIR(n,A,I,t,h,k; J,j)

Hardware interval polynomial interval refinement.

Inputs
   n : a positive beta-digit.
   A : a hardware interval polynomial of degree n containing
       a real polyunomial a(x) of degree n.
   I : an open  hardware isolating interval for a simple root
       \alpha of a(x).  I is of the form (a/2^h,(a+1)/2^h)
       for some integer h <= k.
   t : the trend of \alpha.
   h : the beta-integer described above.
   k : a beta-integer, k <= 52, such that 1/2^k is the width of
       a desired refined isolating interval for \alpha, h < k.

Outputs
   J : a hardware sub-interval of I that is an isolating
       interval for \alpha.  Either J is an open interval
       [b/2^j,(b+1)/2^j] for some integer j, h <= j <= k,
       the largest j that can be achieved using bisections 
       and interval arithmetic evaluations of A(x), or else
       J is a one-point interval [b/2^j,b/2^j].
   j : the beta-integer described above.

Remark
   HIPIR is floating-point overflow-underflow protected.
======================================================================*/
#include "saclib.h"

void HIPIR(n,A,I,t,h,k,J_,j_)
	BDigit n;
        interval A[],I;
	BDigit t,h,k;
	interval *J_;
	BDigit *j_;
{
	interval J;
	BDigit j,s;
	double a,b,c,w;
	Word ap;

Step1: /* Set FPCATCH. */
	FPCATCH();

Step2: /* Initialize width, w. */
	a = I.left;
	b = I.right;
	w = b - a;
	j = h;

Step3: /* Evaluate at midpoint. */
	c = a + w / 2;
	s = HIPFES(n,A,c);

Step4: /* Indeterminate sign. */
	if (s == NIL || FPCHECK() == 1) {
	   b = a + w;
	   goto Step8; }

Step5: /* Root found. */
	if (s == 0) {
	   a = c;
	   b = c;
	   j = j + 1;
	   goto Step8; }

Step6: /* Bisect interval. */
	if (s != t)
	   a = c;
	w = w / 2;
	j = j + 1;

Step7: /* Test for completion. */
	if (j < k)
	   goto Step3;
	b = a + w;

Step8: /* Compose J. */
	J.left = a;
	J.right = b;

Step9: /* Reset FPCATCH. */
	if (FPCHECK() == 1) {
	   j = h;
	   FPCATCH(); }

Return: /* Return J and j. */
	*J_ = J;
	*j_ = j;
	return;
}
