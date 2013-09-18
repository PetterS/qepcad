/*===========================================================================
		       L <- GCATL(A,n)

GCA to list.

Inputs
  A : is an array handle for a garbage collected array of size n.
  n : the size of the array.

Outputs
  L : a list containing the elements of in the same order.
===========================================================================*/
#include "saclib.h"

Word GCATL(A,n)
       Word A,n;
{
       Word L,i;

Step1: /* Initialize. */
       L = NIL;
       if (n == 0)
	  goto Return;

Step2: /* Put the elements into the list. */
       for (i = 0; i < n; i++)
	  L = COMP(GCAGET(A,i),L);
       L = INV(L);

Return: /* Prepare for return. */
       return(L);
}
