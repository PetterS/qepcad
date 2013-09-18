/*=====================================================================
                         t <- LSICOMP(I,J)

Logarithmic standard interval comparison test.

Inputs
   I,J : logarithmic standard intervals.

Output
   t : an integer.  t = -2 if I < J, t = -1 if J < I,
       t = 0 if I = J, t = +1 if I is properly
       contained in J, and t = +2 if J is properly
       contained in I.
=====================================================================*/
#include "saclib.h"

Word LSICOMP(I,J)
       Word I,J;
{
       Word a1,a2,b1,b2,t,t1,t2;

Step1: /* Obtain endpoints. */
       FIRST2(I,&a1,&a2);
       FIRST2(J,&b1,&b2);

Step2: /* Compare corresponding endpoints. */
       t1 = LBRNCOMP(a1,b1);
       t2 = LBRNCOMP(a2,b2);

Step3: /* Case analysis. */
       if (t1 == 0 && t2 == 0)
	  t = 0;
       else if (t1 >= 0 && t2 <= 0)
	  t = 1;
       else if (t1 <= 0 && t2 >= 0)
	  t = 2;
       else if (LBRNCOMP(b2,a1) <= 0)
	  t = -1;
       else
	  t = -2;

Return: /* Return t. */
       return(t);
}
