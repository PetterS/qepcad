/*======================================================================
                      AMUPRRS(M,I,A1,A2,I1,I2; Is1,Is2,s)

Algebraic module univariate polynomial real root separation.  

Inputs
      M : in Z[X], the minimal polynomial of an algebraic number alpha.
      I : an acceptable isolating interval for alpha.  
  A1,A2 : in Z[alpha,X], deg(A1) > 0, deg(A2) > 0.
  I1,I2 : Binary rational intervals, each of which is either left-open 
          and right-closed, or a one-point interval. I1 contains a 
          unique root alpha1 of A1 of odd multiplicity, and I2 
          contains a unique root alpha2 not equal alpha1 of A2 of 
          odd multiplicity.

Outputs
  Is1,Is2 : Binary rational intervals. Is1 is a subinterval of I1 
            containing alpha1 and Is2 is a subinterval of I2 containing 
            alpha2. Is1 and Is2 are strongly disjoint.  
            If I1 is left-open and right-closed then so is Is1, and 
            similarly for I2 and Is2.  
        s : a BETA-digit, s = -1 if Is1 < Is2, and s = 1 if Is1 > Is2.
======================================================================*/
#include "saclib.h"

void AMUPRRS(M,I,A1,A2,I1,I2, Is1_,Is2_,s_)
       Word M,I,A1,A2,I1,I2, *Is1_,*Is2_,*s_;
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
           s1 = AMUPSR(M,I,A1,b1);
         c = RIB(a1,b1);
         u = AMUPSR(M,I,A1,c);
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
           s2 = AMUPSR(M,I,A2,b2);
         c = RIB(a2,b2);
         u = AMUPSR(M,I,A2,c);
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
