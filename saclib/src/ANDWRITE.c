/*===========================================================================
                         ANDWRITE(M,I,n)

Algebraic number decimal write.  

Inputs
  M : an integral minimal polynomial for a real algebraic number alpha.
  I : an acceptable isolating interval for alpha.  
  n : a nonnegative integer.  

Side effects
     A decimal approximation R to alpha is written to the output stream.
     |alpha -  R| <=  1/2 10^{-n}.  The decimal approximation is followed
     by "+" if |R| < |alpha| and "-" if |R| > |alpha|.
===========================================================================*/
#include "saclib.h"

void ANDWRITE(M,I,n)

       Word M,I,n;
{
       Word J,R,Mp,K;
       Word a,a1,a2,b,b1,b2,d,d1,d2,e,f,m;
       Word N;

Step1: /* Rational number. */
       if (PDEG(M) == 1) {
	  R = IUPRLP(M);  RNDWRITE(R,n);  return; };

Step2: /* Interval approximation. */
       J = ISFPIR(M,I,n + 1);

Step3: /* 0 in J? */
       while (RISIGN(J) == NIL) J = IUPIIR(M,J);

Step4: /* Decimal approximation of interval endpoint. */
       FIRST2(J,&a,&b);
       N = IEXP(10,n);  
       if (RISIGN(J) > 0) {
	  FIRST2(a,&a1,&a2);
	  IQR(IPROD(a1,N),a2,&d1,&d2);
	  d = RNRED(d1,N);
	  e = RNSUM(d,LIST2(1,N));
	  f = RNSUM(e,LIST2(1,N)); }
       else {
	  FIRST2(b,&b1,&b2);
	  IQR(IPROD(b1,N),b2,&d1,&d2);  
	  f = RNRED(d1,N);
	  e = RNDIF(f,LIST2(1,N));  
	  d = RNDIF(e,LIST2(1,N)); }

Step5: /* Refine interval until e not in J */
       while ( RNCOMP(e,a) >= 0 && RNCOMP(e,b) <= 0) {
	  J = IUPIIR(M,J);
	  FIRST2(J,&a,&b); }
       if (RNCOMP(b,e) < 0)
	  K = LIST2(d,e);
       else
	  K = LIST2(e,f);

Step6: /* determine which half alpha belongs to. */
       FIRST2(K,&d,&e);
       m = RNQ(RNSUM(d,e),RNINT(2));
       while (RNCOMP(m,a) >= 0 && RNCOMP(m,b) <= 0) {
	  J = IUPIIR(M,J);
	  FIRST2(J,&a,&b); }
       if (RNCOMP(b,m) < 0) {
	  RNDWRITE(d,n);
	  if (RISIGN(J) > 0) CWRITE('+');
	  else               CWRITE('-'); }
       else {
	  RNDWRITE(e,n);
	  if (RISIGN(J) > 0) CWRITE('-');
	  else CWRITE('+'); }

Return: /* Prepare for return. */
       return;
}
