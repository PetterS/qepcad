/*===========================================================================
		       LEXNEXTC(n,k,I; t)

Lexicographically next combination.

Inputs
  n : a postiive BETA-digit.
  k : a positive BETA-digit, 1 <= k <= n.
  I : an array of k indices, i.e, 0 <= I[0] < I[1] < ... < I[k-1] < n.

Output
  t : the last-changed index

Side effects
  I is modified to contain the lexicographically next index set.
  If I[k-i] = n-i, for i = 1,...,k, then I[0] is set to -1.
===========================================================================*/
#include "saclib.h"

void LEXNEXTC(n,k,I,t_)
       Word n,k,*I,*t_;
{
       Word c,i,j,t;

Step1: /* Get next index set. */
       i = 1;
       while (i <= k && I[k-i] == n-i)
	  i++;
       t = k - i;
       if (i > k)
	  I[0] = -1;
       else {
	  c = I[t] + 1;
	  I[t] = c;
	  for (j = k-i+1; j < k; j++)
	     I[j] = ++c; }

Return: /* Prepare for return. */
       *t_ = t;
       return;
}
