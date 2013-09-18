/*======================================================================
                     L <- LPFZC(C,P)

List of projection factors which are zero on cell.

Inputs
  C : A qepcad cell data structure.
  P : The qepcad data structure for the projection factors.

Outputs
  L : A list of projection factors whose level is the same as C, and
      which are identically zero in C.  These projection factors are
      ordered in the list by decreasing index.
======================================================================*/
#include "qepcad.h"

Word LPFZC(Word C, Word P)
{
      Word v,l,Q,L,i,s,p;

Step1: /* Get the sign vector for the projection factors of the cell's 
          level, and the list of projection factors of that level. */
      l = LELTI(C,LEVEL);
      v = FIRST(LELTI(C,SIGNPF));
      Q = LELTI(P,l);

Step2: /* Find proj fac's with sign zero in C. */
      L = NIL;
      for(i = 1; v != NIL; i++) {
	ADV(v,&s,&v);
	ADV(Q,&p,&Q);
	if (s == 0)
	  L = COMP(p,L); }

Return: /* Prepare to return. */
      return (L);

}
