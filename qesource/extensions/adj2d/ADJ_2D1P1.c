/*
This considers only a single stack and that from the left.
This particular function deals negative asymptotes.
*/
#include "adj2D.h"
void sa_send(const char* S);

Word ADJ_2D1P1(Word U, Word V, Word w_l, Word B)
{
  Word Sol,S,Solp,u,I,w_u;

  /*sa_send("[");*/

Step1: /* Initialization. */
  if (U == NIL) {
    Sol = LIST1(NIL);
    goto Return; }
  Sol = NIL;
  S = NIL;

Step2: /* */
  do {
    Solp = ADJ_2D1P2(U,V,w_l,B);
    if (Solp != AD2D_FAIL)
      Sol = CCONC(ADD_2_SOL(S,Solp),Sol);
    if (U == NIL) break;
    ADV(U,&u,&U);
    FIRST2(u,&I,&w_u);
    S = COMP( LIST2(I,LIST2(B,AD2D_N_In)) , S );
  } while(VECTOR_LTEQ(w_u,w_l));
  if (Sol == NIL)
    Sol = AD2D_FAIL;
  
Return: /* Prepare to return. */
  /*sa_send("]");*/
  return Sol;
}
