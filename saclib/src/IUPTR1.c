/*======================================================================
                      B <- IUPTR1(A)

Integral univariate polynomial translation by 1. 

Inputs
  A : in Z[x].

Outputs
  B : in Z[x], B(x) = A(x+1).
======================================================================*/
#include "saclib.h"

Word IUPTR1(A)
       Word A;
{
       Word Ap,B,*P,a,a1,ap,c,e,f,fb,h,i,j,k,m,n,s,t;
       /* hide Ap,a1,ap,c,e,f,fb,h,i,j,k,m,n,s,t; */

Step1: /* Degree zero. */
       n = PDEG(A);
       if (n == 0)
         {
         B = A;
         goto Return;
         }

Step2: /* Compute maximum coefficient length. */
       fb = 0;
       Ap = A;
       do
         {
         Ap = RED(Ap);
         ADV(Ap,&a,&Ap);
         f = ILOG2(a);
         if (f > fb)
           fb = f;
         }
       while (Ap != NIL);

Step3: /* Store coefficients in array. */
       k = (fb + n + ZETA - 1) / ZETA;
       m = k * (n + 1);
       if (m > NPTR1 - 1) {
	 GCAFREE(GCAPTR1);
	 NPTR1 = m + 1;
	 GCAPTR1 = GCAMALLOC(NPTR1,GC_NO_CHECK);
       } 
       P = GCA2PTR(GCAPTR1);
       Ap = A;
       i = 1;
       for (h = n; h >= 0; h--)
         {
         if (Ap == NIL)
           e = -1;
         else
           e = FIRST(Ap);
         if (e == h)
           ADV2(Ap,&e,&a,&Ap);
         else
           a = 0;
         ap = a;
         if (ap < BETA)
           ap = LIST1(ap);
         for (j = 1; j <= k; j++)
           {
           if (ap != NIL)
             ADV(ap,&a1,&ap);
           else
             a1 = 0;
           P[i] = a1;
           i = i + 1;
           }
         }

Step4: /* Apply synthetic division. */
       for (h = n; h >= 1; h--)
         {
         c = 0;
         m = m - k;
         for (i = 1; i <= m; i++)
           {
           s = P[i] + P[i + k] + c;
           c = 0;
           if (s >= BETA)
             {
             s = s - BETA;
             c = 1;
             }
           else
             if (s <= -BETA)
               {
               s = s + BETA;
               c = -1;
               }
           P[i + k] = s;
           }
         }

Step5: /* Convert B to normal form. */
       B = NIL;
       e = 0;
       i = k * n;
       do
         {
         a = NIL;
         j = k;
         do
           {
           s = P[i + j];
           j = j - 1;
           }
         while (s == 0 && j != 0);
         if (s != 0)
           {
           c = 0;
           h = i + 1;
           j = j + 1;
           for (t = 1; t <= j; t++)
             {
             a1 = P[h] + c;
             c = 0;
             if (s > 0 && a1 < 0)
               {
               a1 = a1 + BETA;
               c = -1;
               }
             if (s < 0 && a1 > 0)
               {
               a1 = a1 - BETA;
               c = 1;
               }
             a = COMP(a1,a);
             h = h + 1;
             }
           while (FIRST(a) == 0)
             a = RED(a);
           if (RED(a) == BETA)
             a = FIRST(a);
           else
             a = INV(a);
           B = COMP2(e,a,B);
           }
         e = e + 1;
         i = i - k;
         }
       while (e <= n);

Return: /* Prepare for return. */
       return(B);
}
