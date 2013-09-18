/*======================================================================
                      STATSACLIB()

Statistics of saclib.

Side effects
  Various statistics are written to the output stream.
======================================================================*/
#include "saclib.h"

void STATSACLIB()
{

Step1:  /* Report the GC statistics. */   
        SWRITE("\n------------------------------------------------------");
        SWRITE("-----------------------\n");
        GWRITE(GCC);  SWRITE(" Garbage collections, ");
        GWRITE(GCCC); SWRITE(" Cells and ");
        GWRITE(GCAC); SWRITE(" Arrays reclaimed, in ");
        GWRITE(TAU);  SWRITE(" milliseconds.\n");
        GWRITE(LENGTH(AVAIL));   SWRITE(" Cells in AVAIL, ");
        GWRITE(NU / 2); SWRITE(" Cells in SPACE.\n");

Step2:  /* Report the system times. */
        SWRITE("\n");
        SWRITE("System time: ");
        GWRITE(CLOCK() - TAU0); SWRITE(" milliseconds.\n");
        SWRITE("System time after the initialization: ");
        GWRITE(CLOCK() - TAU1); SWRITE(" milliseconds.\n");
        SWRITE("------------------------------------------------------");
        SWRITE("-----------------------\n");

Return: /* Prepare for return. */
        return;
}
