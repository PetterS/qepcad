/*======================================================================
                      L <- PCADCL(Cs,i)

Pruned CAD cell list.

Inputs
  Cs  : A pruned partial CAD.
  i  : A level in the CAD.

Outputs
  L  : A list of all the level i cells in Cs.
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

Word PCADCL(Word Cs, Word i)
{
      Word CC,L,c;

Step0: /* The level 0 cell is just Cs. */
      if (i == 0) { L = LIST1(Cs); goto Return; }
 
Step1: /* Get list of children. */
      CC = LELTI(Cs,SC_CDTV);
      if (ISATOM(CC)) { L = NIL; goto Return; }

      if ( i > 1 ) {
Step2: /* The children of C are not of level i. */
	for(L = NIL; CC != NIL; CC = RED(CC)) {
	  c = FIRST(CC);
	  L = CCONC(L,PCADCL(c,i-1)); } }

      else {
Step3: /* The children of C are of level i. */
	L = CC; }

Return: /* */
      return (L);
}
