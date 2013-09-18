/*======================================================================
                      AMUPRICSW(M,I,A;L,Is)

Algebraic module univariate polynomial real root isolation, 
coefficient sign variation method, weakly disjoint intervals.

Inputs
  M : an element of Z[X].  M(alpha) = 0, is the defining polynomial for 
      Q(alpha).
  I : an isolating interval for alpha.
  A : an element of Z[alpha,X].  A /= 0 and is squarefree in Q(alpha)[X].

Outputs
  L : a list (I_1,...,I_r) of isolating intervals for the real roots of A.
      I_j = (a_j,b_j) is standard open or one-point binary rational interval.
      a_1 <= b_1 <= ... <= a_r <= b_r.
  Is : an acceptable isolating interval for alpha contained in I.
======================================================================*/
#include "saclib.h"

Word AMUPRICSW(M,I,A,L_,Is_)

       Word M,I,A;
       Word *L_,*Is_;
{
       Word L,Is;
       Word As_1,As_2,Ab,ab,I_1,I_2,Ls_1,Ls_2,L_0,L_1,
           L_2,b_1,b_2,m;

Step1: /*[Initialize and check if A(0) = 0.]*/
       m = PDEG(A);
       if (m == 0)
         {
         L = NIL;
         goto Return;
         }
       Ab = PDBORD(A);
       if (PDEG(Ab) < m)
         L_0 = LIST1(LIST2(0,0));
       else
         L_0 = NIL;
       L_1 = NIL;
       L_2 = NIL;

Step2: /*[Isolate positive roots.]*/
       AMUPRBH(M,I,Ab,&b_1,&As_1);
       AMUPRINCS(M,I,As_1,0,RNINT(1),&Ls_1,&Is);
       while (Ls_1 != NIL)
         {
         ADV(Ls_1,&I_1,&Ls_1);
         I_1 = RIRNP(I_1,b_1);
         L_1 = COMP(I_1,L_1);
         }
       L_1 = INV(L_1);

Step3: /* Isolate negative roots. */
       As_2 = AMUPNT(As_1); 
       b_2 = RNNEG(b_1);
       AMUPRINCS(M,Is,As_2,0,RNINT(1),&Ls_2,&Is);
       while (Ls_2 != NIL)
         {
         ADV(Ls_2,&I_2,&Ls_2);
         I_2 = RIRNP(I_2,b_2);
         L_2 = COMP(I_2,L_2);
         }

Step4: /* Combine intervals. */
       L = CONC(L_2,CONC(L_0,L_1));

Return:
       *L_ = L;
       *Is_ = Is;
       return;
}
