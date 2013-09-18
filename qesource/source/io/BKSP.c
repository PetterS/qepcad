/*======================================================================
                      BKSP()

Backspace.  The last character read is put back onto the input stream.
(Replaces the saclib BKSP.)
======================================================================*/
#include "qepcad.h"
#include <stdio.h>

void BKSP()
{
       /* hide algorithm */

Step1: /* Put back. */
       if (setWASBKSP(1)) FAIL("BKSP","was called twice conjecutively.");

Return: /* Prepare for return. */
       return;
}
