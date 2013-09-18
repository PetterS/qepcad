/*======================================================================
                     t <- CHTVQ(cs,b)

Cell homogeneous truth value query.

inputs
  cs : A pruned cad cell.
  b  : Either 0 or 1.
outputs
  t : 1 if the truth value of every cell with truth value in the sub-cad
      rooted at cs is equal to b, otherwise 0.
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

Word CHTVQ(Word cs, Word b)
{
      Word l,t,ccs;

Step1: /* Get the child/truth value for cs. */
      l = LELTI(cs,SC_CDTV);

Step2: /* Test truth values if l agrees with b. */
      if (ISATOM(l))
        t = (l == b);
      else {
        do {
          ADV(l,&ccs,&l);
          t = CHTVQ(ccs,b);
        } while((t) && (l != NIL)); }

Return: /* Prepare to return. */
      return (t);
}
