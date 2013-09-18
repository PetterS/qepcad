/*===========================================================================
			  As <- MIDCRA(M,m,mp,A,a)

Modular integer digit chinese remainder algorithm.  

Inputs
  M  : a positive integer.  
  m  : an odd positive BETA-integer.  Gcd(M,m)=1.  
  mp : the inverse of the image of M under the homomorphism H_m.  
  A  : an element of Z'_M.
  a  : an element of Z_m.

Outpus
  As : the unique element of Z'_Ms which is 
       congruent to A modulo M and 
       congruent to a modulo m, 
       where Ms = M * m.
===========================================================================*/
#include "saclib.h"

Word MIDCRA(M,m,mp,A,a)
       Word M,m,mp,A,a;
{
       Word As,ab,b,d;

Step1: /* As = A. */
       ab = MDHOM(m,A);
       d = MDDIF(m,a,ab);
       if (d == 0) {
	  As = A;
	  goto Return; }

Step2: /* General case. */
       b = MDPROD(m,d,mp);
       if (b + b > m)
	  b = b - m;
       As = ISUM(IDPR(M,b),A);

Return: /* Prepare for return. */
       return(As);
}
