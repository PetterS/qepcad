/*======================================================================
                      J <- ISFPIR(A,I,k)

Integral squarefree polynomial isolating interval refinement.

Inputs
  A : a squarefree univariate integral polynomial.
  I : an isolating interval for a real root alpha of A.
  k : a BETA-digit, k >= 0.

Outputs
  J : a subinterval of I isolating alpha with length less than 10^{-k}.
======================================================================*/
#include "saclib.h"

Word ISFPIR(A,I,k)
       Word A,I,k;
{
       Word J,q,r,sh,sp,t,u,v,w,x;
       /* hide sh,sp,t; */

Step1: /* Compute. */
       r = IEXP(10,k);
       q = LIST2(1,r);
       FIRST2(I,&u,&v);
       sp = IUPBES(A,v);
       x = RNDIF(v,u);
       t = RNCOMP(x,q);
       while (t >= 0)
         {
         w = RIB(u,v);
         sh = IUPBES(A,w);
         if (sp == 0 || sh * sp < 0)
           u = w;
         else
           {
           v = w;
           sp = sh;
           }
         x = RNDIF(v,u);
         t = RNCOMP(x,q);
         }
       J = LIST2(u,v);

Return: /* Prepare for return. */
       return(J);
}
