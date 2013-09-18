/*======================================================================
                           IUPHIP(A; B,t)

Integral univariate polynomial to hardware interval polynomial.

Input
   A : a non-zero univariate integral polynomial.

Outputs
   B : the  hardware interval polynomial that results from
       replacing each coefficient of A with the smallest
       hardware interval containing it.
   t : if t = 0, the program failed because of exponent
       overflow and B is undefined.  Otherwise t = 1.
======================================================================*/
#include "saclib.h"

void IUPHIP(A, B_,t_)
        Word A;
        interval **B_;
        BDigit *t_;
{
        BDigit i,n,t;
        interval *B;
        Word Ap,a;

Step1: /* Get array for B. */
        n = PDEG(A);
        B = GETHIPARRAY(n);

Step2: /* /* Convert coefficients. */
        Ap = A;
        for (i = n; i >= 0; i--) {
           if (Ap == NIL || FIRST(Ap) < i)
              B[i] = izero;
           else {
              Ap = RED(Ap);
              ADV(Ap,&a,&Ap);
              IHI(a,&B[i],&t);
              if (t == 0) {
                 FREEARRAY(B);
                 goto Return; } } }

Return: /* Return B and t.*/
        *B_ = B;
        *t_ = t;
        return;
}
