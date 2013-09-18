/*======================================================================
                      L <- HA(c,c_l,P,J,D)

Half Stack Adjacency for 2D CAD cells.

Inputs
  c  : a section cell in the 1D CAD.
  c_l: a neighbor of c.
  P  : the projection factor set.
  J  : the projection polynomial set.
  D  : the CAD

Outputs
  L  : a list of elements of the form ((i,j),(k,l))
       indicating an adjacency between cell (i,j) and cell (k,l).
======================================================================*/
#include "newadj2D.h"

Word HA(Word c, Word c_l, Word P, Word J, Word D)
{
  Word U,V,v_l,Sol,S,A,Ap,a,b;

Step1: /* Initialization. */
  v_l = HALDCOEFMASK(D,c,P,J);
  U = HAS_CONS(c_l,P);
  V = HAS_CONS(c,P);

Step2: /* Get Adjacencies. */
  Sol = HAP1(U,V,v_l,FIRST(LELTI(c,INDX)));

Step3: /* If c_l is to the right of c, reverse order of pairs. */
  if (LAST(LELTI(c,INDX)) < LAST(LELTI(c_l,INDX)) && Sol != AD2D_FAIL) {
    for(S = NIL; Sol != NIL; Sol = RED(Sol)) {
      for(A = NIL, Ap = FIRST(Sol); Ap != NIL; Ap = RED(Ap)) {
	FIRST2(FIRST(Ap),&a,&b);
	A = COMP(LIST2(b,a),A); }
      S = COMP(A,S); }
    Sol = S; }

Return: /* Prepare to return. */
  return Sol;
}

