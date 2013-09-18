/*===========================================================================
			   ARIE(A,n,I)

Array remove indexed elements.

Inputs
  A : a garbage collected array containing n elements
      A_0, A_1, ..., A_{n-1}.
  n : a positive BETA-digit.
  I : a list (i_1,...,i_k) of BETA-digits, 0 <= i_1 < ... < i_k < n.

Side effects
  The array A is modified by removing the elements indexed by I.
  This is done by reindexing the elements of A so that the
  elements indexed by I are overwritten.
===========================================================================*/
#include "saclib.h"

void ARIE(A,n,I)
       Word A,n,I;
{
       Word A1,Ip,c,i,j,k;

Step1: /* Initialize. */
       Ip = I;
       c = 0;
       k = n;

Step2: /* Remove elements. */
       while (Ip != NIL) {
	  ADV(Ip,&i,&Ip);
	  i -= c;
	  c++;
	  k--;
	  for (j = i; j < k; j++) {
	     A1 = GCAGET(A,j+1);
	     GCASET(A,j,A1); } }

Return: /* Prepare for return. */
       return;
}
