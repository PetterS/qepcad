/*======================================================================
                      L <- ADJ_2D_PART(c,c_l,c_r,P,J)

Adjacency for 2D CAD cells.

Inputs
  c  : a section cell in the 1D CAD.
  c_l: c's left neighbor.
  c_r: c's right neighbor.
  P  : the projection factor set.
  J  : the projection polynomial set.
 
Outputs
  L  : a list of elements of the form ((i,j),(k,l))
       indicating an adjacency between cell (i,j) and cell (k,l).

Note:  This version of the adjacencey algorithm is intended to deal
with the problem that in a partial c_l or c_r might not have stacks.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"

Word ADJ_2D1_COMPLETE(Word c, Word c_l, Word c_r, Word P, Word J)
{
       Word Sol,Sol1,Sol2;


Step1: /* Construct list of possible adjacency assignments. */
       if (LELTI(c,CHILD) == NIL) {
	 Sol = NIL;
	 goto Return; }
       if (LELTI(c_l,CHILD) == NIL)
	 Sol1 = LIST1(NIL);
       else
	 Sol1 = ADJ_2D1(c,c_l,P,J);
       if (LELTI(c_r,CHILD) == NIL)
	 Sol2 = LIST1(NIL);
       else
	 Sol2 = ADJ_2D1(c,c_r,P,J);

Step2: /* If assignment is not unique, decide which is correct. */
       if (LENGTH(Sol1) == 1 && LENGTH(Sol2) == 1)
	 Sol = CCONC(FIRST(Sol1),FIRST(Sol2));
       else
	 Sol = ACMADJ2D(c,c_l,c_r,P);
       Sol = LIST1(Sol);

Return: /* Prepare to return. */
       return Sol;
}


