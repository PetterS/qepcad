/*===========================================================================
                    SIMPLEQE(A,I,B,J;G,s,t,K,a,b,T1,T2)

Simple extension from a multiple extension, QE version.

Inputs
   A : Z[x].  Minimal polynomial for a real algebraic number alpha.
   I : an acceptable isolating interval for alpha.
   B : Q(alpha)[y].  B(alpha,y) is squarefree defining polynomial for a
       real algebraic number beta.
   J : an acceptable isolating interval for beta.
  
Outputs
   G : Z[x].  Minimal polynomial for a real algebraic number gamma.
              Q(gamma) = Q(alpha,beta).
   s,t : in Z.  gamma = s*alpha + t*beta.
   K : an acceptable isolating interval for gamma.
   a : element of Q(gamma).  a = alpha.
   b : element of Q(gamma).  b = beta.
   T1 : Time for AFUPSFNDB.
   T2 : Time for all else.
===========================================================================*/
#include "qepcad.h"

void SIMPLEQE(Word A, Word I, Word B, Word J, Word *G_, Word *s_, Word *t_, Word *K_, Word *a_, Word *b_, Word *T1_, Word *T2_)
{
       Word G,s,t,K,a,b,T1,T2;
       Word F,F1,Fp,Bt,Is,Js,v,vp;
       Word Gt,g,C,Gb,Bp,Bb,Ab,At,x;
       Word Bps,Q,Gs,e,c; /* Chris added 3/16/00 */

Step1: /* Trivial cases. */
       T1 = 0;
       T2 = ACLOCK();                       
       x = AFCR(PMON(RNINT(1),1));
       if (PDEG(A) == 1 && PDEG(B) == 1) {
          G = PMON(1,1);
          K = LIST2(0,0); s = 0; t = 0;
          a = AFFRN(IUPRLP(A));
          b = AFUPRL(A,B);
          goto Step7; }
       if (PDEG(A) == 1 && PDEG(B) > 1) {
          G = AFPICR(1,B);
          G = PLDCF(PTMV(2,G));
          IPSRP(1,G,&g,&G);
          K = J; s = 0; t = 1;
          a = AFFRN(IUPRLP(A));
          b = x;
          goto Step7; }
       if (PDEG(A) > 1 && PDEG(B) == 1) {
          G = A; K = I; s = 1; t = 0; a = x;
          b = AFUPRL(A,B);
          goto Step7; }

Step2: /* Compute squarefree norm. */
       T1 = ACLOCK();
       AFUPSFNDB(A,B,&s,&Bt,&F);
       T1 = ACLOCK() - T1;
       
Step3: /* Find the factor of the norm which has gamma as a root and
          compute an isolating interval for gamma. */
       Is = I; Js = J; vp = 0;
       do {
          K = RISUM(RIRNP(Is,RNINT(s)),Js);
          Fp = F; F = NIL;
          while (Fp != NIL) {
             ADV(Fp,&F1,&Fp);
             v = IUPVOI(F1,K);
             if (v > 0) {
                vp = v;
                F = COMP(F1,F); } }
          if (LENGTH(F) > 1 || vp != 1) {
             Is = IUPIIR(A,Is);
             Js = AFUPIIR(A,Is,B,Js); } }
       while (LENGTH(F) > 1 || vp != 1);
       G = FIRST(F);
       
Step4: /* Q(alpha,beta) = Q(alpha). */
       if (PDEG(G) == PDEG(A)) {
          Gt = AFPFIP(1,G);
          AFUPGCDB(A,Gt,Bt,&C,&Gb,&Bb);
          a = x;  g = AFNEG(PTBCF(1,C)); 
          b = AFDIF(g,AFPROD(A,a,AFFINT(s)));
          G = A; K = I; s = 1; t = 0; 
          goto Step7; }
       
Step5: /* gamma = s*alpha + beta. */
       t = 1;
       At = AFPFIP(1,A);
       Bp = AFPICR(1,Bt);
       Bp = PTMV(2,Bp);

       /* At this point, we're looking to compute
	  GCD(A(x),Bt(x,gamma)) over Q(gamma).  We do this by computing
	  GCD(A(x),Bt(x,y)) over Q[y]/<G(y)>[x], but coefficients of Bt
	  as a polynomial in x over Q[y] might not be reduced to their
	  canonical form as elements in Q[y] of degree less than G(y). So
	  we have to do that reduction to make sure that AFUPGCDR works
	  right. So I'm adding these ... */
       Bps = NIL;
       Gs = RPFIP(1,G);
       for(Bp = CINV(Bp); Bp != NIL; Bp = RED2(Bp)) {
	 FIRST2(Bp,&c,&e);
	 RPQR(1,c,Gs,&Q,&c);
	 if (c != 0)
	   Bps = COMP2(e,c,Bps); }
       Bp = Bps;
       /* ... lines.  3/16/00 */

       Bp = AFPCR(1,Bp);
       AFUPGCDB(G,At,Bp,&C,&Ab,&Bb);
       a = AFNEG(PTBCF(1,C));  g = x;
       b = AFDIF(g,AFPROD(G,a,AFFINT(s)));

Step6: /* Make K an acceptable isolating interval. */
       K = IPSIFI(G,K);

Step7: /* Get total time. */
       T2 = ACLOCK() - T2 - T1;

Return: /* Prepare for return. */
       *G_ = G;
       *s_ = s;
       *t_ = t;
       *K_ = K;
       *a_ = a;
       *b_ = b;
       *T1_ = T1;
       *T2_ = T2;
       return;
}
