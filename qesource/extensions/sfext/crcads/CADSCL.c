/*======================================================================
                      L <- CADSCL(C,i)

CAD section cell list.

Inputs
  C  : A partial CAD.
  i  : A level in the CAD.

Outputs
  L  : A list of all the level i cells in C which are sections.
======================================================================*/
#include "qepcad.h"

Word CADSCL(Word C, Word i)
{
      Word CC,L,c;

Step1: /* Get list of children. */
      CC = LELTI(C,CHILD);
      if (CC == NIL) { L = NIL; goto Return; }

      if ( i > 1 ) {
Step2: /* The children of C are not of level i. */
	for(L = NIL; CC != NIL; CC = RED(CC)) {
	  c = FIRST(CC);
	  L = CCONC(L,CADSCL(c,i-1)); } }

      else {
Step3: /* The children of C are of level i. */
	L = NIL;
	for(CC = RED(CC); CC != NIL; CC = RED2(CC))
	  L = COMP(FIRST(CC),L); }

Return: /* Prepare to return. */
      return (L);
}
