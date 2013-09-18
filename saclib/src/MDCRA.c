/*===========================================================================
			a <- MDCRA(m1,m2,mp1,a1,a2)

Modular digit chinese remainder algorithm.  

Inputs
  m1,m2 : positive BETA-integers, 
          with gcd(m1,m2)=1 and ml=m1*m2 less than BETA.       
  mp1   : the inverse of m1 in Z/(m2).  
  a1,a2 : elements of Z/(m1) and Z/(m2) respectively.  

Outpus
  a     :  the unique element of z(ml) such that 
           a is congruent to a1 modulo m1 and 
           a is congruent to a2 modulo m2.
===========================================================================*/
#include "saclib.h"

Word MDCRA(m1,m2,mp1,a1,a2)
       Word m1,m2,mp1,a1,a2;
{
       Word a,ab,b,d;

Step1: /* a = a1. */
       ab = REM(a1,m2);
       d = MDDIF(m2,a2,ab);
       if (d == 0) {
	  a = a1;
	  goto Return; }

Step2: /* General case. */
       b = REM(d * mp1,m2);
       a = m1 * b + a1;

Return: /* Prepare for return. */
       return(a);
}
