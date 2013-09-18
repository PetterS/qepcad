/*======================================================================

Truth value closure (closure of open set) 2D.

======================================================================*/
#include "truthbytop.h"
#include "adj2D.h"

void QepcadCls::TVCCOOS2D(Word D, Word P, Word J)
{
  Word S,cl,cm,cr,L,i,Ll,Lr,l,a,b;

Step1: /* Assign truth values via closure between cells in same stack. */
  TVCLOSURE1DS(D,P,J,GVNFV,3);

Step2: /* Special case: none or one cell in 1-space. */
  S = LELTI(D,CHILD);
  if (S == NIL || LENGTH(S) == 1)
    goto Return;

Step3: /*  */
  do {
    ADV2(S,&cl,&cm,&S); cr = FIRST(S);
    L = FIRST(ADJ_2D_PART(cm,cl,cr,P,J));
    i = LAST(LELTI(cm,INDX));
    Ll = NIL; Lr = NIL;
    while(L != NIL) {
      ADV(L,&l,&L);
      FIRST2(l,&a,&b);
      if (FIRST(a) < i || FIRST(b) < i)
	Ll = COMP(l,Ll);
      else
	Lr = COMP(l,Lr); }
    TVCCOSBSVAI(cm,cl,Ll);
    TVCCOSBSVAI(cm,cr,Lr);
  }while(RED(S) != NIL);

Step4: /* Assignments between 1D cells. */
  TVCLOSURE1D(D,P,J,GVNFV,3);
  CTVPROPUP(D,UNDET,GVNFV,TOPINF);

Return: /* Prepare to return. */
  return;
}

