/*======================================================================
                      CADFPCADWI(D,P,S,I,Pb)

QEPCAD CAD data structure from pruned CAD data structure,where it's
guaranteed that the input factors are all in P.

Inputs
 D : is Pruned CAD cell structure.
 P : is the projection factor data structure that defines D.
 S : is the signiture for D's parent.
 I : is the index for D's parent.
 Pb: is the projection factor data structure that defines the signiture
     of the cells in the CAD or RCAD structure which are referenced by
     the cells of D.

Outputs
 Ds: is a QEPCAD CAD data structure representation of D. 

======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

Word CADFPCADWI(Word D, Word P, Word S, Word I, Word Pb)
{
      Word Db,Is,N,Sb,Pb_N,Ts,L,p,i,is,Q,Ms,C,Cs,Ds,Ss;
      Word Mb,mb;

Step1: /* Is D the root cell? */
      Db = LELTI(D,SC_REP);
      if (LELTI(D,SC_PAR) == NIL) {
	Is = NIL;
	Ss = NIL;
	Ms = NIL; }

      else {
Step2: /* D is not the root cell. */
	Is = CINV(COMP(LELTI(D,SC_INX),CINV(I)));
	N = LENGTH(Is);

Step3: /* Signiture & multiplicity information. */
	Sb = FIRST(LELTI(Db,SIGNPF));
	Pb_N = LELTI(Pb,N);
	Ts = NIL; Ms = NIL; is = 0;
 /* Loop over each level N polynomial in P. */
	for(L = CINV(LELTI(P,N)); L != NIL; L = RED(L)) {
	  p = FIRST(L); i = 1; is++;
 /* Set i so that p is the ith level N pol in Pb. */
	  i = PFPIPFL(p,Pb_N);
if (i == 0) { SWRITE("CAPFPCAD: Can't find the polynomial!\n"); }
	  Ts = COMP(LELTI(Sb,i),Ts);
 /* Set the multiplicity list if necessary */
	  for (Mb = LELTI(Db,MULSUB); Mb != NIL; Mb = RED(Mb)) {
	    mb = FIRST(Mb);
	    if (FIRST(mb) == i) {
	      Ms = COMP(LIST2(is,SECOND(mb)),Ms); } } }
	Ms = CINV(Ms);
	Ss = COMP(Ts,S); }

Step4: /* Children. */
	C = LELTI(D,SC_CDTV);
	if ( ISATOM(C) ) {
	  Cs = NIL; }
	else {
	  for(Cs = NIL; C != NIL; C = RED(C)) {
	    Cs = COMP(CADFPCADWI(FIRST(C),P,Ss,Is,Pb),Cs); }
	  Cs = CINV(Cs); }

Step5: /*  */
	Ds = LCOPY(Db);
	SLELTI(Ds,CHILD,Cs);
	SLELTI(Ds,INDX,Is);
	SLELTI(Ds,SIGNPF,Ss);
        SLELTI(Ds,HOWTV,PCELLHOWTV(D,Pb,P));
	SLELTI(Ds,MULSUB,Ms);

Return: /* Prepare to return. */
	return (Ds);
}
     
