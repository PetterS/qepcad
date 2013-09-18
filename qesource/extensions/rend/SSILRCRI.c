/*======================================================================
                      s <- SSILCRI(a,b)

Smallest standard interval, in logarithmic representation, containing 
rational interval.

Inputs
      a : A rational number.
      b : A rational number, b > a, such that 0 is not in (a,b).
Outputs
      s : The smallest standard interval, with logarithmic binary rational
          endpoints, containing the interval (a,b).

Note: This function is based on the following facts:
Let A be the assertion "p is the smallest integer s.t. there exists a 
standard interval of length 2^p which contains (a,b)".
Condition I:  2 | floor( a / 2^(p-1) )
Condition II: 2^p >= b - a;
Condition I is necessary for A.  So is II. Also, if 2^(p-1) >= b - a,
then condition I is a sufficient condition for the existance of a standard
interval of length 2^p containing (a,b).

======================================================================*/
#include "rend.h"

Word SSILRCRI(Word a_, Word b_)
{
       Word s,a,b,p,c,a1,a2,b1,b2,n,t,m,B,C,r;

Step0: /* Reflect interval if neccesary. */
       if (RNSIGN(a_) == -1) {
         s = 1; a = RNNEG(b_); b = RNNEG(a_); }
       else {
         s = 0; a = a_; b = b_; }

Step1: /* Initialize loop.  */
       RNFCL2(RNDIF(b,a),&p,&c);
       if (p == c) p--;
       FIRST2(b,&b1,&b2);
       if (a == 0)
         n = 0;
       else {
         FIRST2(a,&a1,&a2);
         n = IQ(ITRUNC(a1,p),a2); }

Step2: /* Loop until n is even, then increment p and divide n by 2. */
       do {
         if (ISATOM(n)) t = ODD(n);
         else t = ODD(FIRST(n));
         p++;
         n = IDP2(n,1);
       }while(t);
       m = ISUM(n,1);

Step3: /* If p is smallest possible, i.e. p = c, check (m+1)2^p > b. */
       if (p == c) {
         if (p >= 0) {
           B = b1;
           C = IMP2(IPROD(b2,m),p); }
         else {
           B = IMP2(b1,-p);
           C = IPROD(b2,m); }
         if (ICOMP(B,C) >= 1)
           goto Step2; }

Return: /* Return, reflecting the output interval if needed. */
       if (s) { r = n; n = -m; m = -r; }
       return (LIST2(LBRNFIE(n,p),LBRNFIE(m,p)));
}
