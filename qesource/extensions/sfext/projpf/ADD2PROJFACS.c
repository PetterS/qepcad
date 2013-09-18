/*======================================================================
                      ADD2PROJFACS(r,f,h,P)

Add to the projection factors.

Inputs
  r : a BETA-digit, r >= 1.
  f : in Z[X1,...,Xr], f non-constant, irreducible, primitive.  f need
      not be non-constant in Xr.
  h : a derivation history for f.
  P : the set of projection factors.

Side Effects
  P's constituents are altered. If f does not appear in P, then
  f is put in a qepcad data structure and appended to the projection
  factor list of the appropriate level.  If f does appear in P, then
  that qepcad polynomial data structure is altered to include h in its
  derivation history.
======================================================================*/
#include "qepcad.h"

void ADD2PROJFACS(Word r, Word f, Word h, Word P)
{
      Word P_r,Pp,t,pp,l,F,j;

/* Get f down to it's lowest non-constant level. */
      while ( PDEG(f) < 1 ) {
	f = PLDCF(f);
	r--; }

/* Is f already in P? */
      P_r = LELTI(P,r); t = 0;
      for(Pp = P_r; Pp != NIL; Pp = RED(Pp)) {
	pp = FIRST(Pp);
	if ( EQUAL(LELTI(pp,PO_POLY),f) ) {
	  t = 1; break; } }

/* Yes. */
      if (t) {
	if ( ISATOM(FIRST(LELTI(pp,PO_PARENT))) )
	  SLELTI(pp,PO_PARENT,LIST2(LELTI(pp,PO_PARENT),h));
	else
	  SLELTI(pp,PO_PARENT,CCONC(LELTI(pp,PO_PARENT),LIST1(h))); }

/* No. */
      else {
	j = THIRD(SECOND(LAST(P_r)));
	l = LIST3(LFS("P"),r,j + 1);
	F = MPOLY(f,l,LIST1(h),PO_OTHER,PO_KEEP);
	P_r = CCONC(P_r,LIST1(F));
	SLELTI(P,r,P_r); }

/* Return. */
      return;
    }
