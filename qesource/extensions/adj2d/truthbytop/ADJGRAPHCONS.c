/*======================================================================

Adjacency graph constructor

======================================================================*/
#include "truthbytop.h"
#include "adj2D.h"

Word QepcadCls::ADJGRAPHCONS(Word D, Word P, Word J)
{
  Word G,L,S,s,c,Sp,i,j,cl,cm,cr,E,Lp;

Step1: /* Initialization. */
  G = NIL;

Step2: /* Graph vertices. L is a list of all vert's in descending lex order. */
  L = NIL;
  for(S = LELTI(D,CHILD); S != NIL; S = RED(S))
    for(s = LELTI(FIRST(S),CHILD); s != NIL; s = RED(s))
      L = COMP(FIRST(s),L);
  for(Lp = L; Lp != NIL; Lp = RED(Lp)) {
    c = FIRST(Lp);
    GADDVERTEX(LELTI(c,INDX),LELTI(c,TRUTH),&G); }

Step3: /* Add edges. */
  S = LELTI(D,CHILD);
  if (LENGTH(S) < 3)
    goto Return;
  
Step4: /* Edges between cells in the same stack. */
  for(Sp = S; Sp != NIL; Sp = RED(Sp)) {
    for(s = LELTI(FIRST(Sp),CHILD); s != NIL; s = RED(s)) {
      FIRST2(LELTI(FIRST(s),INDX),&i,&j);
      if (j % 2 == 0) {
	GADDEDGE(LIST2(LIST2(i,j+1),LIST2(i,j)),G);
	GADDEDGE(LIST2(LIST2(i,j-1),LIST2(i,j)),G); } } }
      
Step5: /* Edges between cells in different stacks. */
 do {
    ADV2(S,&cl,&cm,&S); cr = FIRST(S);
    for(E = C1DTOEDGELIST(cl,cm,cr,P,J); E != NIL; E = RED(E))
      GADDEDGE(FIRST(E),G);
  }while(RED(S) != NIL);

Return:
 return G;
}
