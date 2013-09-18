/*
This considers only a single stack and that from the left.
This particular function deals positive asymptotes.
*/
#include "adj2D.h"
void sa_send(const char* S);

Word ADJ_2D1P3(Word U, Word w_l, Word B)
{
  Word Sol,u,I,w_u,r,c1,c2;

  /*sa_send("[");*/

Step1: /* Initialization. */
  if (U == NIL) {
    Sol = LIST1(NIL);
    goto Return; }

  ADV(U,&u,&U);
  FIRST2(u,&I,&r);
  Sol = LIST1(LIST2(I,LIST2(B,AD2D_Infy)));

  while(U != NIL) {
    ADV(U,&u,&U);
    FIRST2(u,&I,&w_u);
    r = VECTOR_SUM(r,w_u);
    Sol = COMP(LIST2(I,LIST2(B,AD2D_Infy)),Sol); }
  while(r != NIL) {
    ADV(r,&c1,&r);
    ADV(w_l,&c2,&w_l);
    if (c1 != 0 && c2 == 0) {
      Sol = AD2D_FAIL;
      goto Return; } }
  Sol = LIST1(Sol);

Return: /* Prepare to return. */
  /*sa_send("]");*/
  return Sol;
}
