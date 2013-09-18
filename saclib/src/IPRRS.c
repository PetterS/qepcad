/*======================================================================
                      IPRRS(A1,A2,I1,I2; Is1,Is2,s)

Integral polynomial real root separation.

Inputs
  A1,A2 : in Z[X], squarefree, deg(A) > 0.
  I1,I2 : intervals with binary rational number endpoints, each of which
          is either left-open and right-closed, or a one-point interval.
	  I1 contains a unique root alpha_1 of A1, and I2 contains a
	  unique root alpha_2 /= alpha_1 of A2.

Outputs
  Is1,Is2 : binary rational subintervals of I1 and I2 containing alpha_1
            and alpha_2 respectively, with Is1 and Is2 strongly disjoint.
            If I1 is left-open and right-closed then so is Is1,
            and similarly for I2 and Is2.
  s       : a BETA-digit, s = -1 if Is1 < Is2, and s = 1 if Is1 > Is2.
======================================================================*/
#include "saclib.h"

void IPRRS(A1,A2,I1,I2, Is1_,Is2_,s_)
       Word A1,A2,I1,I2, *Is1_,*Is2_,*s_;
{
       Word Is1,Is2,a1,a2,b1,b2,c,d1,d2,s,s1,s2,t,u,v;
       /* hide s,s1,s2,t,u,v; */

Step1: /* I1 and I2 disjoint. */
       FIRST2(I1,&a1,&b1);
       FIRST2(I2,&a2,&b2);
       if (RNCOMP(b1,a2) < 0)
         {
         Is1 = I1;
         Is2 = I2;
         s = -1;
         goto Return;
         }
       if (RNCOMP(b2,a1) < 0)
         {
         Is1 = I1;
         Is2 = I2;
         s = 1;
         goto Return;
         }

Step2: /* Initialize. */
       d1 = RNDIF(b1,a1);
       d2 = RNDIF(b2,a2);
       s1 = 2;
       s2 = 2;

Step3: /* Bisect I1. */
       t = RNCOMP(d1,d2);
       if (t >= 0)
         {
         if (s1 > 1)
           s1 = IUPBES(A1,b1);
         c = RIB(a1,b1);
         u = IUPBES(A1,c);
         if (s1 == 0 || s1 * u < 0)
           {
           a1 = c;
           v = 1;
           }
         else
           {
           b1 = c;
           s1 = u;
           v = -1;
           }
         d1 = RNDIF(b1,a1);
         }

Step4: /* Bisect I2. */
       if (t < 0)
         {
         if (s2 > 1)
           s2 = IUPBES(A2,b2);
         c = RIB(a2,b2);
         u = IUPBES(A2,c);
         if (s2 == 0 || s2 * u < 0)
           {
           a2 = c;
           v = -1;
           }
         else
           {
           b2 = c;
           s2 = u;
           v = 1;
           }
         d2 = RNDIF(b2,a2);
         }

Step5: /* I1 and I2 disjoint. */
       if (v < 0 && RNCOMP(b1,a2) < 0)
         s = -1;
       else
         if (v > 0 && RNCOMP(b2,a1) < 0)
           s = 1;
         else
           goto Step3;
       Is1 = LIST2(a1,b1);
       Is2 = LIST2(a2,b2);

Return: /* Prepare for return. */
       *Is1_ = Is1;
       *Is2_ = Is2;
       *s_ = s;
       return;
}
