/*==========================================================================
    IUPLHS(q,Q,Qpp,Ab,Bb,Sb,Tb,Ap,Bp,Yp,Zp,U,D,A,B; Y,Z,Us,As,Bs)

Integral univariate polynomial linear Hensel step.

Inputs
  q : a positive BETA-digit.
  Q : in Z, Q = q^k, k >= 2.
  Qpp : Q / q^2.
  Ab,Bb,Sb,Tb : in Z_q[x] such that Ab*Sb + Bb*Tb = 1, deg(Sb) < deg(Bb),
                deg(Tb) < deg(Ab) and ldcf(Ab) = 1.
  Ap,Bp : in Z_{Q/q}[x], Ab = H_q(Ap), Bp = H_q(Bp).
  Yp,Zp : in Z_q[x] such that A = Ap + (Q/q) Zp, B = Bp + (Q/q) Yp.
  U : in Z[x].  Yp,Zp,U satisy Ab*Yp + Bb*Zp = U (mod q).
  D : in Z_q[x].
  A,B : in Z_Q[x].  A = Ap + (Q/q)Zp, B = Bp + (Q/q)Yp.

Outputs
  Y,Z : in Z_q[x].
  Us : in Z[x].  Y, Z, and U satisfy Ab*Y + Bb*Z = Us (mod q).
  As,Bs : in Z_{qQ}[x].  A = H_Q(As), B = H_Q(Bs) and 
          As*Bs = A*B + Q*D (mod qQ).
==========================================================================*/
#include "saclib.h"

void IUPLHS(q,Q,Qpp,Ab,Bb,Sb,Tb,Ap,Bp,Yp,Zp,U,D,A,B, Y_,Z_,Us_,As_,Bs_)
       Word q,Q,Qpp,Ab,Bb,Sb,Tb,Ap,Bp,Yp,Zp,U,D,A,B, *Y_,*Z_,*Us_,*As_,*Bs_;
{
       Word As,Bs,Uc,Us,V,Vt,Y,Z,t,t1,t2;
       Word *Abp,*Bbp,*Sbp,*Tbp,*Ucp,*Ypp,*Zpp;

Step1: /* Compute Us = D + V/q - Q/q^2 Yp Zp and Uc = Us (mod q). */
       t1 = IPPROD(1,Ap,Yp);
       t2 = IPPROD(1,Bp,Zp);
       t  = IPSUM(1,t1,t2);
       V  = IPDIF(1,U,t);
       Vt = IPEQ(1,V,PMON(q,0));
       t  = IPSUM(1,D,Vt);
       t1 = IPPROD(1,Yp,Zp);
       t2 = IPIP(1,Qpp,t1);
       Us = IPDIF(1,t,t2);
       if (Qpp == 1)
	  Uc = MPHOM(1,q,Us);
       else
	  Uc = MPHOM(1,q,t);

Step2: /* Convert to arrays. */
       Abp = MAPFMUP(Ab);
       Bbp = MAPFMUP(Bb);
       Sbp = MAPFMUP(Sb);
       Tbp = MAPFMUP(Tb);
       Ucp = MAPFMUP(Uc);
       Ypp = MAPGET(MAX(MAPDEG(Bbp) - 1,MAPDEG(Ucp) - MAPDEG(Abp)));
       Zpp = MAPGET(MAPDEG(Abp)-1);

Step3: /* Solve the equation Ab * Y + Bb * Z = Uc for Y and Z. */  
       MAPSE(q,Abp,Bbp,Sbp,Tbp,Ucp, Ypp,Zpp);

Step4: /* Convert to lists and free arrays. */
       Y = MUPFMAP(Ypp);
       Z = MUPFMAP(Zpp);
       MAPFREE(Abp);
       MAPFREE(Bbp);
       MAPFREE(Sbp);
       MAPFREE(Tbp);
       MAPFREE(Ucp);
       MAPFREE(Ypp);
       MAPFREE(Zpp);

Step5: /* Set As = A + Q * Z and Bs = B + Q * Y. */
       As = IPSUM(1,A,IPIP(1,Q,Z));
       Bs = IPSUM(1,B,IPIP(1,Q,Y));

Return: /* Prepare for return. */
       *Y_  = Y;
       *Z_  = Z;
       *Us_ = Us;
       *As_ = As;
       *Bs_ = Bs;
       return;
}
