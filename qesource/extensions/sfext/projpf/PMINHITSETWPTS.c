/*======================================================================
                      S <- PMINHITSETWPTS(Q,P,H)

Projection factor minimum hitting set with preference to a given subset.

Inputs
  Q  : A a set of subsets of the projection factors.
  P  : The projection factors.
  H  : A subset of the projection factors.
Outputs
  S  : A minimum wieghted hitting set if one exists. Otherwise 0.
       The wieghting scheme is simply that each polynomial in H
       has wieght 1, and each polynomial not in H has wieght |H| + 1.
Note : Both Q and H are lists whose elements are projection factors.
       P, on the other hand, is a list whose ith element is a list of
       level i projection factors. 
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

Word PMINHITSETWPTS(Word Q, Word P, Word H)
{
      Word Ps,Pp,l_H,T,Qp,q,q_H,q_NH,p,a,b,Sp,Spp,i,S;

      Ps = NIL; T = NIL;
      for(Pp = P; Pp != NIL; Pp = RED(Pp)) Ps = CCONC(Ps,FIRST(Pp));
      l_H = LENGTH(H);

Step1: /* Make a list T which is equivalent to Q, except that it
          lists the polynomial indices instead of the p.f. data structs. */
      for(Qp = Q; Qp != NIL; Qp = RED(Qp)) {
        q = FIRST(Qp);

Step2: /* Make a list of the indices of the polynomials in q.  */
	q_H = NIL; q_NH = NIL;
	while (q != NIL) {
	  ADV(q,&p,&q);
	  a = PFPIPFL(p,Ps);
	  b = 1; 
	  if ( ! PFPIPFL(p,H) ) {
	    b += l_H;
	    q_NH = COMP(LIST2(a,b),q_NH); }
	  else
	    q_H = COMP(LIST2(a,b),q_H); }
        T = COMP(CONC(q_H,q_NH),T); }

Step3: /* Find a minimum hitting set for T, then convert the resulting
          subset of indices into the corresponding subset of P. */
      Sp = MINWEIGHTHITSET(T,-1);
      if (Sp == 0) S = 0;
      else {
        S = NIL;
	for(Spp = NIL; Sp != NIL; Sp = RED(Sp)) {
	  Spp = COMP(FIRST(FIRST(Sp)),Spp); }
	for(i = 1; Ps != NIL; i++) {
          ADV(Ps,&p,&Ps);
          if ( MEMBER(i,Spp) )
            S = COMP(p,S); } }

Return: /* Return. */
      return (S);
}
