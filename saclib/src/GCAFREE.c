/*======================================================================
                           GCAFREE(A)

Garbage collected array memory deallocation.

Inputs
  A : a GCA handle.

Side effects
  The array represented by A is deallocated, the cell is linked to GCAAVAIL.
======================================================================*/
#include "saclib.h"

void GCAFREE(A)
       Word A;
{
       extern void free();
       /* hide algorithm */

Step1: /* Test for illegal GCA handle. */
       if (A <= BETAp || BETApp <= A) 
         goto Return;
   
Step2: /* Free memory. */
       if (GCASPACEBp[A].array != 0)
	 free(GCASPACEBp[A].array);
       GCASPACEBp[A].array = (Word *)0;
       GCASPACEBp[A].len = 0;

Step3: /* Link free cell to avail list. */
       GCASPACEBp[A].next = GCAAVAIL;
       GCAAVAIL = A;

Return: /* Prepare for return. */
       return;
}
