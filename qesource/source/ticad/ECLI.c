/*======================================================================
                     ECLI(D; c,t)

Eligible cell with least index.

Input
  D : is a partial CAD.

Output
  c  : is the eligible cell with lexicographically least index
       in the partial CAD D, if one exists, otherwise NIL.
  t  : is 1 if there is a eligible cell, otherwise 0.

Definition:  A candidate cell is a cell with undetermined truth value
which has no children.

Definition:  An eligible cell is a cell with undetermined truth value
that satisfies any user "selected cell condition" and has no children.
An eligible cell is described in some other programs as a "desired 
candidate cell".

This function keeps a stack of indices of possible eligible cells in 
the global variable GVECS.  The order of the indices in the stack is
lexicographic, so to get the cell with least index, the first
index is popped from the stack. Two things complicate this scheme:

1) Constructing a stack may create new eligible cells, so the program
   must push any indices of new eligible cells created by the last stack 
   construction onto GVECS.  To do this, a global variable GVECPI is
   used which contains the index of the last candidate cell returned
   by the function. Any new eligible cells must be children of the cell
   with this index.  Thus, new eligible cells can be found and their
   indices pushed onto GVECS.

2) Constructing a stack may remove eligible cells from the partial
   CAD through the process of truth propagation.  Whenever a cell 
   index I is popped from the stack, an an attempt is made to 
   retrieve the cell with that index from the CAD using the function
   CELLNA.  If the cell is still in the CAD, CELLNA will return it. If 
   the cell with index I has been removed from the CAD, CELLNA will 
   return the nearest ancestor of the now non-existent cell.  This 
   cell must have a determined truth value, and the program ignores 
   the cell in this case.

A GVECPI value of 0 indicates that the stack GCECS has to be 
initialized.  This is done by the function ISFECLI which creates a 
lexicographically ordered list of all eligible cells in the partial 
CAD D.
======================================================================*/
#include <stdlib.h>
#include "qepcad.h"

void QepcadCls::ECLI(Word D, Word *c_, Word *t_)
{
  Word L,l,t,c,p;

Step1: /* Initialize if first time through (GVECPI = 0). */
       if (GVECPI == 0) {
	 GVECS = ISFECLI(D);
	 goto Step3; }

Step2: /* Look for previously returned eligible cell.  If it is still
in the CAD and has undetermined truth value, push the indices of its 
eligible children onto the stack. */
       p = CELLNA(GVECPI,D);
       if (SCREEN(p))
	 for(L = CINV(LELTI(p,CHILD)); L != NIL; L = RED(L)) {
	   l = FIRST(L);
	   if (SCREEN(l))
	     GVECS = COMP(LELTI(l,INDX),GVECS); }

Step3: /* Keep popping cell indices off the stack until one is found 
such that the corresponding cell still exists and does not already 
have a truth value.  If the cell returned by CELLNA is not the one
with index GVECPI, then it must have determined truth value.  Thus 
this single test below accounts for two cases:  The cell with index
GVECPI does exist but has determined truth value, or the cell with
index GVECPI does not exist any longer. */
       while(GVECS != NIL) {
	 ADV(GVECS,&GVECPI.W,&GVECS.W);
	 p = CELLNA(GVECPI,D);
	 if (SCREEN(p)) {
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

/* t <- SCREENBYQUANTIFIER(c)

   c : a qepcad cell
   t : true if c can't be dismissed based on quantifier information
        and false if it can 
*/
BDigit QepcadCls::SCREENBYQUANTIFIER(Word c)
{
      Word k, I, Q, t;

Step1: /* Initialization */
      k = LELTI(c,LEVEL);
      I = LELTI(c,INDX);  
      t = TRUE;
      
Step2: /* If the cell is in bound space, check quantifier! */
      if (k > GVNFV)
      {
	Q = LELTI(GVQ,k - GVNFV);
	switch(Q) {
	case FULLDE: if (LAST(I) % 2 == 0) t = FALSE; break;
	case FULLDA: if (LAST(I) % 2 == 0) t = FALSE; break; }
      }

Return: /* Prepare to return */
      return t;
}

/* This function returns TRUE if a stack should 
   be raised over cell c, and FALSE otherwise. */
BDigit QepcadCls::SCREEN(Word c)
{
  Word T,k,I;
  T = LELTI(c,TRUTH);
  k = LELTI(c,LEVEL);
  I = LELTI(c,INDX);

  return ( // k == 0 || <-- Removed and added k == 0 to last two cases  below
	   (
            (T != NA) &&
	    (T == UNDET || (PCFULL == 'y' && k < GVNFV)) && 
	    (PCUSEDES != 'y' || ISDESIRED(c,PCDESIRED) == 1) &&
	    (k == 0 || SCREENBYQUANTIFIER(c)) &&
	    (k == 0 || !PCMZERROR || k > GVNFV || LAST(I) % 2)
	    ));
}
