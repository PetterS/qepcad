/*======================================================================
                      ANIIPE(M,I,N,J,t,L; S,k,K)

Algebraic number isolating interval for a primitive element.

Input:
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  I : a binary rational isolating interval for alpha which is either
      left-open and right-closed or a one-point interval.
  N : in Z[x], the minimal polynomial of a real algebraic number beta.  
  J : a binary rational isolating interval for beta which is either 
      left-open and right-closed or a one-point interval.
  t : in Z, Q(alpha + t * beta) = Q(alpha,beta). 
  L : a list of elements of Z[x].
      If degree(M) = 1 and degree(N) = 1, then 
          L = (P), where P is primitive, positive, and of degree 1.
      If degree(M) = 1, degree(N) > 1, then 
          L = (N). 
      If degree(M) > 1, degree(N) = 1, then 
          L = (M),.
      If degree(M) > 1, degree(N) > 1, then 
          L = a nonempty list of positive irreducible univariate 
          integral polynomials exactly one of which has 
          alpha + t * beta as a root. 

Output:
  S : in Z[x].
  k : a BETA-digit.
  K : a binary rational interval.
      If degree(M) = 1 and degree(N) = 1, then 
        S = P, 
        k = 1,
        K = a binary rational isolating interval for the real root
            of P which is either left-open and right-closed or a
            one-point interval.  
      If degree(M) = 1, degree(N) > 1, then 
        S = N, 
        k = 1, 
        K = J.
      If degree(M) > 1, degree(N) = 1, then 
        S = M, 
        k = 1,
        K = I.  
      If degree(M) > 1, degree(N) > 1, then       
        S = the element of L having alpha + t * beta as a root, 
        k = the index of S in L,
        K = a left-open, right-closed binary rational isolating
            interval for alpha + t * beta as a root of S.
======================================================================*/
#include "saclib.h"

void ANIIPE(M,I,N,J,t,L, S_,k_,K_)
       Word M,I,N,J,t,L, *S_,*k_,*K_;
{
       Word Jp,Js,K,L1,Lp,S,a,b,c,cs,d,ds,e,k,kp,m,n,s1,s2,sp,tp,v,
            vp;
       /* hide L1,Lp,cs,ds,k,kp,m,n,s1,s2,sp,v,vp; */

Step1: /* M or N has degree 1. */
       k = 1;
       m = PDEG(M);
       n = PDEG(N);
       if (m == 1 && n == 1)
         {
         S = FIRST(L);
         K = IPRIM(S);
         K = FIRST(K);
         goto Return;
         }
       if (m == 1)
         {
         S = N;
         K = J;
         goto Return;
         }
       if (n == 1)
         {
         S = M;
         K = I;
         goto Return;
         }

Step2: /* Initialization. */
       FIRST2(I,&a,&b);
       s1 = IUPBES(M,b);
       Jp = J;
       FIRST2(J,&c,&d);
       s2 = IUPBES(N,d);
       tp = RNINT(t);

Step3: /* Make new interval. */
       Js = RIRNP(Jp,tp);
       FIRST2(Js,&cs,&ds);
       K = LIST2(RNSUM(a,cs),RNSUM(b,ds));

Step4: /* Test for real roots of each Li in current interval. */
       v = 0;
       kp = 0;
       Lp = L;
       do
         {
         ADV(Lp,&L1,&Lp);
         kp = kp + 1;
         vp = IUPVOI(L1,K);
         if (vp > 1)
           goto Step5;
         if (vp == 1)
           if (v == 1)
             goto Step5;
           else
             {
             v = 1;
             S = L1;
             k = kp;
             }
         }
       while (!(Lp == NIL));
       goto Return;

Step5: /* Bisect isolating intervals for alpha and beta. */
       e = RIB(a,b);
       sp = IUPBES(M,e);
       if (sp * s1 < 0)
         a = e;
       else
         {
         b = e;
         s1 = sp;
         }
       e = RIB(c,d);
       sp = IUPBES(N,e);
       if (sp * s2 < 0)
         c = e;
       else
         {
         d = e;
         s2 = sp;
         }
       Jp = LIST2(c,d);
       goto Step3;

Return: /* Prepare for return. */
       *S_ = S;
       *k_ = k;
       *K_ = K;
       return;
}
