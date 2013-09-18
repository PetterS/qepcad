/*======================================================================
                      L <- GDPGEN(m,k)

Gaussian digit prime generator.

Inputs
  m, k  : positive BETA-digits.

Outputs
  L  : the orded list (p1,...,pr) of all prime numbers p such that
       m <= p < m+4*k and p is congruent to 3 mod 4.
======================================================================*/
#include "saclib.h"

Word GDPGEN(m,k)
       Word m,k;
{
       Word *A,L,d,i,j,m1,m2,mb,ms,p,q,qb,r,r4,r6;
       /* hide A,d,i,j,m1,m2,mb,ms,p,q,qb,r,r4,r6; */

Step1: /* Initialize. */
       A = (Word *)malloc(sizeof(Word) * (k + 1));
       if (A == ((Word *)0)) 
         FAIL("GDPGEN","No more memory",k);
       m1 = m + EVEN(m);
       r = REM(m,4);
       m1 = m + 3 - r;
       m2 = m1 + 4 * k - 4;
       for (i = 1; i <= k; i++)
         A[i] = 0;

Step2: /* Mark proper multiples of dl=3, dl=6*nl+1 
          and dl=6*nl-1 with dl**2 <= ml2. */
       d = 3;
       r4 = 3;
       r6 = 3;
       do
         {
         qb = m2 / d;
         if (d > qb)
           goto Step3;
         mb = qb * d;
         r = REM(mb,4);
         if (r == 3)
           j = 0;
         else
           if (r4 == 1)
             j = r + 1;
           else
             j = 3 - r;
         ms = mb - j * d;
         i = (ms - m1) / 4 + 1;
         q = qb - j;
         while (i > 0 && q > 1)
           {
           A[i] = 1;
           i = i - d;
           q = q - 4;
           }
         if (r6 == 1)
           {
           d = d + 4;
           r6 = 5;
           }
         else
           {
           d = d + 2;
           if (r4 == 3)
             r4 = 1;
           else
             r4 = 3;
           if (r6 == 5)
             r6 = 1;
           else
             r6 = r6 + 2;
           }
         }
       while (1);

Step3: /* Construct prime list. */
       L = NIL;
       p = m2;
       for (i = k; i >= 1; i--)
         {
         if (A[i] == 0)
           L = COMP(p,L);
         p = p - 4;
         }

Return: /* Prepare for return. */
       free(A);
       return(L);
}
