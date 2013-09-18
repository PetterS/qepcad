/*===========================================================================
			       RUPWRITE(A,v)

Rational univariate polynomial write.

Inputs
  A : in Q[x].
  v : a variable.

Side effects
  The rational polynomial A is written in the output stream in 
  recursive format using the variable v.
===========================================================================*/
#include "saclib.h"

void RUPWRITE(A,v)
       Word A,v;

{
       Word Ap,e,a,n1,p1;

Step1:  /* A = 0 */
       if (A == 0) {
	  CWRITE('0');
	  goto Return; }

Step2: /* Initialize. */
       Ap = A;
       n1 = RNINT(-1);
       p1 = RNINT(1);
       CWRITE('(');

Step3: /* Write coefficient */
       FIRST2(Ap,&e,&a);
       if (EQUAL(a,n1) && e > 0) {
	  CWRITE('-');
	  goto Step4; }
       if (EQUAL(a,p1) && e > 0) {
	  if (A != Ap)
	     CWRITE('+');
	  goto Step4; }
       if (RNSIGN(a) > 0 && A != Ap)
	  CWRITE('+');
       RNWRITE(a);

Step4: /* Write variable and exponent */
       if (e > 0)
	  VWRITE(v);
       if (e > 1) {
	  CWRITE('^');
	  AWRITE(e); }
       Ap = RED2(Ap);
       if (Ap != NIL)
	  goto Step3;

Step5: /* Close. */
       CWRITE(')');

Return: /* Prepare for return. */
       return;
}
