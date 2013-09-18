/*=========================================================================
                           IRLSA(A,n,k; n')

Integer restricted left shift in array.

Inputs
   A : An array of size at least n + 1, containing a non-negative 
       integer A' of length n.
   n : a non-negative BETA-digit.
   k : a non-negative BETA-digit, k < ZETA.

Output
   n' : The length of the integer 2^k * A'.

Effect : The integer A' is replaced in A by the integer 2^k * A'.
=========================================================================*/
#include "saclib.h"

void IRLSA(A,n,k, np_)
	Word *A,n,k, *np_;
{
	Word a,ap,i,kp,np;

Step1: /* n = 0 or k = 0. */
	if (n == 0 || k == 0) {
           np = n;
	   goto Return; }

Step2: /* Shift loop. */
	kp = ZETA - k;
	ap = 0;
	for (i = 0; i < n; i++) {
	   a = A[i];
	   A[i] = ((a << k) & BETA1) | ap;
	   ap = a >> kp; }

Step3: /* Last carry. */
	if (ap != 0) {
	   A[n] = ap;
	   np = n + 1; }
        else
           np = n;

Return: /* Return n'. */
	*np_ = np;
}
