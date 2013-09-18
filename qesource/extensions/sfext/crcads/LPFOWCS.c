/*======================================================================
                     L <- LPFOWCS(C,P)

List of projection factors of which cell is a section.

Inputs
  C : A qepcad cell data structure, must be a section cell!
  B : A qepcad cell data structure, the cell immediately above C in its stack
  P : The qepcad data structure for the projection factors.

Outputs
  L : A list of projection factors whose level is the same as C, and
      which are identically zero in C, but not identically zero in the
      stack containing C - i.e. not nullified on the stack's base.
      These projection factors are ordered in the list by decreasing index.
======================================================================*/
#include "qepcad.h"

Word LPFOWCS(Word C, Word B, Word P)
{
      Word v,l,Q,L,i,s,p,sB,vB;

Step1: /* Get the sign vector for the projection factors of the cell's 
          level, and the list of projection factors of that level. */
      l = LELTI(C,LEVEL);
      v = FIRST(LELTI(C,SIGNPF));
      vB = FIRST(LELTI(B,SIGNPF));
      Q = LELTI(P,l);

Step2: /* Find proj fac's with sign zero in C. */
      L = NIL;
      for(i = 1; v != NIL; i++) {
	ADV(v,&s,&v);
	ADV(vB,&sB,&vB);
	ADV(Q,&p,&Q);
	if (s == 0 && sB != 0)
	  L = COMP(p,L); }

Return: /* Prepare to return. */
      return (L);

}

  /*
      Word M,Pp,L,i;

      M = LELTI(C,MULSUB);
      Pp = P;
      for(L = NIL; Pp != NIL && M != NIL; M = RED(M)) {
	i = FIRST(FIRST(M));
	while( Pp != NIL && i > FIRST(RED(LELTI(FIRST(Pp),PO_LABEL))))
	  Pp = RED(Pp);
	if (Pp != NIL && i == FIRST(RED(LELTI(FIRST(Pp),PO_LABEL))))
	  L = COMP(FIRST(Pp),L); }
      L = CINV(L);
  */


