/*======================================================================
                      b <- DVCMP(d1,d2)

Degree vector comparison.

Inputs
  d1 , d2 : are degree vectors of distributive 
            polynomials in r variables, r >= 0. 

Outputs
  b  :  b = -1 if d1 < d2,
	b = 0  if d1 = d2, 
        b = 1  if d1 > d2,
        with respect to the inverse lexicographical ordering of degree vectors.
======================================================================*/
#include "saclib.h"

Word DVCMP(d1,d2)
       Word d1,d2;
{
       Word b,dp1,dp2,e1,e2;
       /* hide algorithm */

Step1: /* Compute. */
       dp1 = d1;
       dp2 = d2;
       b = 0;
       while (dp1 != NIL)
         {
         ADV(dp1,&e1,&dp1);
         ADV(dp2,&e2,&dp2);
         if (e1 < e2)
           {
           b = -1;
           goto Return;
           }
         if (e1 > e2)
           {
           b = 1;
           goto Return;
           }
         }

Return: /* Prepare for return. */
       return(b);
}
