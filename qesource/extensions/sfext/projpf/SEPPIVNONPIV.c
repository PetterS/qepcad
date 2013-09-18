/* Separate pivot from no-pivot polynomials. */
/* Note:  GVPIVOT is list of lists of labels! */
#include "qepcad.h"

void QepcadCls::SEPPIVNONPIV(Word Q_k, Word k, Word *PP_, Word *NP_)
{
      Word C,NP,PP,L,l;

Step1: /* No pivot at this level. */
      if ((!ISLIST(GVPIVOT)) || (LENGTH(GVPIVOT) < k) || 
	  ((C = LELTI(GVPIVOT,k)) == NIL)) {
	PP = Q_k; NP = NIL; goto Return; }

Step2: /* There is a pivot at this level. */
	  NP = NIL; PP = NIL; L = Q_k;
	  while (L != NIL) {
	    ADV(L,&l,&L);
	    if ( !MEMBER(LELTI(l,PO_LABEL),C) )
	      NP = COMP(l,NP);
	    else
	      PP = COMP(l,PP); }

Return:/* Return. */
	  *PP_ = PP;
	  *NP_ = NP;
	  return;
}
