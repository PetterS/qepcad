/*===========================================================================
			      B <- MIINV(M,A)

Modular integer inverse.  

Inputs
  M : a positive integer.  
  A : a unit of Z_M.

Output
  B : A^-1.
===========================================================================*/
#include "saclib.h"

Word MIINV(M,A)
       Word M,A;
{
       Word *A1,*A2,*T,*V1,*V2;
       Word B,a0,a1,b0,b1,g1,g2,m1,m2,n1,n2,o,s,t,u1,u2,v1,v2;
       Word Vp1,Vp2,m;

Step1: /* Single-precision input. */
       if (M < BETA) {
	  DEGCD(M,A,&t,&u1,&B);
	  if (B < 0)
	     B = B + M;
	  goto Return; }

Step2: /* Initialize and convert inputs to array representation. */
       m = ILENGTH(M) + 2;
       A1 = GETARRAY(m);
       A2 = GETARRAY(m);
       IFLTA(M,A1,m,&A1,&m1,&s,&o);
       IFLTA(A,A2,m,&A2,&m2,&s,&o);
       V1 = GETARRAY(m);
       V2 = GETARRAY(m);
       IFLTA(0,V1,m,&V1,&n1,&s,&o);
       IFLTA(1,V2,m,&V2,&n2,&s,&o);

Step3: /* Check for completion. */
       if (m2 == 0)
	  goto Step5;

Step4: /* Compute remainders and cosequence elements. */
       g1 = ILOG2A(A1,m1);
       g2 = ILOG2A(A2,m2);
       v1 = 0;
       if (g1 - g2 < ZETA) {
	  if (g1 >= 2 * ZETA) {
	     ILWORDS(A1,m1,A2,m2,&a1,&a0,&b1,&b0);
             DDPCC(a1,a0,b1,b0,&u1,&u2,&v1,&v2); }
	  else if (g1 >= ZETA && g1 - g2 < ZETA / 2) {
	     ILWORD(A1,m1,A2,m2,&a1,&b1);
             DPCC(a1,b1,&u1,&u2,&v1,&v2); }
          else if (g1 < ZETA) {
	     a0 = A1[0];
	     b0 = A2[0];
	     DEGCD(a0,b0,&t,&u1,&v1);
	     Vp1 = IFATL(V1,n1,1);
	     Vp2 = IFATL(V2,n2,1);
	     B = IDIPR2(Vp1,Vp2,u1,v1);
	     if (ISIGNF(B) < 0)
	       B = ISUM(M,B);
	     goto Step6; }
	  else
	     v1 = 0; }
       if (v1 != 0) {
	  if (ISIGNA(V2,n2) == SIGN(v2))
	     s = 1;
	  else
	     s = -1;
	  if (u1 == 0) {
	     ISLCOMB(A1,m1,A2,m2,v2,1,&m1);
	     T = A1; A1 = A2; A2 = T;
	     t = m1; m1 = m2; m2 = t;
	     ISLCOMB(V1,n1,V2,n2,v2,s,&n1);
	     T = V1; V1 = V2; V2 = T;
	     t = n1; n1 = n2; n2 = t; }
	  else {
	     IDLCOMB(A1,m1,A2,m2,u1,v1,u2,v2,1,1,&m1,&m2);
	     IDLCOMB(V2,n2,V1,n1,v2,u2,v1,u1,s,-s,&n2,&n1); } }
       else {
	  IHEAS(A1,m1,A2,m2,V1,n1,V2,n2,&m1,&n1);
	  T = A1; A1 = A2; A2 = T;
	  t = m1; m1 = m2; m2 = t;
	  T = V1; V1 = V2; V2 = T;
	  t = n1; n1 = n2; n2 = t; }
       goto Step3;

Step5: /* Convert output to a list. */
       s = ISIGNA(V1,n1);
       B = IFATL(V1,n1,1);
       if (s < 0)
	  B = ISUM(M,B);

Step6: /* Free arrays. */
       FREEARRAY(A1);
       FREEARRAY(A2);
       FREEARRAY(V1);
       FREEARRAY(V2);

Return: /* Prepare for return. */
       return(B);
}
