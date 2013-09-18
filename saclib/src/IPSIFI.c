/*======================================================================
                      J <- IPSIFI(A,I)

Integral polynomial standard isolating interval from  
isolating interval.

Inputs
  I : an interval with binary rational endpoints, which is either
      left-open and right-closed or a one-point interval.
  A : in Z[X], has a unique root alpha of odd multiplicity in I.

Outputs
  J : If I is a one-point interval, then J = I.
      If I is left-open and right closed, then J is either a standard
      left-open and right-closed subinterval of I containing alpha,
      or if alpha is a binary rational number, J may possibly instead
      be the one-point interval (alpha,alpha).
======================================================================*/
#include "saclib.h"

Word IPSIFI(A,I)
       Word A,I;
{
       Word J,a,b,c,k,m,n,s,t;
       /* hide k,s,t; */

Step1: /* Initialization. */
       FIRST2(I,&a,&b);
       t = IUPBES(A,b);
       if (t == 0)
         {
         J = LIST2(b,b);
         goto Return;
         }

Step2: /* Bisect I until standard subinterval obtained. */
       do
         {
         RNBCR(a,b,&m,&n,&k);
         if (IDIF(n,m) == 1)
           {
           J = LIST2(a,b);
           goto Return;
           }
         c = RIB(a,b);
         s = IUPBES(A,c);
         if (s == 0)
           {
           J = LIST2(c,c);
           goto Return;
           }
         else
           if (s * t < 0)
             a = c;
           else
             b = c;
         }
       while (1);

Return: /* Prepare for return. */
       return(J);
}
