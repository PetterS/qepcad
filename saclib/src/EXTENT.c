/*======================================================================
                      n <- EXTENT(a)

Extent.

Inputs
 a  : object.

Outputs
  n : an integer, the extent of a.
      The extent of an atom is 0.
      The extent of a list is equal to the number of elements
      in the list plus the extents of the elements.
======================================================================*/
#include "saclib.h"

Word EXTENT(a)
       Word a;
{
       Word a1,ap,n;
       /* hide a1,n; */

Step1: /* a an atom. */
       n = 0;
       if (a < BETA)
         goto Return;

Step2: /* a a list. */
       ap = a;
       while (ap != NIL)
         {
         ADV(ap,&a1,&ap);
         n = n + EXTENT(a1) + 1;
         }

Return: /* Prepare for return. */
       return(n);
}
