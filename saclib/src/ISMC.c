/*===========================================================================
                           R <- ISMC(M,Mp,m,U)

Integer solution of modular congruence.

Inputs
  M : in Z, M > 1, M odd (that M is odd is used in inequality tests).
  Mp: in Z, Mp = floor((M/2)^(1/2)).
  m : in Z, m = ILOG2(Mp).
  U : in Z, 0 <= U < M.

Outputs
  R ; if U = 0 then R = 0.  Otherwise, if there exist integers
      A > 0 and B /= 0 such that |A|, B < (M/2)^(1/2) and 
      A = B U (mod M) then R = (A,B), but if not then R = NIL.
===========================================================================*/
#include "saclib.h"

Word ISMC(M,Mp,m,U)
       Word M,Mp,m,U;
{
       Word *A1,*A2,*V1,*V2,*W,*T;
       Word A,B,R,a0,a1,b0,b1,c,cp,d,g1,g2,m1,m2,n1,n2,s,t,u1,u2,v1,v2,w;

Step1: /* U = 0. */
       if (U == 0) {
          R = 0;
          goto Return; }

Step2: /* Single-precision input. */
       if (M < BETA) {
          R = DSMC(M,Mp,U);
          goto Return; }

Step3: /* Initialize and convert to array representation. */
       R = 0;
       m1 = ILENGTH(M) + 2;
       m2 = ILENGTH(U) + 2;
       A1 = GETARRAY(m1);
       A2 = GETARRAY(m2);
       IFLTA(M,A1,m1,&A1,&m1,&d,&d);
       IFLTA(U,A2,m2,&A2,&m2,&d,&d);
       w = ILENGTH(Mp);
       W = GETARRAY(w);
       IFLTA(Mp,W,w,&W,&w,&d,&d);
       n1 = n2 = w + 2;
       V1 = GETARRAY(n1);
       V2 = GETARRAY(n2);
       IFLTA(0,V1,n1,&V1,&n1,&d,&d);
       IFLTA(1,V2,n2,&V2,&n2,&d,&d);

Step4: /* Check for completion. */
       if (IACOMPA(V2,n2,W,w) > 0) {
          R = NIL;
          goto Step7; }
       if (IACOMPA(A2,m2,W,w) <= 0)
          goto Step7;

Step5: /* Compute remainder and cosequence. */
       c = m - ILOG2A(V2,n2) - 1;
       g1 = ILOG2A(A1,m1);
       g2 = ILOG2A(A2,m2);
       v1 = 0;
       if (g1 - g2 < ZETA) {
          cp = 1 << MAX(c-1,0);
          if (g1 >= 2 * ZETA && c > ZETA / 2) {
             ILWORDS(A1,m1,A2,m2,&a1,&a0,&b1,&b0);
             if (c > ZETA)
                DDPCC(a1,a0,b1,b0,&u1,&u2,&v1,&v2);
             else
                DDRPCC(cp,a1,a0,b1,b0,&u1,&u2,&v1,&v2); }
          else if (g1 >= ZETA && g1 - g2 < ZETA / 2) {
             ILWORD(A1,m1,A2,m2,&a1,&b1);
             if (c > ZETA / 2)
                DPCC(a1,b1,&u1,&u2,&v1,&v2);
             else
                DRPCC(cp,a1,b1,&u1,&u2,&v1,&v2); } }
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
       goto Step4;

Step7: /* Form output. */
       if (R != NIL) {
          if (ISIGNA(A2,m2) == 0)
             R = NIL;
          else {
             if (ISIGNA(V2,n2) < 0) {
                A = IFATL(A2,m2,-1);
                B = IFATL(V2,n2,-1); }
             else {
                A = IFATL(A2,m2,1); 
                B = IFATL(V2,n2,1); }
             R = LIST2(A,B); } }

Step8: /* Free arrays. */
       FREEARRAY(A1);
       FREEARRAY(A2);
       FREEARRAY(W);
       FREEARRAY(V1);
       FREEARRAY(V2);

Return: /* Prepare for return. */
       return(R);
}

