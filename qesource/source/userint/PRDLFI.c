/*======================================================================
                      PRDLFI()

Process "display-level-factors i" command. 
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDLFI()
{
      Word i,j,L;

Step1: /* Get level. */
      i = IREAD();
      if (i < 1 || i > GVNV) {
	IWRITE(i); SWRITE(" is not a level.\n");
	goto Return; }

Step2: /* Display. */
      IPLLDWRMOD(GVVL,LIST1(LELTI(GVPF,i))); SWRITE("\n");

Return: /* Prepare for return. */
      return;
}
