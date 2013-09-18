/*======================================================================
                      PRDLPI()

Process "display-level-polynomials i" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDLPI()
{
      Word i;

Step1: /* Get level. */
      i = IREAD();
      if (i < 1 || i > GVNV) {
	IWRITE(i); SWRITE(" is not a level.\n");
	goto Return; }

Step2: /* Display. */
      IPLLDWRMOD(GVVL,LIST1(LELTI(GVPJ,i))); SWRITE("\n"); goto Return;

Return: /* Prepare for return. */
      return;
}
