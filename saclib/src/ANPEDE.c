/*======================================================================
                      ANPEDE(A,B;C,t)

Algebraic number primitive element for a double extension.            

Inputs
  A : in Z[x].  A is the integral minimal polynomial of an algebraic 
      number alpha.
  B : in Z[x].  B is the integral minimal polynomial of an algebraic 
      number beta.

Outputs
  C : a list (C1,...,Cn), where Ck in Z[x].  Ck is the minimal polynomial
      for a primitive element of the multiple extension field 
      Q(alpha_i,beta_j), where alpha_i and beta_j are conjugates of alpha
      and beta.
  t : in Z.  Q(alpha_i + t beta_j) = Q(alpha_i,beta_j).
======================================================================*/
#include "saclib.h"

Word ANPEDE(A,B, C_,t_)

       Word A,B;
       Word *C_, *t_;
{
       Word C,t;
       Word m,n,Ap,P,Bp,R,Rp,Rb,Rbp,s,c;


Step1: /* A and B have degree 1. */
       t = 0;
       m = PDEG(A);
       n = PDEG(B);
       if (m == 1 && n == 1)
         {
         C = LIST1(PMON(1,1));
         t = 0;
         goto Return;
         }

Step2: /* A or B has degree 1. */
       if (m == 1)
         {
         C = LIST1(B);
         t = 1;
         goto Return;
         }
       if (n == 1)
         {
         C = LIST1(A);
         t = 0;
         goto Return;
         }

Step3: /* Find t such that alpha + t*beta is primitive. */
       t = 1;
       Bp = PINV(1,B,1);
       do {
          P = PBIN(PMON(-t,0),1,PMON(1,1),0);
          Ap = IPGSUB(1,A,2,LIST1(P));
          R = IPRES(2,Ap,Bp);
          Rp = IPDMV(1,R);
          IPGCDC(1,R,Rp,&C,&Rb,&Rbp);
          if (PDEG(C) > 0)
             {
             if (t > 0)
                t = -t;
             else
                t = -t + 1;
             }
          }
       while (PDEG(C) > 0);

Step4: /* Get minimal polynomials for conjugates alpha_i + t*beta_j. */
       IPSCPP(1,R,&s,&c,&R);
       C = IUSFPF(R);

Return:
       *t_ = t;
       *C_ = C;
       return;
}
