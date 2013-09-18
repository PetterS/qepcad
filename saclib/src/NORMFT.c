/*===========================================================================
		  NORMFT(N,p,Q,Qp,q,K,T; F,Nb)

Norm polynomial factor test.

Inputs
  N  : in Z[x], the norm of a polynomial A[alpha,x] in Z[alpha][x],
       where alpha is an algebraic number.  N is squarefree. 
  p  : an odd medium prime.  
  Q  : a positive power of p.  
  Qp : the floor function of the square root of Q/2.
  q  : a BETA-digit, q = ILOG2(Qp).
  K  : a list of lists of elements of Z/(Q)[x].
  T  : the product of the elements of K evaluated at 1.
  N1 : in Z.  N1 = N(1).

Outputs
  F  : a factor of N (may be = 1).  If the product of
       polynomials in the lists in K is congruent to an
       irreducible monic factor Fs of N with rational
       coefficients such that the numerators and denominators of
       the coefficients are less than Qp in absolute value, then
       F is the positive and primitive polynomial similar to Fs.
  Nb : N divided by F.
===========================================================================*/
#include "saclib.h"

void NORMFT(N,p,Q,Qp,q,K,T,N1, F_,Nb_)
       Word N,p,Q,Qp,q,K,T,N1, *F_,*Nb_;
{
       Word B,F,F1,Fp,Fs,Ft,K1,Kp,Nb,Nt,R,a,b,c,e,r,u;

Step1: /* Initialize. */
       F = PMON(1,0);
       Nb = N;

Step2: /* Convert T to a rational, if possible. */
       r = RNFMRPP(Q,Qp,q,p,T);
       if (r == NIL)
	  goto Return;

Step4: /* Test whether the numerator of r divides N(1), and
          whether the denominator of r divides the leading
	  coefficient of N. */
       a = RNNUM(r);
       if (IREM(N1,a) != 0)
	  goto Return;
       b = RNDEN(r);
       c = PLDCF(N);
       if (IREM(c,b) != 0)
          goto Return;

Step5: /* Compute modular polynomial product. */
       Fp = PMON(1,0);
       Kp = K;
       while (Kp != NIL) {
	  ADV(Kp,&K1,&Kp);
	  while (K1 != NIL) {
	     ADV(K1,&F1,&K1);
	     Fp = MIPPR(1,Q,Fp,F1); } }

Step7: /* Convert Fp to a rational polynomial Fs if possible. */
       Fs = NIL;
       while (Fp != 0) {
	  PADV(Fp,&e,&u,&Fp);
	  r = RNFMRPP(Q,Qp,q,p,u);
	  if (r == NIL)
	     goto Return;
	  b = RNDEN(r);
	  if (IREM(c,b) != 0)
	     goto Return;
	  Fs = COMP2(r,e,Fs); }
       Fs = INV(Fs);

Step8: /* Convert Fs to a primitive integral polynomial Ft. */
       IPSRP(1,Fs,&c,&Ft);

Step9: /* Check if Ft is guaranteed to be irreducible. */
       if (PDEG(Ft) != 1) {
          B = IUPLB(Ft,2);
          if (ICOMP(Q,B) < 0)
	     goto Return; }

Step10: /* Is Ft a factor? */
       IPQR(1,N,Ft,&Nt,&R);
       if (R == 0) {
	  F = Ft;
	  Nb = Nt; }

Return: /* Prepare for return. */
       *F_  = F;
       *Nb_ = Nb;
       return;
}
