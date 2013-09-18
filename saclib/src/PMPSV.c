/*======================================================================
                      B <- PMPSV(A,r,i,k)

Polynomial multiplication by power of specified variable.

Inputs
   A : a polynomial A(x_1,...,x_r) over a ring.
   r : r > 0, a beta-digit.
   i : 1 <= i <= r, a beta-digit.
   k : a beta-digit.  Either k >= 0 or else A is divisible by (x_i)^k.

Output
   B : B(x_1,...,x_r) = (x_i)^k * A(x_1,...,x_r).
======================================================================*/
#include "saclib.h"

Word PMPSV(A,r,i,k)
       Word A,r,i,k;
{
        Word a,Ap,b,B,j;

Step1: /* Case A = 0 or k = 0. */
        if (A == 0 || k == 0) {
           B = A;
           goto Return; }

Step2: /* Case i = r. */
        if (i == r) {
           B = PMPMV(A,k);
           goto Return; }

Step3: /* Case i < r. */
        Ap = A;
        B = NIL;
        while (Ap != NIL) {
           ADV2(Ap, &j,&a,&Ap);
           b = PMPSV(a,r - 1,i,k);
           B = COMP2(b,j,B); }
        B = INV(B);

Return: /* Return B. */
        return(B);
}

