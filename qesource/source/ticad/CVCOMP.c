/*======================================================================
                      t <- CVCOMP(c1,c2)

Conversion complexity Compare.

\Input
  \parm{c1} is a non-root cell.
  \parm{c2} is another non-root cell.
  
\Output
  \parm{t} is $1$ if $c_1$ requires non-trivial conversion and $c_2$
                  requires trivial conversion,
             $-1$ if $c_1$ requires trivial conversion and $c_2$
                  requires non-trivial conversion, and
              $0$ otheriwse.
======================================================================*/
#include "qepcad.h"

Word CVCOMP(Word c1, Word c2)
{
       Word I1,I2,M1,M2,Mp1,Mp2,R1,R2,b1,b2,m1,m2,mp1,mp2,s1,
            s2,t,Ip1,Ip2,bp1,bp2;
       /* hide R1,R2,m1,m2,mp1,mp2,t; */

Step1: /* Setup. */
       s1 = LELTI(c1,SAMPLE);
       if (ISPRIMIT(s1))
         {
         FIRST3(s1,&M1,&I1,&b1);
         m1 = PDEG(M1);
         mp1 = 1;
         }
       else
         {
         FIRST5(s1,&M1,&I1,&Mp1,&Ip1,&bp1);
         m1 = PDEG(M1);
         mp1 = PDEG(Mp1);
         }
       s2 = LELTI(c2,SAMPLE);
       if (ISPRIMIT(s2))
         {
         FIRST3(s2,&M2,&I2,&b2);
         m2 = PDEG(M2);
         mp2 = 1;
         }
       else
         {
         FIRST5(s2,&M2,&I2,&Mp2,&Ip2,&bp2);
         m2 = PDEG(M2);
         mp2 = PDEG(Mp2);
         }

Step2: /* Compare. */
       if (mp1 > 1 && m1 > 1) R1 = 1; else R1 = 0;
       if (mp2 > 1 && m2 > 1) R2 = 1; else R2 = 0;
       t = SIGN(R1 - R2); goto Return;

Return: /* Prepare for return. */
       return(t);
}
