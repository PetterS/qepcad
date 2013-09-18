/*======================================================================
                        SIQUOT(I,J,K)

Software interval quotient.  

Inputs
   I, J : software intervals of the same precision, say p, J not
          containing 0.
   K : an array of size (at least) 2 * p + 6.

Effect
   The smallest p-precision software interval containing I / J is
   computed and placed in K.
======================================================================*/
#include "saclib.h"

void SIQUOT(I,J,K)

       BDigit *I,*J,*K;
{
       BDigit p,q;

Step1: /* Get the precision. */
	p = I[2];
	q = p + 3;

Step2: /* J > 0. */
	if (J[1] > 0) {
	   if (I[1] > 0) {
	      FQUOT(I,J + q,-1,K);
	      FQUOT(I + q,J,+1,K + q); }
	   else if (I[q + 1] < 0) {
	      FQUOT(I,J,-1,K);
	      FQUOT(I + q,J + q,+1,K + q); }
	   else {
	      FQUOT(I,J,-1,K);
	      FQUOT(I + q,J,+1,K + q); }
	   goto Return; }

Step3: /* J < 0. */
	if (I[1] > 0) {
	   FQUOT(I + q,J,-1,K);
	   FQUOT(I,J + q,+1,K + q); }
	else if (I[q + 1] < 0) {
	   FQUOT(I + q,J,-1,K);
	   FQUOT(I,J + q,+1,K + q); }
	else {
	   FQUOT(I + q,J,-1,K);
	   FQUOT(I,J + q,+1,K + q) ; }

Return: /* Return. */
	return;
}
