/*======================================================================
                     d <- NEWDERIV(KT,P,Pb,Jb,Ph)

Choose a new derivative to add! Pb and Jb will be modified.

Inputs
  KT : the "derivative tree" structure returned by KCONST.
  P  : the "current" projection factor set.
  Pb : the set of all projection factors before the addition started.
  Jb : the set of all projection polynomials.
  Ph : the set of all projection factors used thus far, even if they've
       been removed.

Outputs
  d  : a qepcad projection factor data structure, a derivative which
       could potentially resolve conflicting pairs in the CAD defined
       by P.
======================================================================*/
#include "qepcad.h"
static Word DFS(Word o,Word KT,Word P);

Word NEWDERIV(Word KT, Word P, Word Pb, Word Jb, Word Ph)
{
      Word s,f,o,d,i,j,Q,q,dq,h,DQ,L,l,o_l;

Step1: /* Depth first search of KT until first vertex with out-nieghbor
list value 0 or first vertex which is not in Ph. */
      s = DFS(FIRST(FIRST(KT)),KT,Ph);
      FIRST2(s,&f,&o);
      FIRST2(RED(o),&i,&j);
      Q = POLFLAB(o,Pb);

Step2: /* If f is 1 then Q is not in P, so introduce it. */
      if (f == 1) {
	d = Q;
	goto Return; }

Step3: /* If f is 0 then we should add a derivative of Q. */
      q = LELTI(Q,PO_POLY);
      dq = IPDMV(i,q);
      h = LIST3(PO_DER,0,Q); /* The history for dq. */
      ADD2PROJPOLS(i,dq,h,Jb,Pb,&DQ,&L);
      while (L != NIL) {
	ADV(L,&l,&L);

/* Check to see if l is a level i factor which is new to Ph. */
	o_l = LELTI(l,PO_LABEL);
	if ( SECOND(o_l) == i && POLFLAB(o_l,Ph) == 0 ) {
	  d = l; goto Return; } }

Step4: /* It is possible that all factors of Q have been added before.
	  try another derivative then. */
      goto Step1;

Return:/* Return. */
      return (d);
}


static Word DFS(Word o, Word KT, Word P)
{
      Word i,P_i,KTp,v,o_v,L,r;

Step1: /* Is the pol with index o in P? If not tell it to add o. */
      i = SECOND(o);
      for(P_i = LELTI(P,i); P_i != NIL; P_i = RED(P_i)) {
	if ( EQUAL(o, LELTI(FIRST(P_i),PO_LABEL)) )
	  break; }
      if ( P_i == NIL ) {
	r = LIST2(1,o); goto Return; }

Step2: /* Get L, the list of out nieghbors of o. */
      for(KTp = KT; KTp != NIL; KTp = RED(KTp)) {
	v = FIRST(KTp);
	FIRST2(v,&o_v,&L);
	if ( EQUAL(o_v,o) )
	  break; }

Step3: /* Search the out nieghbors of o. */
      if ( L == NIL ) {
	r = 0; goto Return; }
      if ( L == 0 ) {
	r = LIST2(0,o); goto Return; }
      while ( 1 ) {
	r = DFS(FIRST(L),KT,P);
	if (r != 0) break;
	L = RED(L); }

Return:/* Return. */
      return (r);
}
