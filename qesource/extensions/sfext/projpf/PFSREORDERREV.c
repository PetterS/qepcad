/* Projection factor structure re-order reverse direction. */
/* PFS's A and B, where B is contained in A, reorder B so that
   the order of polynomials in B is the same as in A. */
#include "qepcad.h"

Word PFSREORDERREV(Word A, Word B)
{
      Word C,N,r,A_r,B_r,C_r;

Step1: /* Initialize. */
      C = NIL; N = IMIN(LENGTH(A),LENGTH(B));

Step2: /* Construct C level by level. */
      for(r = N; r > 0; r--) {
	A_r = LELTI(A,r);
	B_r = LELTI(B,r);
	for( C_r = NIL; A_r != NIL; A_r = RED(A_r))
	  if ( PFPIPFL(FIRST(A_r),B_r) )
	    C_r = COMP(FIRST(A_r),C_r);
	C = COMP(INV(C_r),C); }

Return:/* Return. */
      return (C);
}
