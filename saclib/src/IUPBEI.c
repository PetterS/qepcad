/*=============================================================================
                         B <- IUPBEI(A,c,k)

Integral univariate polynomial binary rational evaluation. Using arrays.

Inputs 
   A : a univariate integral polynomial.
   c : an integer.
   k : a nonnegative BETA-digit.

Output
   B : an integer. B = 2^(k*n) * A(c/2^k), where n = deg(A).
==============================================================================*/
#include "saclib.h"

Word IUPBEI(A,c,k)
	Word A,c,k;
{
        BDigit d,e,f,M,M2,m,n,o,p,s,t;
        Word B,Bh[LARGE],*Bp,*C,Ch[SMALL];

Step1: /* Copy c into array. */
        IFLTA(c,Ch,SMALL,&C,&m,&t,&o);

Step2: /* Upper bound for length of result. */
        n = PDEG(A);
        d = ILOGB(IPSUMN(1,A));
        e = (k + 1) / ZETA + 1;
        f = maxm(e,m);
        M = n * f + d + 1;

Step3: /* Get an array of twice the length. */
        M2 = 2 * M;
        if (M2 > LARGE)
          Bp = GETARRAY(M2);
        else
          Bp = Bh;

Step4: /* Accumulate result in array. */
        IUPBREA(A,C,m,t,k,Bp,M,&p,&s);

Step5: /* Copy result to list. */
	B = IFATL(Bp,p,s);

Step6: /* Free up memory. */
       if (M2 > LARGE)
          FREEARRAY(Bp);
       if (m > SMALL)
          FREEARRAY(C);

Return:	/* Return B. */
	return(B);
}
