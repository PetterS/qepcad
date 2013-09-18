/*======================================================================
                      GCGLOBAL(p)

Declare a global variable to the Garbage Collector.

Inputs
  p : a C pointer, the address of the global variable.

Side effects
  A cell referencing the global variable is added to the GCGLOBALS list.
======================================================================*/
#include "saclib.h"

void GCGLOBAL(p)
       Word *p;
{
Step1: /* Add. */
  GCGLOBALS = PTRCOMP(p,GCGLOBALS);

Return: /* Prepare for return. */
  return;
}
