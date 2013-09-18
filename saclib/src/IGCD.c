/*===========================================================================
                               C <- IGCD(A,B)

Integer greatest common divisor.

Inputs
  A,B : in Z.

Outputs
  C : gcd(A,B).
===========================================================================*/
#include "saclib.h"

Word IGCD(A,B)
       Word A,B;
{
       Word *A1,*A2,*T,C,a,a0,a1,b,b0,b1,d,g1,g2,m1,m2,t,u1,u2,v1,v2;

Step1: /* Single-precision input. */
       if (A < BETA && B < BETA) {
	  a = absm(A);
	  b = absm(B);
	  if (a > b)
	     C = DGCD(a,b);
	  else
	     C = DGCD(b,a);
	  goto Return; }

Step2: /* Initialize and convert to array representation. */
       m1 = ILENGTH(A) + 2;
       m2 = ILENGTH(B) + 2;
       A1 = GETARRAY(m1);
       A2 = GETARRAY(m2);
       IFLTA(A,A1,m1,&A1,&m1,&d,&d);
       IFLTA(B,A2,m2,&A2,&m2,&d,&d);

Step3: /* Swap if necessary. */
       if (IACOMPA(A1,m1,A2,m2) < 0) {
	  T = A1;
	  t = m1;
	  A1 = A2;
	  m1 = m2;
	  A2 = T;
	  m2 = t; }

Step4: /* Compute remainders. */
       while (ISIGNA(A2,m2) != 0) {
	  if (m1 == 1) {
	     C = DGCD(A1[0],A2[0]);
	     A1[0] = C;
	     goto Step5; }
	  g1 = ILOG2A(A1,m1);
	  g2 = ILOG2A(A2,m2);
	  v1 = 0;
	  if (g1 - g2 < ZETA)
	     if (g1 >= 2 * ZETA) {
		ILWORDS(A1,m1,A2,m2,&a1,&a0,&b1,&b0);
		DDPCC(a1,a0,b1,b0,&u1,&u2,&v1,&v2); }
	     else if (g1 - g2 < ZETA / 2) {
		ILWORD(A1,m1,A2,m2,&a1,&b1);
		DPCC(a1,b1,&u1,&u2,&v1,&v2); }
	  if (v1 != 0)
	     IDLCOMB(A1,m1,A2,m2,u1,v1,u2,v2,1,1,&m1,&m2);
	  else {
	     IEAS(A1,m1,A2,m2,&m1);
	     T = A1;
	     t = m1;
	     A1 = A2;
	     m1 = m2;
	     A2 = T;
	     m2 = t; } }
	  
Step5: /* Convert gcd to list representation and free arrays. */
       C = IFATL(A1,m1,1);
       FREEARRAY(A1);
       FREEARRAY(A2);

Return: /* Prepare for return. */
       return(C);
}
