/*==========================================================================
                        Bs <- AFPNORM(r,M,B)

Algebraic number field polynomial norm.

Inputs
  M : integral minimal polynomial of an algebraic number alpha.  
  r  : a non-negative BETA-digit.  
  B  : an element of Q(alpha)[x1,...,xr].

Outputs
  Bs : an element of Z[x1,...,xr].  Positive, primitive polynomial 
       similar to the norm of B. 
==========================================================================*/
#include "saclib.h"

Word AFPNORM(r,M,B)
       Word r,M,B;
{
       Word Mp,m,Bp,Bs,R,b;

Step1: /* Convert representation. */
       Bp = AFPICR(r,B);  IPSRP(r+1,Bp,&b,&Bp);

Step2: /* Check for A having only rational coefficients. */
       Bp = PCPV(r+1,Bp,1,r+1);  m = PDEG(M);
       if (PDEG(Bp) == 0) {
         R = PLDCF(Bp);  R = IPEXP(r,R,m);
         goto Step4;
       }

Step3: /* Compute resultant of B and M. */
       Mp = PINV(1,M,r);
       R = IPRES(r + 1,Mp,Bp);  

Step4: /* Compute integral primitive part. */
       Bs = IPABS(r,IPIPP(r,R));

Return: /* Prepare for return. */
       return(Bs);
}
