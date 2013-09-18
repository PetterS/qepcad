/*======================================================================
                      ESPCADWRITE(D,i)

ESPCAD write.

Inputs
  D : an ESPCAD.
  i : an integer.

Side Effects
  The ESPCAD D is written to the standard out, using i blanks to
  offset the cells of lowest level.

======================================================================*/
#include "espcad.h"

void ESPCADWRITE(Word D, Word i)
{
       Word j,L;

Step1: /* Indent. */
       for(j = 0; j < i; j++)
	 SWRITE("     ");
  
Step2: /* Write cell info. */
       OWRITE(PCADCINDEX(D));
       SWRITE(":");
       OWRITE(LELTI(D,SC_SIGN));
       SWRITE(":");
       OWRITE(LELTI(D,SC_EXTS));
       SWRITE(":");
       IWRITE(LELTI(D,SC_TMPM));
       SWRITE(":");
       OWRITE(LELTI(D,SC_RRNV));
       SWRITE(":");

Step3: /* Write truth value if leaf, otherwise children. */
       if (ISATOM(LELTI(D,SC_CDTV))) {
	 IWRITE(LELTI(D,SC_CDTV)); SWRITE("\n"); }
       else {
	 SWRITE("\n");
	 L = LELTI(D,SC_CDTV);
	 while (L != NIL) {
	   ESPCADWRITE(FIRST(L),i+1);
	   L = RED(L); } }

Return: /* Return. */
       return;
}
