/*===========================================================================
		      L <- MMAMNSB(p,n,M)

Medium modulus array matrix null space basis.

Inputs
  p : a medium prime.
  n : a positive BETA-digit.
  M : an n by n matrix of elements of Z/(p), represented by an array
      of arrays.

Output
  L : a list of vectors, represented by arrays, constituting a basis 
      for the space of all vectors A such that A * M = 0.
============================================================================*/
#include "saclib.h"

Word MMAMNSB(p,n,M)
       Word p,n,**M;
{
       Word *P,i,L,k,j,h,*B,a,b,c,d;

Step1: /* Initialize P, the pivot record,
	             L, the basis list and
		     k, the row looping index. */
       P = GETARRAY(n); 
       for (i = 0; i < n; i++)
	  P[i] = -1;
       L = NIL;
       k = 0;

Step2: /* Search for pivot column. */
       j = 0;
       while (j != n && (P[j] >= 0 || MATELT(M,k,j) == 0))
	  j++;

Step3: /* Produce basis vector. */
       if (j == n) {
	  B = GETARRAY(n); 
	  for (j = 0; j < n; j++) {  
	     if (j == k)
		B[j] = 1;
	     else { 
		h = 0;
		while (h != n && P[h] != j)
		   h++;
		if (h < n) 
		   B[j] = MATELT(M,k,h);
		else 
		   B[j] = 0; } }
	  L = PTRCOMP(B,L);
	  goto Step7; }

Step4: /* Update pivot record. */
       P[j] = k;

Step5: /* Multiply pivot column by the negative inverse of the pivot. */
       a = MATELT(M,k,j);
       b = p - MDINV(p,a); 
       MATELT(M,k,j) = p - 1; 
       for (i = k + 1; i < n; i++) {  
	  c = MATELT(M,i,j);
	  if (c != 0) { 
	     d = b * c; 
	     MATELT(M,i,j) = d % p; } }

Step6: /* Add multiples of pivot column to all other columns. */
       for (i = 0; i < n; i++)
	  if (i != j) {
	     a = MATELT(M,k,i);
	     if (a != 0) {
		MATELT(M,k,i) = 0;
		for (h = 0; h < n; h++) {
		   b = a * MATELT(M,h,j) + MATELT(M,h,i);
		   MATELT(M,h,i) = b % p; } } }

Step7: /* Increment row index and test for end. */
       k++; 
       if (k < n)
	  goto Step2;
       FREEARRAY(P);

Return: /* Prepare for return. */
       return(L);
}
