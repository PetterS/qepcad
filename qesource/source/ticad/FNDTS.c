/*======================================================================
                      FNDTS(M,N; t,S,U)

Find t such that alpha + t beta is primitive 
 and also find the subresultant.

\Input
  \parm{M} is the minimal polynomial of $\alpha$.
  \parm{N} is the minimal polynomial of $\beta$. 

\Output
  \parm{t} is such that $\alpha + t \beta$ is primtive.
  \parm{S} is .....
  \parm{U} is .....
======================================================================*/
#include "qepcad.h"

void FNDTS(Word M, Word N, Word *t_, Word *S_, Word *U_)
{
       Word C,Mp,Np,P,R,Rb,Rbp,Rp,S,U,W,cs,s,t;
       /* hide s,t; */

Step1: /* Setup. */
        t = 1; Np = PINV(1,N,1);

Step2: /* Find t such that alpha + t beta is primitive. */
        P = PBIN(PMON(-t,0),1,PMON(1,1),0);
        Mp = IPGSUB(1,M,2,LIST1(P));
        R = IPRES(2,Mp,Np);
        Rp = IPDMV(1,R);
        IPGCDC(1,R,Rp,&C,&Rb,&Rbp);
        if (PDEG(C) > 0)
          { if (t > 0) t = -t; else t = -t + 1; goto Step2; }

Step3: /* Factorize R. */
        IPSCPP(1,R,&s,&cs,&R); S = IUSFPF(R);

Step4: /* Get subresultant of degree one of M' and N'. */
        if (PDEG(Mp) > PDEG(Np))
           W = IPSPRS(2,Mp,Np);
        else
           W = IPSPRS(2,Np,Mp);
        W = INV(W);
        U = SECOND(W);
        goto Return;

Return: /* Prepare for return. */
       *t_ = t;
       *S_ = S;
       *U_ = U;
       return;
}
