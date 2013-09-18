/*===========================================================================
			   IPGCDC(r,A,B; C,Ab,Bb)

Integral polynomial greatest common divisor and cofactors.

Inputs
   r : a BETA-digit, r >= 0.
 A,B : in Z[x_1,...,x_r].

Outputs
 C     : in Z[x_1,...,x_r], C = gcd(A,B).
 Ab,Bb : If C is non-zero then 
            Ab = A/C and Bb = B/C.
         Otherwise 
            Ab = 0 and Bb = 0.
======================================================================*/
#include "saclib.h"

void IPGCDC(r,A,B, C_,Ab_,Bb_)
       Word r,A,B, *C_,*Ab_,*Bb_;
{
       Word Ab,Ah,Ahs,Ap,As,Bb,Bh,Bhs,Bp,Bs,C,Chs,Cp,Cs,P,Q,U,Us,
            V,Vs,W,Ws,a,ab,ah,ap,b,bb,bh,bp,c,ch,chp,cp,cpp,cs,d,
            e,f,g,p,q,qp,t;

Step1: /* A = B = 0. */
       if (A == 0 && B == 0) {
	  C = 0;
	  Ab = 0;
	  Bb = 0;
	  goto Return; }

Step2: /* r = 0. */
       if (r == 0) {
	  C = IGCD(A,B);
	  Ab = IEQ(A,C);
	  Bb = IEQ(B,C);
	  goto Return; }

Step3: /* A=0 or B=0. */
       if (A == 0) {
	  C = IPABS(r,B);
	  Ab = 0;
	  Bb = PINV(0,IPSIGN(r,B),r);
	  goto Return; }
       if (B == 0) {
	  C = IPABS(r,A);
	  Bb = 0;
	  Ab = PINV(0,IPSIGN(r,A),r);
	  goto Return; }
       
Step4: /* Compute integer contents and primitive parts. */
       IPICPP(r,A,&a,&Ah);
       IPICPP(r,B,&b,&Bh);
       c = IGCD(a,b);

Step5: /* Compute normalization factor. */
       ah = PLBCF(r,Ah);
       bh = PLBCF(r,Bh);
       ch = IGCD(ah,bh);

Step6: /* Compute norms. */
       d = IPMAXN(r,Ah);
       e = IPMAXN(r,Bh);
       f = IMAX(d,e);
       g = IPROD(IPROD(2,ch),f);

Step7: /* Compute degree vectors. */
       U = PDEGV(r,Ah);
       V = PDEGV(r,Bh);

Step8: /* Initialize prime list and degree vector. */
       P = LPRIME;
       W = COMP(FIRST(U) + 1,RED(U));

Step9: /* Obtain next prime. */
       if (P == NIL)
	  FAIL("IPGCDC","Prime list exhausted",r,A,B);
       ADV(P,&p,&P);

Step10: /* Map normalization factor. */
       cs = MDHOM(p,ch);
       if (cs == 0)
	  goto Step9;

Step11: /* Map Ah and Bh. */
       As = MPHOM(r,p,Ah);
       Us = PDEGV(r,As);
       if (EQUAL(U,Us) == 0)
	  goto Step9;
       Bs = MPHOM(r,p,Bh);
       Vs = PDEGV(r,Bs);
       if (EQUAL(V,Vs) == 0)
	  goto Step9;

Step12: /* Compute g.c.d. */
       MPGCDC(r,p,As,Bs,&Cs,&Ahs,&Bhs);

Step13: /* Test for constant g.c.d. */
       if (IPONE(r,Cs) == 1) {
	  C = PINV(0,c,r);
	  Ab = IPIQ(r,A,c);
	  Bb = IPIQ(r,B,c);
	  goto Return; }

Step14: /* Conditional initialization of chinese remainder process. */
       Ws = PDEGV(r,Cs);
       t = VCOMP(W,Ws);
       if (t >= 2) {
	  Q = 1;
	  Ap = 0;
	  Bp = 0;
	  Cp = 0;
	  W = VMIN(W,Ws); }

Step15: /* Test for unlucky prime. */
       if (t == 1 || t == 3)
	  goto Step9;

Step16: /* Apply chinese remainder algorithm. */
       Chs = MPMDP(r,p,cs,Cs);
       qp = MDINV(p,MDHOM(p,Q));
       Cp = IPCRA(Q,p,qp,r,Cp,Chs);
       Ap = IPCRA(Q,p,qp,r,Ap,Ahs);
       Bp = IPCRA(Q,p,qp,r,Bp,Bhs);
       Q = IPROD(Q,p);
       
Step17: /* Test for completion. */
       if (ICOMP(Q,g) <= 0)
	  goto Step9;
       q = ILOG2(Q);
       cp = ILOG2(IPSUMN(r,Cp));
       ap = ILOG2(IPMAXN(r,Ap));
       bp = ILOG2(IPMAXN(r,Bp));
       cpp = MAX(ap,bp);
       if (q < cp + cpp + 2)
	  goto Step9;

Step18: /* Remove normalization. */
       IPICPP(r,Cp,&cp,&C);
       chp = IEQ(ch,cp);
       Ab = IPIQ(r,Ap,chp);
       Bb = IPIQ(r,Bp,chp);
       C = IPIP(r,c,C);
       ab = IEQ(a,c);
       Ab = IPIP(r,ab,Ab);
       bb = IEQ(b,c);
       Bb = IPIP(r,bb,Bb);

Return: /* Prepare for return. */
       *C_ = C;
       *Ab_ = Ab;
       *Bb_ = Bb;
       return;
}
