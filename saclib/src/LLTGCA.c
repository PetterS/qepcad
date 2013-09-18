/*===========================================================================
			 LLTGCA(L; A,n)

List of lists to garbage-collected array.

Inputs
  L : a list, some of whose elements are lists.

Outputs
  n : the length of L.
  A : GCA handle for an array of size n containing the elements 
      of L in the same order as in L.
===========================================================================*/
#include "saclib.h"

void LLTGCA(L,A_,n_)
       Word L,*A_,*n_;
{
       Word A,n,*Ab,Lp,i,A1;

Step1: /* Compute the length of L. */
       n = LENGTH(L);

Step2: /* Get an array handle. */
       A = GCAMALLOC(n,GC_CHECK);

Step3: /* Copy the elements into the array. */
       Ab = GCA2PTR(A);
       Lp = L;
       for (i = 0; i < n; i++) { 
	  A1 = FIRST(Lp); 
	  Ab[i] = A1; 
	  Lp = RED(Lp); }

Return: /* Prepare for return. */
       *n_ = n;
       *A_ = A;
       return;
}
