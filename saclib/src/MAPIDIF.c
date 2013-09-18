/*===========================================================================
			 MAPIDIF(m,A,B)

Modular array polynomial in-place difference.

Inputs
  m : a positive BETA-digit.
  A,B : in Z/(m)[x], A and B are in array representation.  The
        array A should be at least as large as the array B.

Side effects
  A - B is computed and put in A.
===========================================================================*/
#include "saclib.h"

void MAPIDIF(m,A,B)
       Word m,*A,*B;
{
       Word d,e,i;

Step1: /* Initialize. */
       d = MAPDEG(A);
       e = MAPDEG(B);
       for (i = d + 1; i <= e; i++)
	  MAPCF(A,i) = 0;

Step2: /* Compute. */
       for (i = 0; i <= e; i++)
	  MAPCF(A,i) = MDDIF(m,MAPCF(A,i),MAPCF(B,i));

Step3: /* Determine degree. */
       i = maxm(d,e);
       while (MAPCF(A,i) == 0 && i > 0)
	  i--;
       MAPDEG(A) = i;

Return: /* Prepare for return. */
       return;
}
