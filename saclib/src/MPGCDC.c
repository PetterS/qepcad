/*======================================================================
                      MPGCDC(r,p,A,B; C,Ab,Bb)

Modular polynomial greatest common divisor and cofactors.

Inputs
   r : a BETA-digit, r > 0.
   p : a BETA-digit, prime.
 A,B : in Z/(p)[X1,...,Xr].

Outputs
  C,Ab,Bb : in Z/(p)[X1,...,Xr], C = gcd(A,B). If C is non-zero then
            Ab = A/C and Bb = B/C.  Otherwise Ab = 0 and Bb = 0.
======================================================================*/
#include "saclib.h"

void MPGCDC(r,p,A,B, C_,Ab_,Bb_)
       Word r,p,A,B, *C_,*Ab_,*Bb_;
{
       Word Ab,Ah,Ahs,Ap,As,Bb,Bh,Bhs,Bp,Bs,C,Chs,Cp,Cs,Q,U,Us,V,Vs,
            W,Ws,a,ab,ah,ap,b,bb,bh,bp,c,ch,chp,cp,cpp,cs,d,e,f,g,qp,
            rp,t;
       /* hide Us,Vs,ap,bp,cp,cpp,d,e,f,g,qp,rp,t; */

Step1: /* A=B=0. */
       if (A == 0 && B == 0)
         {
         C = 0;
         Ab = 0;
         Bb = 0;
         goto Return;
         }

Step2: /* A=0 or B=0. */
       if (A == 0)
         {
         b = PLBCF(r,B);
         C = MPMON(r,p,B);
         Ab = 0;
         Bb = PINV(0,b,r);
         goto Return;
         }
       if (B == 0)
         {
         a = PLBCF(r,A);
         C = MPMON(r,p,A);
         Bb = 0;
         Ab = PINV(0,a,r);
         goto Return;
         }

Step3: /* r=1. */
       if (r == 1)
         {
         C = MUPGCD(p,A,B);
         Ab = MPQ(r,p,A,C);
         Bb = MPQ(r,p,B,C);
         goto Return;
         }

Step4: /* Compute univariate contents and primitive parts. */
       MPUCPP(r,p,A,&a,&Ah);
       MPUCPP(r,p,B,&b,&Bh);
       c = MUPGCD(p,a,b);

Step5: /* Compute normalization factor. */
       rp = r - 1;
       ah = PLBCF(rp,Ah);
       bh = PLBCF(rp,Bh);
       ch = MUPGCD(p,ah,bh);

Step6: /* Compute degrees. */
       U = PDEGV(rp,Ah);
       V = PDEGV(rp,Bh);
       e = PDEGSV(r,Ah,1);
       f = PDEGSV(r,Bh,1);
       g = PDEG(ch) + MAX(e,f);

Step7: /* Initialize element and degree vector. */
       d = -1;
       W = COMP(FIRST(U) + 1,RED(U));

Step8: /* Obtain next element. */
       d = d + 1;
       if (d == p)
         FAIL("MPGCDC","Elements of Z_p exhausted",r,p,A,B);

Step9: /* Map normalization factor. */
       cs = MPEMV(1,p,ch,d);
       if (cs == 0)
         goto Step8;

Step10: /* Map Ah and Bh. */
       As = MPEVAL(r,p,Ah,1,d);
       Us = PDEGV(rp,As);
       if (EQUAL(U,Us) == 0)
         goto Step8;
       Bs = MPEVAL(r,p,Bh,1,d);
       Vs = PDEGV(rp,Bs);
       if (EQUAL(V,Vs) == 0)
         goto Step8;

Step11: /* Compute g.c.d. */
       MPGCDC(rp,p,As,Bs,&Cs,&Ahs,&Bhs);

Step12: /* Test for constant g.c.d. */
       if (IPONE(rp,Cs) == 1)
         {
         C = PINV(0,c,rp);
         Ab = MPUQ(r,p,A,c);
         Bb = MPUQ(r,p,B,c);
         goto Return;
         }

Step13: /* Conditional initialization of interpolation process. */
       Ws = PDEGV(rp,Cs);
       t = VCOMP(W,Ws);
       if (t >= 2)
         {
         Q = LIST2(0,1);
         Ap = 0;
         Bp = 0;
         Cp = 0;
         W = VMIN(W,Ws);
         }

Step14: /* Test for unlucky element. */
       if (t == 1 || t == 3 || t == 0 && PDEG(Q) > g)
         goto Step8;

Step15: /* Interpolate. */
       Chs = MPMDP(rp,p,cs,Cs);
       qp = MDINV(p,MPEMV(1,p,Q,d));
       Cp = MPINT(p,Q,d,qp,r,Cp,Chs);
       Ap = MPINT(p,Q,d,qp,r,Ap,Ahs);
       Bp = MPINT(p,Q,d,qp,r,Bp,Bhs);
       Q = MPPROD(1,p,Q,LIST4(1,1,0,MDNEG(p,d)));

Step16: /* Test for completion. */
       if (PDEG(Q) <= g)
         goto Step8;
       cp = PDEGSV(r,Cp,1);
       ap = PDEGSV(r,Ap,1);
       bp = PDEGSV(r,Bp,1);
       cpp = MAX(ap,bp);
       if (PDEG(Q) <= cp + cpp)
         goto Step8;

Step17: /* Remove normalization. */
       MPUCPP(r,p,Cp,&cp,&C);
       chp = MPQ(1,p,ch,cp);
       Ab = MPUQ(r,p,Ap,chp);
       Bb = MPUQ(r,p,Bp,chp);
       C = MPUP(r,p,c,C);
       ab = MPQ(1,p,a,c);
       Ab = MPUP(r,p,ab,Ab);
       bb = MPQ(1,p,b,c);
       Bb = MPUP(r,p,bb,Bb);

Return: /* Prepare for return. */
       *C_ = C;
       *Ab_ = Ab;
       *Bb_ = Bb;
       return;
}
