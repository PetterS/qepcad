/*======================================================================
                      k <- IPVCHTP(A)

Integral polynomial variations after circle to half-plane
transformation, partial count.

Inputs
   A : in Z[x], non-zero.

Outputs
   k : Let n = deg(A), A'(x) = x^n A(1/x) and B(x)=A'(x+1).  Let h
      be the number of sign variations in the coefficients of B.
      Then k = min(h,2).
======================================================================*/
#include "saclib.h"
#define IPVCHTP_SIZE 1000

Word IPVCHTP(A)
       Word A;
{
       Word Ab[IPVCHTP_SIZE];
       Word Ap,*P,a,a1,ap,c,e,f,fb,g,h,i,j,k,m,n,s,t;

Step1: /* Compute maximum coefficient length. */
       fb = 0;
       Ap = A;
       do {
	  Ap = RED(Ap);
	  ADV(Ap,&a,&Ap);
	  f = ILOG2(a);
	  if (f > fb)
	     fb = f; }
       while (Ap != NIL);

Step2: /* Store coefficients in array. */
       n = PDEG(A);
       g = (fb + n + ZETA - 1) / ZETA;
       m = g * (n + 1);
       if (m <= IPVCHTP_SIZE)
	  P = Ab;
       else
	  P = GETARRAY(m);
       Ap = PRT(A);
       i = 0;
       for (h = n; h >= 0; h--) {
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
	  for (j = 1; j <= g; j++) {
	     if (ap != NIL)
		ADV(ap,&a1,&ap);
	     else
		a1 = 0;
	     P[i] = a1;
	     i = i + 1; } }

Step3: /* Count sign variations while applying synthetic division . */
       k = 0;
       t = 0;
       m = m - 1;
       j = 1;
       while ((j <= n + 1) && (k < 2)) {
	  c = 0;
	  m = m - g;
	  for (i = 0; i <= m; i++) {
	     a1 = P[i] + P[i + g] + c;
	     c = 0;
	     if (a1 >= BETA) {
		a1 = a1 - BETA;
		c = 1; }
	     else
		if (a1 <= -BETA) {
		   a1 = a1 + BETA;
		   c = -1; }
	     P[i + g] = a1; }
	  s = 0;
	  i = m + g;
	  while (s == 0 & i > m) {
	     if (P[i] != 0)
		s = P[i];
	     i = i - 1; }
	  s = signm(s);
	  if (s == - t && t != 0)
	     k = k + 1;
	  if (s != 0)
	     t = s;
	  j = j + 1; }

Step4: /* Free array. */
       if (P != Ab)
	  FREEARRAY(P);

Return: /* Prepare for return. */
       return(k);
}
