/*======================================================================
                      t <- Mystery_f(L,R,M)

"Mystery function" --  kind of decides if an assignment of adjacencies 
is worth considering.

Inputs
  L  :  a list of n BETA-digits -- "left vector"
  R  :  a list of n BETA-digits -- "right vector"
  M  :  a list of n BETA-digits -- "middle vector"

Outputs
  t  :  M is the multiplicity vector for C, a "section over a section"
        cell.  L is the sum of the multiplicity vectors for all the
        section cells in the stack left of C and R for cells in the
	stack right of C.  t = 0 means that no solution with these
	assignments can be found.  t = -1 means that a solution may
	exist, but more cells must be assigned adjacent to C.  t = 1
	means that a solution may exist with exactly these cells
	assigned adjacent to C.
======================================================================*/
#include "adj2D.h"

Word Mystery_f(Word L, Word R, Word M)
{
  Word Lp,Rp,u,v,min,max,v1; Word u1, M1;

Step1: /* u = the componantwise minimum of L and R.
	  v = the componantwise difference between min and max of L and R.
       */
  Lp = CINV(L); Rp = CINV(R);
  for(u = NIL, v = NIL; Lp != NIL; Lp = RED(Lp), Rp = RED(Rp)) {
    min = MIN(FIRST(Lp),FIRST(Rp));
    max = MAX(FIRST(Lp),FIRST(Rp));
    u = COMP(min,u);
    v = COMP(max - min, v); }

Step2: /* Return 0 if assignments overflow multiplicities. */
  if ( !VECTOR_LTEQ( VECTOR_SUM(u,v) , M ) )
    return 0;
  
Step3: /* Return -1 if multiplicity bounds are satisfied, but the
	  an odd number of sections enter the point. */
  while(v != NIL) {
    ADV(v,&v1,&v);
    if (v1 & 1)
      return -1; }
  /* Return -1 if multiplicity bounds are satisfied, but parity of
     M is not the same as parity of u. */
  while(u != NIL) {
    ADV(u,&u1,&u);
    ADV(M,&M1,&M);
    if ((u1 % 2) != (M1 % 2))
      return -1; }

Step4: /* Otherwise return 1. */
  return 1;


}
