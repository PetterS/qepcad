/*=============================================================================
                         IUPBREA(A,C,m,t,k,B,M; p,s)

Integral univariate polynomial binary rational evaluation - array version.

Inputs
   A : a univariate integral polynomial.
   C : an array. C,m,t together specify an integer c.
       If c is non-zero, C contains |c|.
   m : the BETA-length of c.
   t : the sign of c.
   k : a non-negative BETA-digit.
   B : an array of length >= 2*M.
   M : a positive BETA-digit, M > the BETA-length of any intermediate result
       in Horner's scheme. The inequality is strict because subprograms
       IPRODAP and IMPBAA require an array that might be 1 BETA-digit longer
       than the result.
       One may choose M = deg(A) * max(m,ILOGB(2^k)) + ILOGB(IPSUMN(A)) + 1.

Effect
   The program computes  b = 2^(k*deg(A)) * A(c/2^k).
   If b is non-zero, B contains the integer |b|.

Output
   p : the BETA-length of b.
   s : the sign of b.
==============================================================================*/
#include "saclib.h"

void IUPBREA(A,C,m,t,k,B,M, p_,s_)
        Word A,*C,m,t,k,*B,M,*p_,*s_;
{
        BDigit d,e1,e2,i,j,n,o,p,q,r,s,u;
        Word a1,a2,Ap,*Bp;

Step1: /* A = 0. */
        if (A == 0) {
           p = 0;
           s = 0;
           goto Return; }

Step2: /* c = 0. */
        if (t == 0) {
          if (PORD(A) != 0) {
            p = 0;
            s = 0; }
          else
            IFLTA(PTRCF(A),B,M,&B,&p,&s,&o);
          goto Return; }

Step3: /* Put leading coefficient into result array. */
        ADV2(A,&e1,&a1,&Ap);
        IFLTA(a1,B,M,&B,&p,&s,&o);
        if (ODD(e1) && t < 0)
           s = -s;

Step4: /* Coefficient array. */
        Bp = B + M;

Step5: /* Horner steps. */
        n = e1;
        while (Ap != NIL) {
           ADV2(Ap,&e2,&a2,&Ap);
           for (i = 1; i <= e1 - e2; i++)
              IPRODAP(B,p,C,m,&p);
           d = k * (n - e2);
           q = d / ZETA;
           r = d - q * ZETA;
           IFLTA(a2,Bp,M,&Bp,&j,&u,&o);
           IRLSA(Bp,j,r,&j);
           if (ODD(e2) && t < 0)
              u = -u;
           IMPBAA(Bp,B,j,p,u,s,q,&p,&s); 
           e1 = e2; }

Step6: /* Last term not constant. */
        for (i = 1; i <= e1; i++)
           IPRODAP(B,p,C,m,&p);

Return: /* Return p,s. */
        *p_ = p;
        *s_ = s;
        return;
}
