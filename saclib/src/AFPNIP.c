/*======================================================================
                      L <- AFPNIP(M,A)

Algebraic number field polynomial normalize to integral polynomial.

Inputs
  M  : in Z[x], the minimal polynomial of an algebraic number alpha.
  A : in Q(alpha)[x], deg(A) > 0.

Outputs
  L : a list (L1,...,Ln), n >= 1, of the positive irreducible factors 
      of positive degreee of a univariate integral polynomial which has 
      among its roots the roots of A.
======================================================================*/
#include "saclib.h"

Word AFPNIP(M,A)
       Word M,A;
{
       Word Ap,As,C,L,L1,Lp,Mp,c,d,e,s;
       /* hide c,d,s; */

Step1: /* Convert representation. */
       Ap = A;
       As = NIL;
       while (Ap != NIL)
         {
         ADV2(Ap,&e,&c,&Ap);
         c = AFICR(c);
         As = COMP2(c,e,As);
         }
       As = INV(As);
       IPSRP(2,As,&d,&Ap);

Step2: /* Check for A having only rational coefficients. */
       Ap = PPERMV(2,Ap,LIST2(2,1));
       if (PDEG(Ap) == 0)
         {
         C = PLDCF(Ap);
         goto Step4;
         }

Step3: /* Compute resultant of A and M. */
       Mp = PINV(1,M,1);
       C = IPRES(2,Ap,Mp);

Step4: /* Factor resultant. */
       IPFAC(1,C,&s,&c,&Lp);
       L = NIL;
       do
         {
         ADV(Lp,&L1,&Lp);
         L = COMP(SECOND(L1),L);
         }
       while (!(Lp == NIL));
       L = INV(L);

Return: /* Prepare for return. */
       return(L);
}
