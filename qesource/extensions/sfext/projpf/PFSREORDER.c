/* Projection factor structure re-order. */
/* PFS's A and B, where B is contained in A, reorder A so that
   jth level i polynomial in B is also the jth level i polynomial
   in A. */
#include "qepcad.h"

Word PFSREORDER(Word A_, Word B_)
{
      Word A,a,B,b,C,c,c1,c2;

Step1: /* Initialize. */
      A = A_; B = B_; C = NIL;

Step2: /* Construct C level by level from A and B. */
      while ( A!= NIL && B != NIL ) {
	ADV(A,&a,&A);
	ADV(B,&b,&B);
	c1 = b;
	c2 = LPFSETMINUS(a,b);
	c = CCONC(c1,c2);
	C = COMP(c,C); }

Return: /* Invert C to get order right, and return. */
      C = CINV(C);
      return (C); 
}
