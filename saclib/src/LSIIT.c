/*=====================================================================
			t <- LSIIT(I,J)

Logarithmic standard interval inclusion test.

Inputs
   I,J : logarithmic standard intervals.

Output
   t : an integer.  t = -1 if I is not contained in J,
       t = 0 if I = J, and t = +1 if I is properly
       contained in J.
=====================================================================*/
#include "saclib.h"

Word LSIIT(I,J)
       Word I,J;
{
       Word a1,a2,b1,b2,t,t1,t2;

Step1: /* Obtain endpoints. */
       FIRST2(I,&a1,&a2);
       FIRST2(J,&b1,&b2);

Step2: /* Compare endpoints. */
       t1 = LBRNCOMP(a1,b1);
       t2 = LBRNCOMP(a2,b2);

Step3: /* Case analysis. */
       if (t1 == 0 && t2 == 0)
	  t = 0;
       else if (t1 >= 0 && t2 <= 0)
	  t = 1;
       else
	  t = -1;

Return: /* Return t. */
       return(t);
}
