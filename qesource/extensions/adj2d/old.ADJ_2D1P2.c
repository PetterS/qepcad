/*
This considers only a single stack and that from the left.
This particular function deals non-asymptotes.
 */
#include "adj2D.h"

Word ADJ_2D1P2(Word U, Word V, Word w_l, Word B)
{
  Word Sol,S,v,J,w_v,u,w_u,I,Solp,t;

Step1: /* V empty. */
  if (V == NIL) {
    Sol = ADJ_2D1P3(U,w_l);
    goto Return; }

Step2: /* */
  S = NIL;
  Sol = NIL;
  ADV(V,&v,&V);
  FIRST2(v,&J,&w_v);
  t = 0;
  do {
    while(VECTOR_ODD_E(w_v) || t) {
      t = 0;
      if (U == NIL) goto Return;
      ADV(U,&u,&U);
      FIRST2(u,&I,&w_u);
      if (! VECTOR_LTEQ(w_u,w_v) ) goto Return;
      S = COMP(LIST2(I,J),S);
      w_v = VECTOR_SUM(w_v,VECTOR_NEG(w_u)); }
    Solp = ADJ_2D1P2(U,V,w_l,B);
    if (Solp != AD2D_FAIL)
      Sol = CCONC(ADD_2_SOL(S,Solp),Sol);
    t = 1;
  } while(SUM_NORM_SP(w_v) != 0);
  if (Sol == NIL)
    Sol = AD2D_FAIL;

Return: /* Prepare to return. */
  return Sol;
}
