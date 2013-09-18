/*
This considers only a single stack and that from the left.
This particular function deals non-asymptotes.
 */
#include "adj2D.h"
#define nEw
void sa_send(const char* S);
#ifdef nEw

Word ADJ_2D1P2(Word U, Word V, Word w_l, Word B)
{
  Word Sol,S,v,J,w_v,u,w_u,I,Solp,t,f;

  /*sa_send("[");*/

Sol = NIL;
S = NIL; 

Step1: /* Base case: V is empty. */
  if (V == NIL) {
    Solp = ADJ_2D1P3(U,w_l,B);
    if (Solp != AD2D_FAIL)
      Sol = CCONC(ADD_2_SOL(S,Solp),Sol);
    goto Return; }
  /* Non base case: v = (J,w_v) is the first element of V */
  ADV(V,&v,&V);
  FIRST2(v,&J,&w_v);

Step2: /* Try assigning no section adjacent to v. */
  if (! VECTOR_ODD_E(w_v)) {
    Solp = ADJ_2D1P2(U,V,w_l,B);
    if (Solp != AD2D_FAIL)
      Sol = CCONC(ADD_2_SOL(S,Solp),Sol); }

Step3: /* Try all assignments of section adjacencies to v. */
  do {

    /* Loop while some muliplicities of v are odd. */
    do {
      /* u = (I,w_u) is  first section in U if U's not empty. */
      if (U == NIL) goto Return;
      ADV(U,&u,&U);
      FIRST2(u,&I,&w_u);

      /* Try assigning u adjacent to v. */
      S = COMP(LIST2(I,J),S);
      w_v = VECTOR_DIF_S(w_v,w_u,&f);
      if (f == 0)
	goto Step1; /* Multiplicities of v are filled by assingment. */
      if (f == 3)
	goto Return;/* Multiplicites of v areover-filled by assingment. */
    } while (f == 2);

    /* All multiplicities of v are even ... move on to next section in V. */
    Solp = ADJ_2D1P2(U,V,w_l,B);
    if (Solp != AD2D_FAIL)
      Sol = CCONC(ADD_2_SOL(S,Solp),Sol);
  }while(1);

Return: /* Prepare to return. */

  /*sa_send("]");*/
  if (Sol == NIL)
    Sol = AD2D_FAIL;
  return Sol;
}

#else

Word ADJ_2D1P2(U,V,w_l,B)
       Word U,V,w_l,B;
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

#endif
