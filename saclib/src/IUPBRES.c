/*======================================================================
                       s <- IUPBRES(A,a)

Integral univariate polynomial binary rational evaluation of sign.

Inputs
   A : in Z[x].
   a : a logarithmic binary rational number. 

Outputs
   s : a BETA-digit, s = sign(A(a)).
======================================================================*/
#include "saclib.h"

BDigit IUPBRES(A,a)
       Word A,a;

{
        BDigit d,e,f,k,M,M2,m,n,o,p,s,t;
        Word Bh[LARGE],*Bp,*C,Ch[SMALL],c;

Step1: /* Let a = c / 2^k with k non-negative. */
       if (a == 0) {
          c = 0;
          k = 0; }
       else {
          FIRST2(a,&c,&k);
          if (k < 0) {
             c = IMP2(c,-k);
             k = 0; } }

Step2: /* Copy c into array. */
        IFLTA(c,Ch,SMALL,&C,&m,&t,&o);

Step3: /* Upper bound for length of result. */
        n = PDEG(A);
        d = ILOGB(IPSUMN(1,A));
        e = (k + 1) / ZETA + 1;
        f = maxm(e,m);
        M = n * f + d + 1;

Step4: /* Get an array of twice the length. */
        M2 = 2 * M;
        if (M2 > LARGE)
          Bp = GETARRAY(M2);
        else
          Bp = Bh;

Step5: /* Accumulate result in array. */
        IUPBREA(A,C,m,t,k,Bp,M,&p,&s);

Step6: /* Free up memory. */
       if (M2 > LARGE)
          FREEARRAY(Bp);
       if (m > SMALL)
          FREEARRAY(C);

Return:	/* Return s. */
	return(s);
}
