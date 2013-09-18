/* P2 has simply to try to "fill up" the first element of V.
   Since P2 has been called, P1 has determined that there may
   be singularities or vertical tangents in v. */
#include "adj2D.h"

Word P2(Word x_l, Word x_r, Word U, Word V, Word W, Word v_l, Word B)
{
  Word v,m_v,As,Sol,t,w,S;

Step1: /* Initialize. */
  ADV(V,&v,&V);
  m_v = LELTI(v,AD2D_Mult);
  As = NIL;
  Sol = NIL;

Step5: /* */
  do {
    t = Mystery_f(x_l,x_r,m_v);

    if (t == 0) break;

    else if (t == 1) {
      S = P1(U,V,W,v_l,B);
      if (S != AD2D_FAIL)
	Sol = CCONC( ADD_2_SOL(As,S) , Sol ); }

    if (W == NIL) break;

    ADV(W,&w,&W);
    x_r = VECTOR_SUM(x_r,LELTI(w,AD2D_Mult));
    As = COMP( LIST2(LELTI(v,AD2D_Index),LELTI(w,AD2D_Index)) , As);
  } while(1);

Return: /* */
  if (Sol == NIL) Sol = AD2D_FAIL;
  return Sol;
}
