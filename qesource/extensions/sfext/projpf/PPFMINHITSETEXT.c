/*======================================================================
                      S <- PPFMINHITSET(Q,P,i)

Pruned projection factor minimum hitting set - extended.

Inputs
  Q  : A a set of subsets of the projection factors of level i.
       Each subset is assumed to be ordered by decreasing index.
  P  : The set of projection factors.
  i  : A level.

Outputs
  S  : A minimum cardinality hitting set if one exists. Otherwise 0.
  N  : A list of the "necessary" polynomials, i.e. those which appear
       as singletons in Q.

======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

Word PPFMINHITSETEXT(Word Q, Word P, Word i, Word *N_)
{
      Word Qp,T,q,r,Sp,S,Pp,p,N;

Step1: /* Make a list T which is equivalent to Q, except that a) it
	  lists the polynomial indices instead of the p.f. data structures,
	  and that b) the indices appear in increasing order. */
      Qp = Q; N = NIL;
      for(T = NIL; Qp != NIL; Qp = RED(Qp)) {
	q = FIRST(Qp);

StepE: /* If q is of length 1, add its contents to N. */
	if (LENGTH(q) == 1)
	  N =  PFSUNION(q,N);

Step2: /* Make a list of the indices of the polynomials in q.  The
	  list of indices will be in ascending order. */
	for(r = NIL; q != NIL; q = RED(q)) {
	  r = COMP(LELTI(LELTI(FIRST(q),PO_LABEL),3),r); }
	T = COMP(r,T); }

Step3: /* Find a minimum hitting set for T, then convert the resulting
	  subset of indices into the corresponding subset of P. */
      Sp = MINHITSET(T,-1);
      if (Sp == 0) S = 0;
      else {
	Pp = LELTI(P,i);
	S = NIL;
	while (Pp != NIL) {
	  ADV(Pp,&p,&Pp);
	  if (MEMBER(LELTI(LELTI(p,PO_LABEL),3),Sp))
	    S = COMP(p,S); } }

Return: /* Return. */
      *N_ = N;
      return (S);
}
