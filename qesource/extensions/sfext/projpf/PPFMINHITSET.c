/*======================================================================
                      S <- PPFMINHITSET(Q,P,i)

Pruned projection factor minimum hitting set.

Inputs
  Q  : A a set of subsets of the projection factors of level i.
       Each subset is assumed to be ordered by decreasing index.
  P  : The set of projection factors.
  i  : A level.

Outputs
  S  : A minimum cardinality hitting set if one exists. Otherwise 0.

======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

Word PPFMINHITSET(Word Q, Word P, Word i)
{
      Word Qp,T,q,r,Sp,S,Pp,p,Sp1,Sp2;

Step1: /* Make a list T which is equivalent to Q, except that a) it
	  lists the polynomial indices instead of the p.f. data structures,
	  and that b) the indices appear in increasing order. */
      Qp = Q;
      for(T = NIL; Qp != NIL; Qp = RED(Qp)) {
	q = FIRST(Qp);

Step2: /* Make a list of the idices of the polynomials in q.  The
	  list of indices will be in ascending order. */
	for(r = NIL; q != NIL; q = RED(q)) {
	  r = COMP(LELTI(LELTI(FIRST(q),PO_LABEL),3),r); }
	T = COMP(r,T); }

Step3: /* Find a minimum hitting set for T, then convert the resulting
	  subset of indices into the corresponding subset of P. */
      Sp1 = RSFHSP(T,&T);
      if (T == NIL) {
	Sp2 = NIL; 
if (PCVERBOSE) { SWRITE("RSFHSP alone sufficed.\n"); }
      } 
      else
	Sp2 = MINHITSET(T,-1);
      if (Sp2 == 0) 
	S = 0;
      else {
	Sp = CONC(Sp1,Sp2);
	Pp = LELTI(P,i);
	S = NIL;
	while (Pp != NIL) {
	  ADV(Pp,&p,&Pp);
	  if (MEMBER(LELTI(LELTI(p,PO_LABEL),3),Sp))
	    S = COMP(p,S); } }

Return: /* Return. */
      return (S);
}
