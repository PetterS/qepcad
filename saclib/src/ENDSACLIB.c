/*======================================================================
                      ENDSACLIB(f)

End saclib.

Inputs
  f : a BETA-digit.
      f = SAC_KEEPMEM, if all memory allocated by a call to GCAMALLOC() 
                       should be kept,
      f = SAC_FREEMEM, if it should be deallocated.

Side effects
  Cleans up the environment of the SACLIB.
======================================================================*/
#include "saclib.h"

void ENDSACLIB(f)
        Word f;
{
        Word i;

Step1:  /* Release the SPACE. */
        free(SPACE);

Step2:  /* Release the memory allocated using GCAMALLOC(). */
	if (f == SAC_FREEMEM) {
          for (i=1; i<=NUp; i++)
	    if (GCASPACE[i].array != (Word *)0)
	      free(GCASPACE[i].array);
	}  
	else
	  GCAFREE(GCAPTR1);

Step3:  /* Release the GCASPACE. */
        free(GCASPACE);

Return: /* Prepare for return. */
        return;
}
