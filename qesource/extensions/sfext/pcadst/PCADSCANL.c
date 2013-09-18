/*======================================================================
                      L <- PCADSCANL(Cs,i)

Pruned CAD section cell and neighbors list.

Inputs
  Cs  : A pruned partial CAD.
  i  : A level in the CAD.

Outputs
  L  : A list of triples (c1,c2,c3) , one for each i-level section
       cell in Cs.  c2 is the PCAD data structure for the section
       cell, c1 is its lower stack neighbor, and c2 its upper stack 
       neighbor.
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

Word PCADSCANL(Word Cs, Word i)
{
      Word CC,CC1,CC2,L,c;

Step1: /* Get list of children. */
      CC = LELTI(Cs,SC_CDTV);
      if (! ISLIST(CC)) { L = NIL; goto Return; }

      if ( i > 1 ) {
Step2: /* The children of Cs are not of level i. */
        for(L = NIL; CC != NIL; CC = RED(CC)) {
          c = FIRST(CC);
          L = CCONC(L,PCADSCANL(c,i-1)); } }

      else {
Step3: /* The children of Cs are of level i. */
        L = NIL;
	CC1 = RED(CC);
	while(CC1 != NIL) {
	  L = COMP(LIST3(FIRST(CC),FIRST(CC1),SECOND(CC1)),L);
	  CC = RED2(CC);
	  CC1 = RED2(CC1); } }

Return: /* Prepare to return. */
      return (L);
}
