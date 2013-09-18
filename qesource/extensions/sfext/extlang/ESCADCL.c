/*======================================================================
                      L <- CADCL(C,i)

Extended Sub-CAD cell list.

Inputs
  C  : An ESCAD.
  i  : A level in the ESCAD.

Outputs
  L  : A list of all the level i cells in C.
======================================================================*/
#include "extlang.h"

Word ESCADCL(Word C, Word i)
{
      Word CC,L,c;

Step0: /* The level 0 cell is just Cs. */
      if (i == 0) { L = LIST1(C); goto Return; }
 
Step1: /* Get list of children. */
      CC = LELTI(C,SC_CDTV);
      if (CC == NIL) { L = NIL; goto Return; }

      if ( i > 1 ) {
Step2: /* The children of C are not of level i. */
        for(L = NIL; CC != NIL; CC = RED(CC)) {
          c = FIRST(CC);
          L = CCONC(L,ESCADCL(c,i-1)); } }

      else {
Step3: /* The children of C are of level i. */
        L = CC; }

Return: /* */
      return (L);
}
