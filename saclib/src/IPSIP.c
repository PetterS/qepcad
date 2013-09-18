/*======================================================================
                           IPSIP(A,p,B)

Integral polynomial to soft-float interval polynomial.

Inputs
   A : in Z[X]. Let n = deg(A).
   p : a positive BETA-digit, the desired precision.
   B : an array of size at least (n+1)(2p+6)+1.

Effect
   B(x), the smallest precision p software interval polynomial 
   of degree n containing A(x) is placed in the array B.
   That is, each coefficient of B(x) is the smallest
   precision p software interval containing the corresponding
   coefficient of A(x).
   B(x) is represented as follows (let c=2p+6 be the length of the
   coefficients)
     B[0] = degree
     B[1],...,B[c] = constant coefficient
     ...
     B[n*c+1],...,B[(n+1)*c] = leading coefficient.
======================================================================*/
#include "saclib.h"

void   IPSIP(A,p,B)
       Word  A;
       BDigit p;
       Word *B;
{
       Word a,Ap;
       BDigit k,K,n,q1,q2,s;

Step1: /* Coefficient size. */
	q1 = p + 3;
	q2 = q1 + q1;

Step2: /* A = 0. */
       if (A == 0) {
          B[0] = 0;
	  ISI(0,p,B + 1);
          return; }

Step3: /* Degree and size. */
       n = FIRST(A);
       B[0] = n;
       s = (n+1) * q2 + 1;

Step4: /* Convert coefficients. */
        K = s - q2;
        Ap = A;
        for (k = n; k >= 0; k--) {
           if (Ap == NIL || FIRST(Ap) < k)
	      ISI(0,p,B + K);
           else {
              Ap = RED(Ap);
              ADV(Ap,&a,&Ap);
              ISI(a,p,B+K); }
           K = K - q2; }

Return: /* return. */
       return;
}
