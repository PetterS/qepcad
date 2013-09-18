/* Add to projection polynomials. 
   J and P are modified. */
/*======================================================================
                      ADD2PROJPOLS(r,q,h,J,P;Q,L_Q)

Add to the projection polynomials.

Inputs
  r : a BETA-digit, r >= 1.
  q : in Z[X1,...,Xr], non-constant.
  h : a derivation history for f.
  J : the qepcad projection polynomials structure.
  P : the qepcad projection factors structure.

Outputs
  Q : the qepcad polynomial data structure for q.
  L_Q: a list of the qepcad polynomial data structures for the factors
      of q.

Side Effects
  J's constituents are altered. If q does not appear in J, then
  q is put in a qepcad data structure and appended to the projection
  factor list of the appropriate level.  If q does appear in J, then
  that qepcad polynomial data structure is altered to include h in its
  derivation history.  P's constituents are also altered to include the
  factors of q.
======================================================================*/
#include "qepcad.h"

void ADD2PROJPOLS(Word r, Word q, Word h, Word J, Word P, Word *Q_, Word *L_Q)
{
      Word J_r,t,Jp,jp,Q,l,s,c,L,foq,h_f,m,j;

      J_r = LELTI(J,r);

/* Is q already in J? */
      t = 0;
      for(Jp = J_r; Jp != NIL; Jp = RED(Jp)) {
	jp = FIRST(Jp);
	if ( EQUAL(LELTI(jp,PO_POLY),q) ) {
	  t = 1; break; } }
      if (t) {
	if ( ISATOM(FIRST(LELTI(jp,PO_PARENT))) )
	  SLELTI(jp,PO_PARENT,LIST2(LELTI(jp,PO_PARENT),h));
	else
	  SLELTI(jp,PO_PARENT,CCONC(LELTI(jp,PO_PARENT),LIST1(h)));
	Q = jp; }
      else {
  
/* Construct a qepcad polynomial data structure for q. */
	if (J_r == NIL)
	  j = 0;
	else
	  j = THIRD(SECOND(LAST(J_r)));
	l = LIST3(LFS("J"),r,j + 1);
	Q = MPOLY(q,l,LIST1(h),PO_OTHER,PO_KEEP);
	J_r = CCONC(J_r,LIST1(Q));
	SLELTI(J,r,J_r);

/* Add the factors of Q to the projection factors. */
	IPFAC(r,q,&s,&c,&L);
	while (L != NIL) {
	  FIRST2(FIRST(L),&m,&foq);
	  h_f = LIST3(PO_FAC,m,Q);
	  ADD2PROJFACS(r,foq,h_f,P);
	  L = RED(L); } }

/* Prepare to return. */
      *Q_ = Q;
      *L_Q = LIST_OF_FACS(Q,P);
      return;
}



