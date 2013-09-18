/*======================================================================
                      M <- COMP(a,L)

Composition.

Inputs
  a : object.
  L : list.

Outputs  
  M : the composition of a and L.
======================================================================*/
#include "saclib.h"

Word COMP(a,L)
       Word a,L;
{
       Word M;
       /* hide algorithm */

Step1: /* Is AVAIL empty? */
       if (AVAIL == NIL) 
         GC();
   
Step2: /* Get new cell. */
       M = AVAIL; 
       AVAIL = RED(M);

Step3: /* Store a and L. */
       SFIRST(M,a);
       SRED(M,L);

Return: /* Prepare for return. */
       return(M);
}
