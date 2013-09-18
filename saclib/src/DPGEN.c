/*======================================================================
                      L <- DPGEN(m,k)

Digit prime generator.

Inputs
  k, m  : positive BETA-digits, 

Outputs
  L  : the ordered list (p1,...,pr) of all prime numbers pi
       such that m <= pi < m+2*k.
======================================================================*/
#include "saclib.h"

Word DPGEN(m,k)
       Word m,k;
{
       Word *A,L,d,h,i,m1,m2,p,q,r,s;
       /* hide A,d,h,i,m1,m2,p,q,r,s; */

Step1: /* Initialize. */
       A = (Word *)malloc((unsigned) (sizeof(Word) * (k + 1)));
       if (A == ((Word *)0)) 
         FAIL("DPGEN","No more memory",k);
       m1 = m + EVEN(m);
       h = 2 * k - 2;
       m2 = m1 + h;
       for (i = 1; i <= k; i++)
         A[i] = 0;

Step2: /* Mark proper odd multiples of dl for dl=3 and dl=6*nl+1 or       
          dl=6*nl-1 with dl**2 <= ml2. */
       d = 3;
       s = 0;
       do
         {
         q = m2 / d;
         if (q < d)
           goto Step3;
         r = REM(m1,d);
         if (r + h >= d || r == 0)
           {
           if (r == 0)
            i = 1;
           else
            if (EVEN(r) == 1)
             i = d - r / 2 + 1;
            else
             i = (d - r) / 2 + 1;
           if (m1 <= d)
            i = i + d;
           while (i <= k)
            {
            A[i] = 1;
            i = i + d;
            }
           }
         if (s == 1)
           {
           d = d + 4;
           s = 2;
           }
         else
           if (s == 2)
            {
            d = d + 2;
            s = 1;
            }
           else
            {
            d = 5;
            s = 2;
            }
         }
       while (1);

Step3: /* Construct prime list. */
       L = NIL;
       p = m2;
       i = k;
       do
         {
         if (A[i] == 0)
           L = COMP(p,L);
         p = p - 2;
         i = i - 1;
         }
       while (!(i == 0));
       if (m == 1)
         SFIRST(L,2);
       if (m == 2)
         L = COMP(2,L);

Return: /* Prepare for return. */
      free(A);
      return(L);
}
