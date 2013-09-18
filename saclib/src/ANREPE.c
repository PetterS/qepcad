/*======================================================================
                     b <- ANREPE(M,A,B,t)

Algebraic number represent element of a primitive extension.

Inputs
  M : in Z[x].  The minimal polynomial for an algebraic
      number gamma.  gamma = alpha + t*beta is a primitive element 
      for the multiple extension Q(alpha,beta).

  A : in Z[x].  A(x) is the minimal polynomial for an algebraic number 
      alpha.
  B : in Z[x].  B(x) is the minimal polynomial for an algebraic number
      beta.
  t : in Z.  gamma = alpha + t*beta is a primitive element.

Outputs
  b :  an element of Q(gamma).  b = beta.
======================================================================*/
#include "saclib.h"

Word ANREPE(M,A,B,t)
       Word M,A,B,t;
{
       Word b;
       Word Ap,Ab,Bp,Bb,P,C;

Step1: /* Construct A(gamma - ty). */
       P = PBIN(PMON(-t,0),1,PMON(1,1),0);
       Ap = IPGSUB(1,A,2,LIST1(P));  Ap = RPFIP(2,Ap);  Ap = AFPCR(1,Ap);
       Bp = PINV(1,B,1);  Bp = RPFIP(2,Bp);  Bp = AFPCR(1,Bp);
       
Step2: /* Compute gcd. */
       AFUPGC(M,Ap,Bp,&C,&Ab,&Bb);

Step3: /* Set b to - trailing coef. of C. */
       b = FOURTH(C);
       b = AFNEG(b);

Return:
       return(b);
}
