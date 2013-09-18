/*======================================================================
                      M <- MCPMV(n,L)

Matrix of coefficients of polynomials, with respect to main variable.

Inputs
  n : a BETA-digit, n > 0. 
  L : a list (L1,...,Lk), k >= 1, with Li in D[X] (D an arbitrary
      domain),  Li non-zero, deg(Li) < n.

Outputs
  M : an n by k matrix over D, with m_{1,i}+m_{2,i}*X + ... +
      m_{n,i}*X^(n-1) = Li for 1 <= i <= k.
======================================================================*/
#include "saclib.h"

Word MCPMV(n,L)
       Word n,L;
{
       Word Lp,Lp1,Ls,M,Mp,Ms,i,k;
       /* hide Ls,Ms,i,k; */

Step1: /* Compute. */
       Lp = L;
       Mp = NIL;
       do
         {
         ADV(Lp,&Ls,&Lp);
         Lp1 = DPFP(1,Ls);
         ADV(Lp1,&k,&Lp1);
         for (i = 1; i <= n - k - 1; i++)
           Lp1 = COMP(0,Lp1);
         Mp = COMP(Lp1,Mp);
         }
       while (!(Lp == NIL));
       M = NIL;
       do
         {
         Ms = Mp;
         Lp = NIL;
         do
           {
           Ls = FIRST(Ms);
           SFIRST(Ms,RED(Ls));
           SRED(Ls,Lp);
           Lp = Ls;
           Ms = RED(Ms);
           }
         while (!(Ms == NIL));
         M = COMP(Lp,M);
         }
       while (!(FIRST(Mp) == NIL));

Return: /* Prepare for return. */
       return(M);
}
