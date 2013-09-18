/*======================================================================
                      J <- ANR(p,A,I)

Algebraic number refinement.

Inputs
   p : a positive beta integer, the precision of the software
       arithmetic to be employed.
   A : the minimal integral polynomial of an algebraic number
       \alpha.
   I : a logarithmic open standard isolating interval for \alpha.

Output
   J : a logarithmic open standard isolating interval for \alpha that
       is a subinterval of I, the smallest that could be obtained
       with precision p arithmetic.
======================================================================*/
#include "saclib.h"

Word ANR(p,A,I)
	BDigit p;
	Word A,I;
{
	BDigit *Ap,*bp,n,q1,q2,S,t;
	Word b,J;

Step1: /* Convert the minimal polynomial to a software interval
          polynomial. */
        n = PDEG(A);
        q1 = p + 3;
        q2 = q1 + q1;
        S = (n + 1) * q2 + 1;
        Ap = GETARRAY(S);
        IPSIP(A,p,Ap);

Step2: /* Compute the trend of \alpha. */
        b = SECOND(I);
        bp = GETARRAY(q1);
        t = LBRNFEC(b,p,bp);
	J = I;
	if (t == 0) {
           FREEARRAY(bp);
           goto Return; }
	 t = SIPES(Ap,bp);
        FREEARRAY(bp);
        if (t == NIL)
           goto Return;

Step3: /* Refine the isolating interval for \alpha. */
        J = SIPIR(Ap,I,t,- (p * ZETA));
        FREEARRAY(Ap);

Return: /* Return J. */
	return(J);
}
