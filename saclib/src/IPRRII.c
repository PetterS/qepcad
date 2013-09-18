/*======================================================================
                      L <- IPRRII(A,Ap,d,Lp)

Integral polynomial real root isolation induction.

Inputs
  A  : in Z[X], primitive, positive, deg(A) > 0.
  Ap : the derivative of A.
  d  : a binary rational real root bound for A.
  Lp : an inflectionless isolation list for Ap.

Outputs
  L  : an inflectionless isolation list for A.
======================================================================*/
#include "saclib.h"

Word IPRRII(A,Ap,d,Lp)
       Word A,Ap,d,Lp;
{
       Word Abp,B,B1,B2,I,I1,Ip,Ipp,L,Ls,a1,a2,as1,b0,b1,bs1,c,dp,k,
            m,m1,n,r,r0,r1,s,s1,s2,sbp,sbp1,sp,ss1,t0,t1,tp0,tp1,ts1,
            u,u1,u2,up,up1,us1,v1,vp1,vs1,ws0,ws1,z,z1,z2;
       /* hide B1,B2,I1,Ls,a1,a2,b0,b1,k,m,m1,n,r,r0,r1,s,s1,s2,sbp,
               sbp1,sp,ss1,t0,t1,tp0,tp1,ts1,ws0,ws1; */

Step1: /* A' without roots. */
       dp = RNNEG(d);
       if (Lp == NIL)
         {
         I = LIST2(dp,d);
         L = LIST2(I,1);
         goto Return;
         }

Step2: /* Initialize. */
       Abp = IPPGSD(1,Ap);
       IPGCDC(1,A,Abp,&B,&B1,&B2);
       n = PDEG(A);
       k = PDEG(B);
       Ls = Lp;
       if (EVEN(n))
         t0 = 1;
       else
         t0 = -1;
       tp0 = -t0;
       b0 = dp;
       I1 = FIRST(Ls);
       a1 = FIRST(I1);
       u1 = IUPBRE(A,a1);
       s1 = RNSIGN(u1);
       L = NIL;
       if (t0 * s1 > 0)
         r0 = 0;
       else
         {
         r0 = 1;
         I = LIST2(b0,a1);
         L = COMP2(1,I,L);
         }
       if (EVEN(k))
         ws0 = 1;
       else
         ws0 = -1;
       m = PDEG(Abp);
       if (EVEN(m))
         sbp1 = 1;
       else
         sbp1 = -1;

Step3: /* Root of A in (b_i,a_{i+1}). */
       ADV2(Ls,&I1,&m1,&Ls);
       b1 = SECOND(I1);
       v1 = IUPBRE(A,b1);
       t1 = RNSIGN(v1);
       if (EVEN(m1))
         tp1 = tp0;
       else
         tp1 = -tp0;
       ts1 = t1;
       if (t1 == 0)
         ts1 = tp1;
       if (Ls == NIL)
         a2 = d;
       else
         a2 = FIRST(FIRST(Ls));
       if (RNCOMP(b1,a2) < 0)
         {
         u2 = IUPBRE(A,a2);
         s2 = RNSIGN(u2);
         if (ts1 * s2 <= 0)
           r1 = 1;
         else
           r1 = 0;
         }
       else
         {
         u2 = v1;
         s2 = t1;
         r1 = 0;
         }

Step4: /* alpha_i a root of A. */
       if (k == 0)
         ws1 = ws0;
       else
         {
         ws1 = IUPBES(B,b1);
         if (ws1 == 0)
           ws1 = -ws0;
         }
       if (ws0 * ws1 < 0)
         {
         L = COMP2(m1 + 1,I1,L);
         goto Step9;
         }

Step5: /* Other roots of A in (a_i,b_i). */
       r = r0 + r1;
       if (r == 2)
         goto Step9;
       if (s1 != 0)
         ss1 = s1;
       else
         ss1 = tp0;
       if (r == 1 || EVEN(m1))
         {
         if (ss1 * t1 <= 0)
           goto Step6;
         else
           goto Step9;
         }
       if (t1 == 0)
         {
         if (ss1 * tp0 > 0)
           goto Step6;
         as1 = a1;
         bs1 = b1;
         goto Step8;
         }
       if (ss1 * t1 < 0)
         goto Step6;
       if (ss1 * tp0 > 0)
         goto Step9;
       else
         goto Step7;

Step6: /* One root in (a_i,b_i). */
       I = IPRRRI(A,Abp,I1,ss1,sbp1);
       L = COMP2(1,I,L);
       goto Step9;

Step7: /* Zero or two roots of A in (a_i,b_i). */
       as1 = a1;
       bs1 = b1;
       us1 = u1;
       vs1 = v1;
       up1 = IUPBRE(Ap,as1);
       vp1 = IUPBRE(Ap,bs1);
       if (vp1 == 0)
         goto Step9;
       do
         {
         z = RNQ(us1,up1);
         z1 = RNDIF(as1,z);
         z = RNQ(vs1,vp1);
         z2 = RNDIF(bs1,z);
         z = RNCOMP(z1,z2);
         if (z >= 0)
           goto Step9;
         c = RIB(as1,bs1);
         u = IUPBRE(A,c);
         s = RNSIGN(u);
         up = IUPBRE(Ap,c);
         sp = RNSIGN(up);
         if (ss1 * s > 0 && sp == 0)
           goto Step9;
         if (s == 0 && tp0 * sp < 0)
           {
           bs1 = c;
           goto Step8;
           }
         if (ss1 * s <= 0)
           {
           Ip = LIST2(as1,c);
           Ipp = LIST2(c,bs1);
           if (tp0 * sp <= 0)
             {
             I = IPRRRI(A,Abp,Ip,ss1,sbp1);
             L = COMP4(1,Ipp,1,I,L);
             }
           else
             {
             I = IPRRRI(A,Abp,Ipp,-ss1,sbp1);
             L = COMP4(1,I,1,Ip,L);
             }
           goto Step9;
           }
         if (tp0 * sp > 0)
           {
           as1 = c;
           us1 = u;
           up1 = up;
           }
         else
           {
           bs1 = c;
           vs1 = u;
           vp1 = up;
           }
         }
       while (1);

Step8: /* Roots at b*_i and in (a*_i,b*_i) */
       do
         {
         c = RIB(as1,bs1);
         s = IUPBES(A,c);
         if (ss1 * s <= 0)
           {
           sbp = IUPBES(Abp,c);
           Ip = LIST2(as1,c);
           Ipp = LIST2(c,bs1);
           if (sbp1 * sbp <= 0)
             {
             I = IPRRRI(A,Abp,Ip,ss1,sbp1);
             L = COMP4(1,Ipp,1,I,L);
             }
           else
             {
             I = IPRRRI(A,Abp,Ipp,-ss1,sbp1);
             L = COMP4(1,I,1,Ip,L);
             }
           goto Step9;
           }
         as1 = c;
         }
       while (1);

Step9: /* Update. */
       if (r1 == 1)
         {
         I = LIST2(b1,a2);
         L = COMP2(1,I,L);
         }
       a1 = a2;
       r0 = r1;
       tp0 = tp1;
       s1 = s2;
       ws0 = ws1;
       sbp1 = -sbp1;
       u1 = u2;
       if (Ls != NIL)
         goto Step3;

Step10: /* Finish. */
       L = INV(L);

Return: /* Prepare for return. */
       return(L);
}
