/*
This is an ultra simplified version of 2D adjacency 2 stack method.  It's assumed 
that asymptotes are not an issue here, and there is a recursive call for each section
in V.
 */
#include "adj2D.h"
void sa_send(const char* S);

Word ADJ_2D1_SIMPLE(Word U, Word V, Word w_l, Word B)
{
  Word Sol,S,v,J,w_v,u,w_u,I,Solp,t,f;

sa_send("[");

Sol = NIL;
S = NIL; 

Step1: /* V empty. */
  if (V == NIL) {
    if (U != NIL)
      Sol = NIL;
    else
      Sol = LIST1(NIL);
    goto Return; }

Step2: /* */
  ADV(V,&v,&V);
  FIRST2(v,&J,&w_v);


Step3: /* */
  t = 0;
  do {

    if (t++) {
    if (U == NIL) goto Return;
      ADV(U,&u,&U);
      FIRST2(u,&I,&w_u);
      S = COMP(LIST2(I,J),S); }
    else
      w_u = ZERO_VECTOR(LENGTH(w_v));

    w_v = VECTOR_DIF_S(w_v,w_u,&f);
    
    if (f == 3)
      goto Return; /* multiplicty overflowed! */
    if (f == 2)
      continue;    /* parity doesn't check. */

  if (V == NIL) {
    if (U != NIL)
      Solp = NIL;
    else
      Solp = LIST1(NIL); }
  else
    Solp = ADJ_2D1_SIMPLE(U,V,w_l,B);

    if (Solp != NIL)
      Sol = CCONC(ADD_2_SOL(S,Solp),Sol);
  }while(1);

Return: /* Prepare to return. */

sa_send("]");
  return Sol;
}

/*  Checks to see if 2 adjacency assignment results are the same. */
int ADJCOMP(Word A, Word B)
{
  Word Bp,a;
  if (LENGTH(A) != LENGTH(B))
    return 0;
  if (LENGTH(A) > 1)
    return 1;
  A = FIRST(A); B = FIRST(B);
  while(A != NIL) {
    ADV(A,&a,&A);
    for(Bp = B; Bp != NIL && !EQUAL(a,FIRST(Bp)); Bp = RED(Bp));
    if (Bp == NIL)
      return 0; }
  return 1;
}
