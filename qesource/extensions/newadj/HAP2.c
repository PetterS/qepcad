/*======================================================================
                      L <- HAP2(U,V,w_l,B)

Half Stack Adjacency for 2D CAD cells, deal non-asymptotes.

Inputs
  U  : the stack over c_(i-1), represented as Adj2D_Cells.
  V  : the stack over section cell c_(i), represented as Adj2D_Cells.
  w_l: the characteristic vector for the set of level 2 polynomials
       whose leading coefficients vanish on c_i.
  B  : B = i, the index of the base cell of V.

Outputs
  L  : a list of elements of the form ((i,j),(k,l))
       indicating an adjacency between cell (i,j) and cell (k,l).
======================================================================*/
#include "newadj2D.h"

Word HAP2(Word U, Word V, Word w_l, Word B)
{
  Word Sol,S,v,J,w_v,u,w_u,I,Solp,t,f;

  Sol = NIL;
  S = NIL; 

Step1: /* Base case: V is empty. */
  if (V == NIL) {
    Solp = HAP3(U,w_l,B);
    if (Solp != AD2D_FAIL)
      Sol = CCONC(ADD_2_SOL(S,Solp),Sol);
    goto Return; }
  /* Non base case: v = (J,w_v) is the first element of V */
  ADV(V,&v,&V);
  FIRST2(v,&J,&w_v);

Step2: /* Try assigning no section adjacent to v. */
  if (! VECTOR_ODD_E(w_v)) {
    Solp = HAP2(U,V,w_l,B);
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
	goto Step1; /* Multiplicities of v are filled by assignment. */
      if (f == 3)
	goto Return;/* Multiplicites of v are over-filled by assignment. */
    } while (f == 2);

    /* All multiplicities of v are even ... move on to next section in V. */
    Solp = HAP2(U,V,w_l,B);
    if (Solp != AD2D_FAIL)
      Sol = CCONC(ADD_2_SOL(S,Solp),Sol);
  }while(1);

Return: /* Prepare to return. */
  if (Sol == NIL)
    Sol = AD2D_FAIL;
  return Sol;
}
