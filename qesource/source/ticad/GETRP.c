/*======================================================================
                      GETRP(S1,t,U; Ms,Ns)

Get the representations for alpha and beta 
as elements of Q(alpha + t beta).

\Input
  \parm{S1} 
  \parm{t}
  \parm{U}
  
\Output
  \parm{M*}
  \parm{N*}
======================================================================*/
#include "qepcad.h"

void GETRP(Word S1, Word t, Word U, Word *Ms_, Word *Ns_)
{
       Word C0,C1,D,Ms,Ns,R,Sp1,T,a,e0,e1,q,r;

Step1: /* Reduce coefficients mod S1. */
        FIRST4(U,&e1,&C1,&e0,&C0);
        C1 = RPFIP(1,C1); C0 = RPFIP(1,C0); Sp1 = RPMAIP(1,S1);
        RPQR(1,C1,Sp1,&q,&C1); RPQR(1,C0,Sp1,&q,&C0);

Step2: /* Find similar integral polynomial for leading coefficient. */
        IPSRP(1,C1,&a,&C1); C0 = RPRNP(1,a,C0);

Step3: /* Multiply C_0 by negated inverse of C_1. */
        IUPRC(S1,C1,&T,&r); R = RNRED(1,r); R = RNNEG(R); R = AFFRN(R);
        T = RPFIP(1,T); T = AFCR(T); C0 = AFCR(C0); D = AFPROD(S1,T,C0);
        Ns = AFPROD(S1,R,D);
        Ms = AFPROD(S1,AFFINT(t),Ns); Ms = AFDIF(AFGEN(),Ms);
        goto Return;

Return: /* Prepare for return. */
       *Ms_ = Ms;
       *Ns_ = Ns;
       return;
}
