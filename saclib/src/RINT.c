/*======================================================================
                      Is <- RINT(I)

Rational interval normalizing transformation.

Inputs
  I : a rational interval (r,s) with r < s.

Outputs
  Is : Let h=floor(lg(s-r))-1 and t=2^h.  
       Is=(rs,ss) where 
       rs is the greatest integer multiple of t 
       which is less than or equal to r, and 
       ss is the least integer multiple of t 
       which is greater than or equal to s.  

Remarks
  I is contained in Is and ss-rs <= 2(s-r).
======================================================================*/
#include "saclib.h"

Word RINT(I)
       Word I;
{
       Word Is,d,h,k,kp,r,rs,s,ss,t;
       /* hide h,k,kp,r,s; */

Step1: /* Compute h=floor(log2(s-r))-1 and t=2^h. */
       FIRST2(I,&r,&s);
       d = RNDIF(s,r);
       RNFCL2(d,&k,&kp);
       h = k - 1;
       t = RNP2(h);

Step2: /* Compute rs. */
       rs = RNFLOR(RNQ(r,t));
       if (rs != 0)
         {
         rs = LIST2(rs,1);
         rs = RNPROD(rs,t);
         }

Step3: /* Compute ss. */
       ss = RNCEIL(RNQ(s,t));
       if (ss != 0)
         {
         ss = LIST2(ss,1);
         ss = RNPROD(ss,t);
         }

Step4: /* Finish. */
       Is = LIST2(rs,ss);

Return: /* Prepare for return. */
       return(Is);
}
