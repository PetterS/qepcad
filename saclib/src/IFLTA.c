/*===========================================================================
			  IFLTA(A,B,b; Bp,n,s,o)

Integer from list to array.

Input
  A : integer.
  B : array of b words.
  b : positive BETA-digit.

Output
  Bp : (pointer to an) array representation of |A|.
       If n <= b  B is used for Bp; otherwise a new array is allocated.
  n  : the BETA-length of A, i.e. n = floor(log_BETA(|A|)) + 1 (if A /= 0);
       n = 0 if A = 0.
  s  : s = sign(A),
  o  : the BETA-order of A, i.e. the largest integer k such that BETA^k
       divides A (if A /= 0); o = 0 if A = 0.
===========================================================================*/
#include "saclib.h"

void IFLTA(A,B,b,Bp_,n_,s_,o_)
       Word A,*B,b,**Bp_,*n_,*s_,*o_;
{
       Word a,bp,i,n,o,s;
       Word Ap,*Bp,*Bpp;

Step1: /* Initialize Bp. */
       Bp = B;

Step2: /* A = 0. */
       if (A == 0) {
	  n = 0;
	  Bp[0] = 0;
	  s = 0;
	  o = 0;
	  goto Return; }

Step3: /* A non-zero BETA-digit. */
       if (A < BETA) {
	  n = 1;
	  if (A < 0) {
	     Bp[0] = -A;
	     s = -1; }
	  else {
	     Bp[0] = A;
	     s = 1; }
	  o = 0;
	  goto Return; }

Step4: /* Initialize for copying. */
       s = 0;
       n = 0;
       bp = b;
       Ap = A;

Step5: /* Copy trailing zeros, determine sign and BETA-order. */
       do {
	  a = FIRST(Ap);
	  if (a < 0) {
	     s = -1;
	     a = -a; }
	  else if (a > 0)
	     s = 1;
	  Bp[n] = a;
	  n = n + 1;
	  Ap = RED(Ap); }
       while (s == 0 && n < bp);
       o = n - 1;

Step6: /* Copy remaining digits. */
       if (s == 1)
	  while (Ap != NIL && n < bp) {
	     a = FIRST(Ap);
	     Bp[n] = a;
	     n = n + 1;
	     Ap = RED(Ap); }
       else
	  while (Ap != NIL && n < bp) {
	     a = -FIRST(Ap);
	     Bp[n] = a;
	     n = n + 1;
	     Ap = RED(Ap); }

Step7: /* Allocate sufficiently large array. Resume copying. */
       if (Ap != NIL) {
	  bp = n + LENGTH(Ap);
	  Bpp = GETARRAY(bp);
	  for (i = 0; i < n; i++)
	     Bpp[i] = Bp[i];
	  Bp = Bpp;
	  if (s == 0)
	     goto Step5;
	  else
	     goto Step6; }

Return: /* Prepare for return. */
        *Bp_ = Bp;
        *n_ = n;
        *o_ = o;
        *s_ = s;
        return;
}
