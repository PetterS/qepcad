/*===========================================================================
			     AFUPWRITE(A,vA,vc)

Algebraic number field univariate polynomial write.

Inputs
  A : in Q(alpha)[X], where the coefficients of A are represented 
      as (ai,Ai) where ai is in Q and Ai is in Z[x];
  vA: a variable for writing A;
  vc: a variable for writing the coefficients of A.

Side effects
  The polynomial A is written in the output stream in external 
  canonical form.
===========================================================================*/
#include "saclib.h"

void AFUPWRITE(A,vA,vc)
       Word A,vA,vc;
{
       Word Ap,e,a;

Step1: /* A = 0 */
       if (A == 0) {
	  CWRITE('0');
	  return; }
  
Step2: /* Initialize. */
       Ap = A;
       CWRITE('(');
  
Step3: /* Write coefficient */
       FIRST2(Ap,&e,&a);  
       if (Ap != A)
	  CWRITE('+');
       AFWRITE(a,vc);

Step4: /* Write variable and exponent */
       if (e > 0)
	  VWRITE(vA);
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
