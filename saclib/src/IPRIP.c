/*======================================================================
                                IPRIP(A; A_1,A_2)

Integral polynomial real and imaginary parts.

Input
   A : a univariate integral polynomial.

Outputs
   A_1, A_2 : bivariate integral polynomials.  A(x + i y) =
              A_1(x,y) + i A_2(x,y).
======================================================================*/
#include "saclib.h"

void IPRIP(A, A1_,A2_)
        Word A, *A1_,*A2_;
{
        Word a,A0,A1,A2,Ap,B1,B2,C1,C2,i,n;

Step1: /* Case A = 0. */
        if (A == 0) {
           A1 = 0;
           A2 = 0;
           goto Return; }

Step2: /* Initialize. */
        Ap = A;
        n = PDEG(A);
        a = PLDCF(A);
        A1 = PMON(a,0);
        A1 = PMON(A1,0);
        A2 = 0;
        Ap = PRED(A);

Step3: /* Alternately multiply A_1 + i A_2 by x + i y and then add the
          next coefficient of A. */
        for (i = n - 1; i >= 0; i--) {
           B1 = PMPSV(A1,2,1,1);    /* B_1 = x A_1 */
           C1 = PMPMV(A2,1);        /* C_1 = y A_2 */
           B2 = PMPSV(A2,2,1,1);    /* B_2 = x A_2 */
           C2 = PMPMV(A1,1);        /* C_2 = y A_1 */
           A1 = IPDIF(2,B1,C1);
           A2 = IPSUM(2,B2,C2);
           if (PDEG(Ap) == i) {
              a = PLDCF(Ap);
              if (Ap != NIL)
                 Ap = PRED(Ap);
              A0 = PMON(PMON(a,0),0);
              A1 = IPSUM(2,A1,A0); } }
        
Return: /* Return A_1 and A_2. */
        *A1_ = A1;
        *A2_ = A2;
        return;
}
