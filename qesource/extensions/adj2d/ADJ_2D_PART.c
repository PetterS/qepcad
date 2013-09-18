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

Word QepcadCls::ADJ_2D_PART(Word c, Word c_l, Word c_r, Word P, Word J)
{
       Word Sol,Sl,Sr,P_2,Pp,I_l,S,a,i1,i2,I_r;

Step1: /* Check for childless cells. */
       Sol = NIL;
       Sl = LELTI(c_l,CHILD);
       Sr = LELTI(c_r,CHILD);
       if ( (Sl == NIL && Sr == NIL) || LELTI(c,CHILD) == NIL)
	 goto Return;

Step2: /* Construct a "shadow stack" if necessary. */
       if (Sl == NIL || Sr == NIL) {
	 P_2 = LELTI(P,2);
	 for(Pp = NIL; P_2 != NIL; P_2 = RED(P_2))
	   Pp = COMP(LELTI(FIRST(P_2),PO_POLY),Pp);
	 Pp = INV(Pp); }
       if (Sl == NIL)
	 ADJ_2D_CONSTRUCT(c_l,Pp);
       if (Sr == NIL)
	 ADJ_2D_CONSTRUCT(c_r,Pp);
  
Step3: /* Construct list of possible adjacency assignments. */
       Sol = ADJ_2D(c,c_l,c_r,P,J);

Step4: /* If assignment is not unique, decide which is correct. */
       if (Sol != AD2D_FAIL && LENGTH(Sol) == 1)
	 Sol = FIRST(Sol);
       else {
SWRITE("Multiplicity not sufficient over "); OWRITE(LELTI(c,INDX)); SWRITE("!\n");
	 Sol = ACMADJ2D(c,c_l,c_r,P); }

Step5: /* Clean up evidence of "shadow stacks". */
       if (Sl == NIL) {
	 I_l = FIRST(LELTI(c_l,INDX));
	 for(S = NIL; Sol != NIL; Sol = RED(Sol)) {
	   a = FIRST(Sol);
	   i1 = FIRST(FIRST(a));
	   i2 = FIRST(SECOND(a));
	   if (i1 != I_l && i2 != I_l )
	     S = COMP(a,S); }
	 Sol = INV(S);
	 SLELTI(c_l,CHILD,NIL); }

       if (Sr == NIL) {
	 I_r = FIRST(LELTI(c_r,INDX));
	 for(S = NIL; Sol != NIL; Sol = RED(Sol)) {
	   a = FIRST(Sol);
	   i1 = FIRST(FIRST(a));
	   i2 = FIRST(SECOND(a));
	   if ( i1 != I_r && i2 != I_r )
	     S = COMP(a,S); }
	 Sol = INV(S);
	 SLELTI(c_r,CHILD,NIL); }
       
       Sol = LIST1(Sol);

Return: /* Prepare to return. */
       return Sol;
}

static void dummy()
{

}
