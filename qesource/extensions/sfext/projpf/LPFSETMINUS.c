/*======================================================================
                           LPFSETMINUS(S,G)

List of projection factors, set minus.

Inputs:
 S : A (set) list of projection factors, all of the same level.
 G : A (set) list of projection factors, all of the same level as 
     those in S.

Outputs:
 Q : A (set) list of all projection factors  in S but not in G.

======================================================================*/
#include "qepcad.h"

Word LPFSETMINUS(Word S, Word G)
{
      Word Q,Sp,s,i_s,t,Gp;

Step1: /* Initialize. */
      Q = NIL;

Step2: /* Loop over each polynomial s in S. */
      for(Sp = CINV(S); Sp != NIL; Sp = RED(Sp)) {
	s = FIRST(Sp);
	i_s = THIRD(LELTI(s,PO_LABEL));

Step3: /* Test if s is in G. */
	t = 0;
	for(Gp = G; t == 0 && Gp != NIL; Gp = RED(Gp))
	  t = (i_s == THIRD(LELTI(FIRST(Gp),PO_LABEL)));

Step4: /* If s is not in G then add s to Q. */
	if (! t)
	  Q = COMP(s,Q); }

Return: /* Return. */
      return (Q);
}
