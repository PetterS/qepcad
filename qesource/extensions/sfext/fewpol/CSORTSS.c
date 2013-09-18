/*======================================================================
                     CSORTSS(A,a,L)

Cell sort on a subset of the signiture.

Inputs
  A : An array of length a.  Each array element A[i] is an array of 
      Words, where each entry is -1,0, or 1.
  a : A non-negative BETA-Digit.
  L : A list of non-negative BETA-Digits such that each array A[i], for
      0 <= i < a, has length at least as great as the maximum element 
      of L.  No duplicate elements should appear in L.

Side effects
  The elements of A are sorted with respect to the entries whose indices
  are in L.  The sorting is lexicographic - order given by the order of
  appearence in L and, of course, -1 < 0 < 1.

======================================================================*/
#include "qepcad.h"

#ifndef BDCOMP
#define BDCOMP(a,b)       ((a) > (b) ? 1 : ((a) < (b) ? -1 : 0))
#endif

void CSORTSS(Word **A, Word a, Word L)
{
      Word i,j,l,s_i,s_j,*temp,**B,b,**C,c,**D,d,Lp;

      if ( (L == NIL) || (a <= 0)) goto Return;

Step1: /* Split list into A: elements with sign -1 on the first
	  element of L, and B: elements with sign 1 or 0 on FIRST(L). */
      i = 0; j = a - 1; l = FIRST(L);
      while (i < j) {
	s_i = A[i][l]; s_j = A[j][l];
	switch ( BDCOMP(s_i,s_j) ) {
	case (-1) : j--; break;
	case (1) : temp = A[i]; A[i] = A[j]; A[j] = temp; j--; break;
	case (0) : if (s_j == -1) i++; else j--; break; } }
      s_i = A[i][l];
      if (s_i == -1) i++;

Step2: /* Split list B into B: elements with sign 0 on FIRST(L), and
	  C: elements with sign 1 on FIRST(L). */
      B = A; b = i;
      C = B + b; i = 0; j = a - b - 1;
      while (i < j) {
	/* s_i, s_j : the signs of C[i] C[j] on l. */
	s_i = C[i][l]; s_j = C[j][l];
	switch ( BDCOMP(s_i,s_j) ) {
	case (-1) : i++; j--; break;
	case (1) : temp = C[i]; C[i] = C[j]; C[j] = temp; i++; j--; break;
	case (0) : if (s_j == 0) i++; else j--; break; } }
      /* s_i = sign of C[i] on l. */
      if (j != -1) {
	s_i = C[i][l];
	if (s_i == 0) i++; }
      c = i;
      D = C + c; d = a - b - c;

Step3: /* For each sublist, recurse sorting on RED(L). */
      Lp = RED(L);
      if ( Lp != NIL) {
	if (b > 1) CSORTSS(B,b,Lp);
	if (c > 1) CSORTSS(C,c,Lp);
	if (d > 1) CSORTSS(D,d,Lp); }
	
Return: /* Return. */
      return;
}
