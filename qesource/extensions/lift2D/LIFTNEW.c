/*
  Lifts over cell c in CAD D with projection factor set P.
  Return 1 if successfull, otherwise 0
  for the moment, it'll always work in software floats.
*/
#include "lift2d.h"

Word LIFT2DNEW(Word c, Word D, Word P)
{

Step1: /* Get coordinate info for c: M the min pol, I the interval */
  FIRST2(LELTI(c,SAMPLE),&M,&I);
  p = 2;
  J = IUPIIRSF(M,I,p);
  Mpf = FIRST(LPFZC(c,P)); /* from sfext/crcads/ */

Step2: /* Loop over */

}


/*======================================================================
Integral univariate polynomial isolating interval refine - using
Software Floats

Inputs:
  M : is the minimal polynomial for alpha
  I : is the isolating interval for alpha
  p : a positive beta integer, the precision of the software
    arithmetic to be employed.
Output
  J : an isolating interval for alpha, of the smallest width that
      could be achieved with precision p computation
======================================================================*/
Word IUPIIRSF(Word M, Word I, BDigit p)
{
  Word n, q1, q2, S, *Mp, b, *bp, t, J, L;  

Step1: /* Convert the minimal polynomial to a software interval
          polynomial. */
        n = PDEG(M);
        q1 = p + 3;
        q2 = q1 + q1;
        S = (n + 1) * q2 + 1;
        Mp = GETARRAY(S);
        IPSIP(M,p,Mp);

Step2: /* Compute the trend of \alpha. */
	b = SECOND(I);
	bp = GETARRAY(q1);
	t = LBRNFEC(b,p,bp);
	J = I;
        L = 0;
	if (t == 0) {
	   FREEARRAY(bp);
	   goto Return; }
	t = SIPES(Mp,bp);
	FREEARRAY(bp);
	if (t == NIL)
	   goto Return;

Step3: /* Refine the isolating interval for \alpha. this refines
	  as much as possible with precision p */
        J = SIPIR(Mp,I,t,- (p * ZETA));

Return: /* Prepare to return */
        FREEARRAY(Mp);
	return J;
}
