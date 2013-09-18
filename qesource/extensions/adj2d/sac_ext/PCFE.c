/*======================================================================
                       c <- PCFE(A,k)

Polynomial coefficient from exponent.

Inputs
   A : a univariate integral polynomial.
   k : an integer

Outputs                          
   c : the coefficient of the term of degree k, an element of the
       base domain.
======================================================================*/
#include "sac_ext.h"

Word PCFE(Word A, Word k)
{
       Word c,i;

Step1: /* Special case A = 0. */
       if (A == 0) {
	 c = 0;
	 goto Return;
       }
       
Step2: /* Find 1st term of degree not greater than k. */
       do {
	 ADV2(A,&i,&c,&A);
       } while( i > k && A != NIL);

Step3: /* if degree of term not equal k, coefficient is 0. */
       if (i != k)
	 c = 0;

Return: /* Prepare to return. */
       return c;
}
