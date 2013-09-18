/*======================================================================
                          c <- CSSP(a,b)

Choose sector sample point.

Inputs
   a, b : binary rational numbers or NIL.  If both are binary
         rational numbers than a <= b.

Output
   c : a binary rational number.  If a = b = NIL then c = 0.
       If a = NIL and b /= NIL then c = floor(b) - 1.  If a /= NIL
       and b = NIL then c = ceiling(a) + 1.  If a /= NIL and
       b /= NIL then c = SLBRNIM(a,b) if a < b and c = a if a = b.
======================================================================*/
#include "qepcad.h"

Word CSSP(Word a, Word b)
{
        Word c;

Step1: /* a or b NIL. */
        if (a == NIL) {
           if (b == NIL)
              c = 0;
           else
              c = RNINT(IDIF(RNFLOR(b),1));
           goto Return; }
        else if (b == NIL) {
           c = RNINT(ISUM(RNCEIL(a),1));
           goto Return; }

Step2: /* Neither a nor b NIL. */
	if (RNCOMP(a,b) > 0) { /* Chris added just in case! 12/19/2001 */
	  FAIL("CSSP","Bad arguments to CSSP! a > b not allowed!"); }
        if (EQUAL(a,b)) {
           c = a;
           goto Return; }
        c = LBRNRN(SLBRNIM(RNLBRN(a),RNLBRN(b)));

Return: /* Return c. */
        return(c);
}
