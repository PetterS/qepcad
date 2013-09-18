/*
Integral bivariate polynomial evaluation at logarithmic 
binary rational interval, software interval polynomial result.

Inputs
   A : in Z[X,Y]. Let n = deg(A) in Y.
   I : a logarithmic binary rational interval
   p : a positive BETA-digit, the desired precision.
   B : an array of size at least (n+1)(2p+6)+1.
Outputs
   An interval polynomial containing A(I)[Y]
*/
#include "lift2d.h"

void IBPELBRISIPR(Word A, Word I, BDigit p, BDigit *B)
{
  BDigit K, n, i, t, *Bi, *Ip;
  Word L,Ai;
  /* Initialization before processing coefficients */
  K = 2*(p + 3); /* The size of one interval */
  n = PDEG(A);
  B[0] = n;
  L = CINV(A);
  Ip = GETARRAY(K);
  LBRISI(I,p,Ip);

  /* Loop over each of the n+1 coefficients of A ***/
  for(i = 0; i <= n; i++)
  {
    if (L == NIL || SECOND(L) != i) { /* The L == NIL shouldn't be needed */
      /** Zero coefficients ********************/
      ISI(0,p,B + 1 + i*K); }
    else {
      /** Non-zero coefficients ****************/
      ADV2(L,&Ai,&t,&L);
      Bi = GETARRAY((PDEG(Ai)+1)*(2*p+6)+1);
      IPSIP(Ai,p,Bi);
      SIPEVAL(Bi,Ip,B +  1 + i*K);
      FREEARRAY(Bi); }
  }
  
  FREEARRAY(Ip);
  return;
}
