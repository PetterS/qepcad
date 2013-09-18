/*===========================================================================
                      T <- RNSUM(R,S)

Rational number sum.  

Inputs
  R,S : rational numbers.  

Outputs
  T   : R + S.
===========================================================================*/
#include "saclib.h"

Word RNSUM(R,S)
       Word R,S;
{
       Word D,E,R1,R2,Rb2,S1,S2,Sb2,T,T1,T2;

Step1: /* R=0 or S=0. */
       if (R == 0) {
	  T = S;
         goto Return; }
       if (S == 0) {
	  T = R;
	  goto Return; }

Step2: /* Obtain numerators and denominators. */
       FIRST2(R,&R1,&R2);
       FIRST2(S,&S1,&S2);

Step3: /* R and S integers. */
       if (R2 == 1 && S2 == 1) {
	  T1 = ISUM(R1,S1);
	  if (T1 == 0)
	     T = 0;
	  else
	     T = LIST2(T1,1);
	  goto Return; }

Step4: /* R or S an integer. */
       if (R2 == 1) {
	  T1 = IPROD(R1,S2);
	  T1 = ISUM(T1,S1);
	  T = LIST2(T1,S2);
	  goto Return; }
       if (S2 == 1) {
	  T1 = IPROD(R2,S1);
	  T1 = ISUM(T1,R1);
	  T = LIST2(T1,R2);
	  goto Return; }

Step5: /* General case. */
       IGCDCF(R2,S2,&D,&Rb2,&Sb2);
       T1 = ISUM(IPROD(R1,Sb2),IPROD(Rb2,S1));
       if (T1 == 0) {
	  T = 0;
	  goto Return; }
       if (D != 1) {
	  E = IGCD(T1,D);
	  if (E != 1) {
	     T1 = IEQ(T1,E);
	     R2 = IEQ(R2,E); } }
       T2 = IPROD(R2,Sb2);
       T = LIST2(T1,T2);

Return: /* Prepare for return. */
       return(T);
}
