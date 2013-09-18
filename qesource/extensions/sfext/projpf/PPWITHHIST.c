/*  Projection polynomial with given history. */
#include "qepcad.h"

Word PPWITHHIST(Word J, Word r, Word h)
{
      Word x,y,p,J_r,q,d,A,t;

Step1: /* Initialize. */
      FIRST2(h,&x,&y);
      p = 0;

Step2: /* Search loop. */
      for(J_r = LELTI(J,r); J_r != NIL; J_r = RED(J_r)) {
	q = FIRST(J_r);
	for(d = LELTI(q,PO_PARENT); d != NIL; d = RED(d)) {
	  A = FIRST(d);
	  if ( x == FIRST(A) && y == SECOND(A)) {
	    switch ( x ) {
	    case (PO_DIS) :
	      t = (LELTI(FOURTH(h),PO_LABEL) == LELTI(FOURTH(A),PO_LABEL));
	      break;
	    case (PO_LCO) :
	    case (PO_TCO) :
	    case (PO_FAC) :
	    case (PO_DER) : 
	      t = (LELTI(THIRD(h),PO_LABEL) == LELTI(THIRD(A),PO_LABEL)); 
	      break;
	    case (PO_RES) : 
	      t = ((LELTI(LELTI(h,4),PO_LABEL) == LELTI(LELTI(A,4),PO_LABEL)) && 
		   ((LELTI(LELTI(h,6),PO_LABEL) == LELTI(LELTI(A,6),PO_LABEL))))
	      ||( (LELTI(LELTI(h,4),PO_LABEL) == LELTI(LELTI(A,6),PO_LABEL)) && 
		 ((LELTI(LELTI(h,6),PO_LABEL) == LELTI(LELTI(A,4),PO_LABEL))));
	      break; }
	    if (t) {
	      p = q; goto Return; } } } }
						 
Return:/* Return. */
      return (p);
}








