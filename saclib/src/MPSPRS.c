/*======================================================================
                      S <- MPSPRS(r,p,A,B)

Modular polynomial subresultant polynomial remainder sequence.

Inputs
   r : a BETA-digit, r > 0.
   p : a BETA-digit, prime.
 A,B : in Z/(p)[X1,...,Xr], deg(A) >= deg(B).

Outputs
  S  : a list of polynomials in Z/(p)[X1,...,Xr], the subresultant P.R.S.
       of the first kind of A and B.
======================================================================*/
#include "saclib.h"

Word MPSPRS(r,p,A,B)
       Word r,p,A,B;
{
       Word G1,G2,G3,Gh3,S,d0,d1,g1,h0,h1,hs0,hs1,i,n1,n2,n3,rp;
       /* hide d0,d1,i,n1,n2,n3,rp; */

Step1: /* Initialize. */
       G1 = A;
       G2 = B;
       S = LIST2(G2,G1);
       n1 = PDEG(G1);
       n2 = PDEG(G2);
       d0 = 0;
       d1 = n1 - n2;
       rp = r - 1;
       i = 1;

Step2: /* Compute Gh_{i+2}. */
       Gh3 = MPPSR(r,p,G1,G2);
       if (Gh3 == 0)
         {
         S = INV(S);
         goto Return;
         }
       if (EVEN(d1) == 1)
         Gh3 = MPNEG(r,p,Gh3);
       n3 = PDEG(Gh3);

Step3: /* Compute hi. */
       if (i > 1)
         {
         g1 = PLDCF(G1);
         h1 = MPEXP(rp,p,g1,d0);
         if (i > 2)
           {
           hs0 = MPEXP(rp,p,h0,d0 - 1);
           h1 = MPQ(rp,p,h1,hs0);
           hs0 = 0;
           }
         }

Step4: /* Compute G_{i+2}. */
       if (i == 1)
         G3 = Gh3;
       else
         {
         hs1 = MPEXP(rp,p,h1,d1);
         hs1 = MPPROD(rp,p,g1,hs1);
         hs1 = LIST2(0,hs1);
         G3 = MPQ(r,p,Gh3,hs1);
         hs1 = 0;
         Gh3 = 0;
         }

Step5: /* Update. */
       S = COMP(G3,S);
       n1 = n2;
       n2 = n3;
       d0 = d1;
       d1 = n1 - n2;
       G1 = G2;
       G2 = G3;
       if (i > 1)
         h0 = h1;
       i = i + 1;
       goto Step2;

Return: /* Prepare for return. */
       return(S);
}
