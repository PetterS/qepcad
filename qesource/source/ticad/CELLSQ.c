/*======================================================================
                   t <- CELLSQ(c,k,h,j)

Cell section query.

Inputs
   c : a cell.
   k : the level of c.
   h : the level of a projection factor P, h <= k.
   j : the index of P among the h-level projection factors.

Output
   t : Let I = (i_1,...,i_k) be the index of c.  Let c* be
       the cell with index I* = (i_1,...,i_h).  If c* is a
       section of P then t = 1; otherwise t = 0.
======================================================================*/
#include "qepcad.h"

Word QepcadCls::CELLSQ(Word c, Word k, Word h, Word j)
{
        Word C,cs,I,i,i1,Is,M,m,t;

Step1: /* Get the index I* unless c* is a sector. */
	I = LELTI(c,INDX);
	Is = NIL;
	for (i = 1; i < h; i++) {
	   ADV(I,&i1,&I);
	   Is = COMP(i1,Is); }
	/*	if (EVEN(i1)) { */
	if (ODD(i1)) {
	   t = 0;
	   goto Return; }
	Is = INV(Is);

Step2: /* Find the cell c*. */
	cs = GVPC;
	while (Is != NIL) {
	   ADV(Is,&i1,&Is);
	   C = LELTI(cs,CHILD);
	   cs = LELTI(C,i1); }

Step3: /* Check whether j occurs in the multiplicity list 0f c. */
	M = LELTI(cs,MULSUB);
	while (M != NIL) {
	   ADV(M,&m,&M);
	   if (FIRST(m) == j) {
	      t = 1;
	      goto Return; } }
	t = 0;

Return: /* Prepare for return. */
       return(t);
}
