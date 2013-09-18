/*======================================================================
            L <- IPALLPARTIALS(Word k, Word P, Word t, Word m)

Integer polynomials all partial derivatives.

Inputs:
k : a level
P : a k-variate saclib integral polynomial
t : am order
m : a positive BETA-digit

Output:
L : a list of all t-order partials of P in the variables 
    x_m, x_{m + 1}, ..., x_k
======================================================================*/
#include "qepcad.h"

Word IPALLPARTIALS(Word k, Word P, Word t, Word m)
{
     Word L,Pp,i;

Step1: /* Base Cases */
     if (m > k && t == 0)
       L = LIST1(P);
     else if (m > k && t > 0)
       L = NIL;
     else {

Step2: /* Recursive Cases */
       Pp = P;
       L = IPALLPARTIALS(k,Pp,t,m + 1);
       for(i = 1; i <= t; i++) {
	 Pp = IPDER(k,Pp,m);
	 L = CCONC(IPALLPARTIALS(k,Pp,t - i,m + 1),L);
       } }

Return: /* Return */
  return L;
}
