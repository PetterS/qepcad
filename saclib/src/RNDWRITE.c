/*======================================================================
                      RNDWRITE(R,n)

Rational number decimal write. 

Inputs
  R : a rational number.  
  n : a non-negative BETA-digit.  

Side effects
  R is approximated by a decimal fraction d with n decimal digits 
  following the decimal point and d is written in the output stream.  
  The inaccuracy of the approximation is at most (1/2)*10^-n.  
  If abs(d) is greater than abs(R) then the last digit is followed by a minus sign, 
  if abs(d) is less than abs(R) then by a plus sign.
======================================================================*/
#include "saclib.h"

void RNDWRITE(R,n)
       Word R,n;
{
       Word A,B,D,F,M,d,i,s,t;
       /* hide B,d,i,s,t; */

Step1: /* Compute approximation. */
       if (R == 0)
         {
         A = 0;
         B = 1;
         }
       else
         FIRST2(R,&A,&B);
       s = ISIGNF(A);
       if (s < 0)
         A = INEG(A);
       M = IEXP(10,n);
       A = IPROD(A,M);
       IQR(A,B,&D,&F);
       F = IDPR(F,2);
       if (F == 0)
         t = 0;
       else
         {
         t = ICOMP(B,F);
         if (t == 0)
           t = 1;
         else
           if (t < 0)
             D = ISUM(D,1);
         }

Step2: /* Convert and write. */
       if (s < 0)
         CWRITE('-');
       IQR(D,M,&D,&F);
       IWRITE(D);
       CWRITE('.');
       for (i = 1; i <= n; i++)
         {
         F = IDPR(F,10);
         IQR(F,M,&d,&F);
         CWRITE(d + '0');
         }
       if (t > 0)
         CWRITE('+');
       else
         if (t < 0)
           CWRITE('-');

Return: /* Prepare for return. */
       return;
}
