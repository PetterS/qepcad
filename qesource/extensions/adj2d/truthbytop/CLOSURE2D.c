/*======================================================================

Truth value closure 2D.

This does true closure, meaning that a cell is only marked TRUE if a
neighbor of higher dimension is already marked true.  I think this is
assuming that we have a full CAD of 2-space.

10/17/01 - just copied TV2D
======================================================================*/
#include "truthbytop.h"
#include "adj2D.h"

void QepcadCls::CLOSURE2D(Word D, Word P, Word J)
{
  Word G,L,S,s,c,Sp,i,j,cl,cm,cr,E,Lp,L0,L1,L2,v,t;

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
    goto StepX;
  
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

Step6: /* Split cell list by dimension. */
 for(L0 = NIL, L1 = NIL, L2 = NIL, Lp = L; Lp != NIL; Lp = RED(Lp)) {
   c = LELTI(FIRST(Lp),INDX);
   switch(vert2dim(c)) {
   case 0: L0 = COMP(c,L0); break;
   case 1: L1 = COMP(c,L1); break;
   case 2: L2 = COMP(c,L2); break; } }

Step7: /* Propogate truth to lower dimensions. */
 for(Lp = CCONC(L2,L1); Lp != NIL; Lp = RED(Lp)) {
   v = FIRST(Lp);
   if (GVERTEXLABEL(v,G) == TRUE) {
     for(S = GSUCCLIST(v,G); S != NIL; S = RED(S))
       GNEWLABEL(FIRST(S),TRUE,G); } }

Step8: /* Propogate false to higher dimensions. */
 for(Lp = CCONC(L0,L1); Lp != NIL; Lp = RED(Lp)) {
   v = FIRST(Lp);
   if (GVERTEXLABEL(v,G) == FALSE) {
     for(S = GPREDLIST(v,G); S != NIL; S = RED(S))
       GNEWLABEL(FIRST(S),FALSE,G); } }

Step10: /* Assign new TV's to CAD. */
 for(Lp = L; Lp != NIL; Lp = RED(Lp)) {
   c = FIRST(Lp);
   t = GVERTEXLABEL(LELTI(c,INDX),G);
   if (t != UNDET) {
     SLELTI(c,TRUTH,t);
     SLELTI(c,HOWTV,TOPINF); } }

StepX: /* Assignments between 1D cells. 
  TVCLOSURE1D(D,P,J,3);
  CTVPROPUP(D,UNDET,GVNFV,TOPINF); */

Return: /* Prepare to return. */
  return;
}
 
