/*======================================================================

Boundary 2D.

Takes current 2D set and sets truth values to define the boundary of
the set.
I think this is assuming that we have a full CAD of 2-space.

10/18/01 - just copied CLOSURE2D
======================================================================*/
#include "truthbytop.h"
#include "adj2D.h"

void QepcadCls::BOUNDARY2D(Word D, Word P, Word J)
{
  Word G,L,S,s,c,Sp,i,j,cl,cm,cr,E,Lp,L0,L1,L2,v,t,tc,fc,LH,LI0;

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

 /* Find isolated true L0 cells */
 LI0 = NIL;
 for(Lp = L0; Lp != NIL; Lp = RED(Lp)) {
   v = FIRST(Lp);
   if (GVERTEXLABEL(v,G) != TRUE)
     continue;
   LH = NIL;
   for(S = GPREDLIST(v,G), tc = 0, fc = 0; 
       S != NIL && GVERTEXLABEL(FIRST(S),G) == FALSE; S = RED(S))
     LH = CCONC(GPREDLIST(FIRST(S),G),LH);
   if (S == NIL) {
     for(;LH != NIL && GVERTEXLABEL(FIRST(LH),G) == FALSE; LH = RED(LH));
     if (LH == NIL)
       LI0 = COMP(v,LI0);
   } }

 /* Set L1 cells to TRUE IFF they have both true & false predecessors, 
    or they are already true and all predecessors are false */
 for(Lp = L1; Lp != NIL; Lp = RED(Lp)) {
   v = FIRST(Lp);
   for(S = GPREDLIST(v,G), tc = 0, fc = 0; S != NIL; S = RED(S)) {
     if (GVERTEXLABEL(FIRST(S),G) == TRUE)
       tc++;
     else
       fc++; }
   if (tc > 0 && fc > 0 || GVERTEXLABEL(v,G) == TRUE && tc == 0)
     GNEWLABEL(v,TRUE,G);
   else
     GNEWLABEL(v,FALSE,G); }
   
 /* Set L2 cells to FALSE */
 for(Lp = L2; Lp != NIL; Lp = RED(Lp))
   GNEWLABEL(FIRST(Lp),FALSE,G);


 /* Set L0 cells to TRUE IFF they have a true predecessor */
 for(Lp = L0; Lp != NIL; Lp = RED(Lp)) {
   v = FIRST(Lp);
   for(S = GPREDLIST(v,G), tc = 0, fc = 0; S != NIL; S = RED(S)) {
     if (GVERTEXLABEL(FIRST(S),G) == TRUE)
       tc++;
     else
       fc++; }
   if (tc > 0)
     GNEWLABEL(v,TRUE,G);
   else
     GNEWLABEL(v,FALSE,G); }
 
 /* Set all the isolated L0 cells to true */
 for(Lp = LI0; Lp != NIL; Lp = RED(Lp))
   GNEWLABEL(FIRST(Lp),TRUE,G);

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
 
