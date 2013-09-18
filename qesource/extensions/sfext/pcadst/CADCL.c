/*======================================================================
                      L <- CADCL(C,i)

CAD cell list.

Inputs
  C  : A partial CAD.
  i  : A level in the CAD.

Outputs
  L  : A list of all the level i cells in Cs.
======================================================================*/
#include "qepcad.h"

Word CADCL(Word C, Word i)
{
      Word CC,L,c;

Step0: /* The level 0 cell is just Cs. */
      if (i == 0) { L = LIST1(C); goto Return; }
 
Step1: /* Get list of children. */
      CC = LELTI(C,CHILD);
      if (CC == NIL) { L = NIL; goto Return; }

      if ( i > 1 ) {
Step2: /* The children of C are not of level i. */
        for(L = NIL; CC != NIL; CC = RED(CC)) {
          c = FIRST(CC);
          L = CCONC(L,CADCL(c,i-1)); } }

      else {
Step3: /* The children of C are of level i. */
        L = CC; }

Return: /* */
      return (L);
}
