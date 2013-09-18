/*======================================================================
                      GIPGEN(N; L1,L2)

Gaussian integer prime generator.

Input
   N  : a beta digit, N >= 2. 

Outputs
   L1 : A naturally ordered list of all rational Gaussian primes less 
        than or equal to the square root of N.
   L2 : A list of all non-real first-octant Gaussian primes, ordered
        by increasing norms, with norms less than or equal to N.

Restriction: N must be less than the square of the largest prime in
             SPRIME, the small prime list.
======================================================================*/
#include "saclib.h"

void GIPGEN(N, L1_,L2_)
       Word N, *L1_,*L2_;
{
       Word *A,f,i,j,L1,L2,n,P,p,q,S,t;

Step1: /* Compute n = ceiling(sqrt(N)). */
        DSQRTF(N,&n,&t);
        if (t > 0)
              n = n + 1;

Step2: /* Get array for squares. */
        A = GETARRAY(n+1);

Step3: /* Compute the squares of the integers from 1 to n. */
        A[1] = 1;
        for (i = 1; i < n; i = i+1)
           A[i+1] = A[i] + i + i + 1;

Step4: /* Loop through the rational primes. */
        P = RED(SPRIME);
        L1 = NIL;
        L2 = LIST1(LIST2(1,1));
        do {
           ADV(P,&p,&P);
           if (p > N)
              goto Step5;
           if (REM(p,4) == 3) {
              if (p < n || (p == n && t == 0)) {
                 L1 = COMP(p,L1); } }
           else {
              i = 1;
              j = 2;
              f = 0;
              do {
                 S = A[i] + A[j];
                 if (S == p) {
                    if (i > j)
                       q = LIST2(i,j);
                    else
                       q = LIST2(j,i);
                    L2 = COMP(q,L2); 
                    f = 1; }
                 else if (S < p) {
                    if (j < n) {
                       j = j + 2; }
                    else {
                       i = i + 2;
                       j = 2; } }
                 else {
                    i = i + 2;
                    j = 2; } }
              while (f == 0); } }
        while (P != NIL);

Step5: /* Invert the lists of Gaussian primes. */
        L1 = INV(L1);
        L2 = INV(L2);

Return: /* Return L1 and L2. */
        *L1_ = L1;
        *L2_ = L2;
        return;
}
