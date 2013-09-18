/*======================================================================
                        SIPROD(I,J,K)

Software interval product.  

Inputs
   I, J : software intervals of the same precision, p.
   K : an array of size (at least) p + 3.

Effect
   The smallest p-precision software interval containing I * J is
   computed and placed in K.
======================================================================*/
#include "saclib.h"

void SIPROD(I,J,K)

       BDigit *I,*J,*K;
{
       BDigit p,q,s,*T;

Step1: /* Get the precision. */
	p = I[2];
	q = p + 3;

Step2: /* I >= 0. */
	if (I[1] >= 0) {
	   if (J[1] >= 0) {
	      FPROD(I,J,-1,K);
	      FPROD(I + q,J + q,+1,K + q); }
	   else if (J[q + 1] < 0) {
	      FPROD(I + q,J,-1,K);
	      FPROD(I,J + q,+1,K + q); }
           else {
	      FPROD(I + q,J,-1,K);
	      FPROD(I + q,J + q,+1,K + q); }
	   goto Return; }

Step3: /* I < 0. */
	if (I[q + 1] < 0) {
           if (J[1] >= 0) {
	      FPROD(I,J + q,-1,K);
	      FPROD(I + q,J,+1,K + q); }
           else if (J[q + 1] < 0) {
	      FPROD(I + q,J + q,-1,K);
	      FPROD(I,J,+1,K + q); }
           else {
	      FPROD(I,J + q,-1,K);
	      FPROD(I,J,+1,K + q); }
	   goto Return; }

Step4: /* I contains 0. */
	if (J[1] >= 0) {
	   FPROD(I,J + q,-1,K);
	   FPROD(I + q,J + q,+1,K + q); }
        else
           if (J[q + 1] < 0) {
	      FPROD(I + q,J,-1,K);
	      FPROD(I,J,+1,K + q); }
        else {
	   T = GETARRAY(q);
	   FPROD(I,J + q,-1,K);
	   FPROD(I + q,J,-1,T);
	   s = FCOMP(K,T);
	   if (s > 0)
	      FCOPY(T,K);
	   FPROD(I,J,+1,K + q);
	   FPROD(I + q,J + q, +1,T);
	   s = FCOMP(K + q,T);
	   if (s < 0)
	      FCOPY(T,K + q);
	   FREEARRAY(T); }

Return: /* Return. */
	return;
}
