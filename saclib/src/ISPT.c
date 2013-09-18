/*===========================================================================
		       s <- ISPT(m,mp,F)

Integer selfridge primality test.  

Inputs
  m  : in Z. m >=3. 
  mp : m - 1.
  F  : a list (q_1,q_2,...,q_k), q_1 <= q_2 <= ... <= q_k, 
       of the prime factors of mp, 
       with mp equal to the product of the q_i.

Outputs
  s  : An attempt is made to find a root of unity modulo m of order m-1.
       If the existence of such a root is discovered then m is prime and
       s = 1.  If it is discovered that no such root exists then m is not
       a prime and s = -1.  Otherwise the primality of m remains uncertain
       and s = 0.
===========================================================================*/
#include "saclib.h"

Word ISPT(m,mp,F)
       Word m,mp,F;
{
       Word Fp,Pp,a,b,mpp,p,p1,q,q1,s;

Step1: /* Initialize outer loop. */
       Fp = F;
       q1 = 1;
       p1 = 1;

Step2: /* Get next divisor of m', if any. */
       do {
	  if (Fp == NIL) {
	     s = 1;
	     goto Return; }
	  ADV(Fp,&q,&Fp); }
       while (ICOMP(q,q1) <= 0);
       q1 = q;

Step3: /* Try successive small primes. */
       Pp = SPRIME;
       do {
	  if (Pp == NIL) {
	     s = 0;
	     goto Return; }
	  ADV(Pp,&p,&Pp);
	  if (p > p1) {
	     p1 = p;
	     a = MIEXP(m,p,mp);
	     if (a != 1) {
		s = -1;
		goto Return; } }
	  mpp = IEQ(mp,q);
	  b = MIEXP(m,p,mpp); }
       while (b == 1);

Step4: /* Return for next divisor. */
       goto Step2;

Return: /* Prepare for return. */
       return(s);
}
