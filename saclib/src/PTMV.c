/*======================================================================
                             B <- PTMV(r,A)

Polynomial transpose main variables.

Inputs
   r : a beta integer, r >= 2.
   A : an element of R[x_1,...,x_r] for some ring R.

Outputs
   B : an element of R[x_1,...,x_r].  B(x_1,...,x_r) = 
       A(x_1,...,x{r-2},x_r,x_{r-1}).
======================================================================*/
#include "saclib.h"

Word PTMV(r,A)
        Word r,A;
{
        BDigit j,k,m;
        Word a,A1,Ap,App,B,B1;

Step1: /* A = 0. */
        if (A == 0) {
           B = 0;
           goto Return; }

Step2: /* Find the degree of A in x_{r-1} and invert A. */
        m = PDEGSV(r,A,r-1);
        Ap = CINV(A);

Step3: /* For k = m, m-1,...,0, extract from A' the terms of
          degree k in x_{r-1}. */
        B = NIL;
        for (k = m; k >= 0; k--) {
           B1 = NIL;
           App = Ap;
           while (App != NIL) {
              A1 = FIRST(App);
              if (A1 != NIL && FIRST(A1) == k) {
                 a = SECOND(A1);
                 j = SECOND(App);
                 B1 = COMP2(j,a,B1);
                 A1 = RED2(A1);
                 SFIRST(App,A1); }
              App = RED2(App); }
           if (B1 != NIL)
              B = COMP2(B1,k,B); }
        B = INV(B);

Return: /* Return B. */
        return(B);
}
