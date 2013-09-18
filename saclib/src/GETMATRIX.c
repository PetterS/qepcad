/*===========================================================================
		      A <- GETMATRIX(m,n)

Get matrix.

Input
  m : a positive integer.
  n : a positive integer.

Output
  A : a pointer to a two-dimensional array of m*n Words,
      i.e., A points to an m-dimensional array of n-dimensional arrays.
      The array is not subject to garbage collection.
===========================================================================*/
#include <stdio.h>
#include "saclib.h"

Word **GETMATRIX(m,n)
       Word m,n;
{
       Word **p,i;

Step1: /* Allocate memory for array. */
       p = (Word **)malloc(m*sizeof(Word *));
       if (p == NULL)
	  FAIL("GETMATRIX","Out of memory.");
       for (i = 0; i < m; i++) {
	  p[i] = GETARRAY(n);
	  if (p[i] == NULL) 
	     FAIL("GETMATRIX","Out of memory."); }

Return: /* Prepare for return. */
       return(p);
}
