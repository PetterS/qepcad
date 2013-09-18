/*======================================================================
                     CSN(c,D;b,d)

Cell stack nieghbors.

inputs
  c : A qepcad cell data structure for a section cell.
  D : Qepcad data structure for a cad.
outputs
  b : The lower nieghbor of C in the stack.
  d : The upper nieghbor of C in the stack.
======================================================================*/
#include "qepcad.h"

void CSN(Word c, Word D, Word *b_, Word *d_)
{
      Word I,S,x,b,d;

Step1: /* Initialization. */
      I = LELTI(c,INDX);
      S = D;

Step2: /* Set S to the stack containing C. */
      for(ADV(I,&x,&I); I != NIL; ADV(I,&x,&I)) {
	S = LELTI(LELTI(S,CHILD),x); }
      S = LELTI(S,CHILD);

Step3: /* Set b to the element before c, and d to the element after c. */
      b = LELTI(S,x-1);
      d = LELTI(S,x+1);

Retrun:
      *b_ = b;
      *d_ = d;
      return;
}
