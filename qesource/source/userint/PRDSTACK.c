/*======================================================================
                          PRDSTACK()

Process "display stack multiplicities" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDSTACK()
{
	Word c,M,t;

Step1: /* Read a cell index and get the cell. */
	CELLRDR(GVPC,&c,&t);
	if (t == 0)
	   goto Return;

Step2: /* Get the stack multiplicities list. */
	M = STACKMULT(c);

Step3: /* Write out the sections and their multiplicity
	  lists. */
	STACKMWR(M);

Return: /* Return. */
	return;
}
