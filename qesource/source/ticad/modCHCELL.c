/*======================================================================
                     ECLI(cs; c,t)

Eligible cell with least index.

Input
  c* : is a partial CAD.

Output
  c  : is the next candidate cell in the partial CAD on c*, if one
       exists, otherwise NIL.
  t  : is 1 if there is a candidate cell, otherwise 0.

This function does a depth-first search for a candidate cell.  A stack
of indices of eligible cells, meaning cells that may become candidate
cells, is kept in the global variable PC_S.  Eligible cells are popped
off this stack until one is found that has undetermined truth value and
over which no stack has been constructed.  Two things complicate this
scheme:

1) Constructing a stack may create new eligible cells, so the program
   must push any indices of new eligible cells created by the last stack 
   construction onto GVECS.  To do this, a global variable GVECPI is
   used which contains the index of the last candidate cell returned
   by the function. Any new eligible cells must be children of the cell
   with this index.  Thus, new eligible cells can be found and pushed
   onto GVECS.

2) Constructing a stack may remove a eligible cells from the partial
   CAD through the process of truth propagation.  Whenever a cell 
   index I is encountered, the cell is retrieved from the CAD using the 
   function CELLNA.  If the cell with index I has been removed from
   the CAD, CELLNA will return the nearest ancestor to the now non-
   existent cell.  This cell must have a determined truth value, and the
   program ignores the cell in this case.

======================================================================*/
#include <stdlib.h>
#include "qepcad.h"

void ECLI(Word cs, Word *c_, Word *t_)
{
       Word L,N,l,t,c,i,p;

Step1: /* Initialize if first time through (GVECPI = 0). */
       if (GVECPI == 0) {
	 GVECS = LIST1(NIL);	 
	 goto Step3; }

Step2: /* Look for previously returned candidate cell.  If it is still
in the CAD and has undetermined truth value push its children on the
stack. */
       p = CELLNA(GVECPI,cs);
       if (LELTI(p,TRUTH) == UNDET) {
	 L = LELTI(p,CHILD); 
	 for(i = 1; L != NIL; i++, L = RED(L)) {
	   l = FIRST(L);
	   GVECS = COMP(LELTI(l,INDX),GVECS); } }

Step3: /* Keep popping cells off the stack until one is found which 
still exists, doesn't already have a truth value and, if there is a cell
condition, the condition is satisfied. If such a cell is found and that
cell already has a stack over it we go to Step2 (note that GVECPI is set 
to that cell's index). */
       while(GVECS != NIL) {
	 ADV(GVECS,&GVECPI,&GVECS);
	 p = CELLNA(GVECPI,cs);
	 if (LELTI(p,TRUTH) == UNDET && (PCUSEDES != 'y' || 
	     ISDESIRED(p,PCDESIRED) == 1)) {
	   if (LELTI(p,CHILD) != NIL)
	     goto Step2; /* Only occurs when CHCELL has also been used. */
	   t = 1;
	   c = p;
	   goto Return; } }

Step4: /* No more cells left. */
       t = 0;
       c = NIL;
       GVECPI = 0;

Return: /* Prepare to return. */
       *c_ = c;
       *t_ = t;
       return;
}
