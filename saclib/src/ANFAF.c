/*===========================================================================
                         ANFAF(M,I,a; N,J)

Algebraic number from algebraic number field element.  

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  I : an acceptable isolating interval for alpha.  
  a : in Q(alpha).  

Outputs
  N : in Z[x]. N is the minimal polynomial of a.
  J : an acceptable isolating interval for a.
===========================================================================*/
#include "saclib.h"

void ANFAF(M,I,a, N_,J_)
       Word M,I,a, *N_,*J_;
{
       Word A,B,C,J,L,N,as,b1,b2,d,s1,s2,u1,u2,v1,v2;

Step1: /* a rational. */
       if (a == 0) {
	  N = PMON(1,1);
	  J = LIST2(0,0);
	  goto Return; }
       as = AFICR(a);
       if (PDEG(as) == 0) {
	  N = PBIN(RNINT(-1),1,SECOND(as),0);
	  IPSRP(1,N,&d,&N);
	  L = IPRIM(N);
	  J = FIRST(L);
	  goto Return; }

Step2: /* Find minimal polynomial. */
       A = PBIN(PMON(RNINT(-1),0),1,as,0);
       IPSRP(2,A,&d,&A);
       A = PPERMV(2,A,LIST2(2,1));
       B = PINV(1,M,1);
       C = IPRES(2,A,B);
       N = IPPGSD(1,C);

Step3: /* Find acceptable isolating interval. */
       L = IPRIM(N);
       do {
	  ADV(L,&J,&L);
	  FIRST2(J,&u1,&u2);
	  v1 = AFFRN(u1);
	  v2 = AFFRN(u2);
	  b1 = AFDIF(a,v1);
	  b2 = AFDIF(a,v2);
	  s1 = AFSIGN(M,I,b1);
	  s2 = AFSIGN(M,I,b2);
	  if (s1 * s2 == -1)
	     goto Return; }
       while (1);

Return: /* Prepare for return. */
       *N_ = N;
       *J_ = J;
       return;
}
