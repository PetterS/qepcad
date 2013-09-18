/*======================================================================
                      b <- AFUPRB(M,I,A)

Algebraic number field univariate polynomial root bound.  

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.  
  I : an acceptable isolating interval for alpha.  
  A : in Q(alpha)[x]. A is a monic and deg(A) > 0.

Outputs
  b : a binary rational number. b is a root bound for A.
      If A(x) = x^n + a_{n-1} x^{n-1} + ... + a1 x + a0, then b is 
      the smallest power of 2 such that 2*abs(a_{n-k})^{1/k} <= b 
      for 1 <= k <= n. If a_{n-k} = 0 for 1 <= k <= n then b = 1.
======================================================================*/
#include "saclib.h"

Word AFUPRB(M,I,A)
       Word M,I,A;
{
       Word Ap,J,N,a,a1,b,e,h,h1,h2,hp,i,n,n1,q,r,t,u,v;
       /* hide Ap,N,a,a1,e,h,h1,h2,hp,i,n,n1,q,r,t,u,v; */

Step1: /* Initialize. */
       ADV2(A,&n,&a,&Ap);
       if (Ap == NIL)
         {
         e = -1;
         goto Step3;
         }
       t = 0;

Step2: /* Process terms. */
       do
         {
         ADV2(Ap,&n1,&a1,&Ap);
         i = n - n1;
         ANFAF(M,I,a1,&N,&J);
         J = ISFPIR(N,J,0);
         FIRST2(J,&u,&v);
         if (u == 0)
           RNFCL2(v,&hp,&h);
         else
           if (v == 0)
             RNFCL2(u,&hp,&h);
           else
             {
             RNFCL2(u,&hp,&h1);
             RNFCL2(v,&hp,&h2);
             h = MAX(h1,h2);
             }
         QREM(h,i,&q,&r);
         if (r > 0)
           q = q + 1;
         if (t == 0 || q > e)
           e = q;
         t = 1;
         }
       while (!(Ap == NIL));

Step3: /* Compute b. */
       b = RNP2(e + 1);

Return: /* Prepare for return. */
       return(b);
}
