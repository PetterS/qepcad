/*======================================================================

Cell 1D to edge list.

Inputs
  cl, cm, cr : three consecutive cells in the CAD of 1-space, cm a
      section cell.
  P : the projection factor set.
  J : the projection polynomial set.

Output
  E : a list of all edges in the CAD's graph from vertices corresponding
      to cells in cl (cr) to vertices corresponding to cells in cm.
======================================================================*/
#include "truthbytop.h"
#include "adj2D.h"

Word QepcadCls::C1DTOEDGELIST(Word cl, Word cm, Word cr, Word P, Word J)
{
  Word E,L,i,Ll,Lr,l,a,b,t;

Step1: /* Initialize. */
  E = NIL;

Step2: /* Get adjacencies for (cl,cm) and (cr,cm). */
  L = FIRST(ADJ_2D_PART(cm,cl,cr,P,J));
  i = LAST(LELTI(cm,INDX));
  Ll = NIL; Lr = NIL;
  while(L != NIL) {
    ADV(L,&l,&L);
    FIRST2(l,&a,&b);
    if (FIRST(a) == i) {
      t = a; a = b; b = t; }
    if (FIRST(a) < i)
      Ll = COMP(LIST2(a,b),Ll); 
    else
      Lr = COMP(LIST2(a,b),Lr); }

Step3: /* Get edges from adjacency info. */
  E = CONC(ADJ2DITOEL(Ll,cl,cm),E);
  E = CONC(ADJ2DITOEL(Lr,cr,cm),E);
    
Return: /* Prepare to return. */
  return E;
}
