/*======================================================================
                      cp <- AD2DC_CONS(c,P)

Adj2D_Cell construct.

Inputs
  c : a cell of the 2D CAD.
  P : the projection factor set.

Outputs
  cp: an Adj2D_Cell structure representing c.
Note:  I'm assuming some things about SIGNPF and MULSUB.
       1) MULSUB is an ordered list, kept ordered just like SIGNPF.
       2) MULSUB concerns no projection factors outside of SIGHNPF.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"
#define nEw
#ifdef nEw

Word AD2DC_CONS(Word c, Word P)
{
       Word M,L,S,s,l,m,k,I,cp;

Step1: /* */
       M = NIL;
       L = LELTI(c,MULSUB);
       
       for(S = FIRST(LELTI(c,SIGNPF)); S != NIL; S = RED(S)) {
	 s = FIRST(S);
	 if (s != 0)
	   M = COMP(0,M);
	 else {
	   ADV(L,&l,&L);
	   FIRST2(l,&k,&m);
	   M = COMP(m,M); } }
       M = INV(M);

Return: /* Construct cp and return. */
  I = LELTI(c,INDX);
  cp = LIST2(I,M); 
  return cp;
}

#else

Word AD2DC_CONS(Word c, Word P)
{
  Word i,M,L,k,m,I,cp,n,p,T,LZ,P_2;

Step1: /* Construct empty multiplicity vector. */
  P_2 = LELTI(P,2);
  n = LENGTH(P_2);
  for(i = 0, M = NIL; i < n; i++)
    M = COMP(0,M);

  LZ = LPFZC(c,P);


Step2: /* Set non-zero entries from cells multiplicity list. */
  for(L = LELTI(c,MULSUB); L != NIL; L = RED(L)) {
    FIRST2(FIRST(L),&k,&m);

        /*-- Find p, the p.f. with index k. --*/
        for(T = LZ; T != NIL; T = RED(T)) {
          p = FIRST(T);
          if (k == THIRD(LELTI(p,PO_LABEL)))
	    break; }
        if (T == NIL) SWRITE("Failure in AD2DC_CONS\n");

    SLELTI(M,PFPIPFL(p,P_2),m); }

Return: /* Construct cp and return. */
  I = LELTI(c,INDX);
  cp = LIST2(I,M); 
  return cp;
}

#endif
