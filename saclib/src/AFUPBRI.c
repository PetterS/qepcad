/*======================================================================
                      N <- AFUPBRI(M,I,L)

Algebraic number field univariate polynomial basis real root isolation.

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  I : an acceptable isolating interval for alpha.  
  L : a list of elements (A1,...,An) of elements of Q(alpha)[x].
      L is a nonempty squarefree basis.

Outputs
  N : a list (I1,B1,...,Im,Bm), m >= 0, where I1 < I2 < ... < Im 
      are  strongly disjoint isolating intervals for all the real 
      roots of A = A1 * ... * An. Each Ii has binary rational endpoints 
      and is left open and right closed. Bi is the unique Aj which has 
      a root in Ii.
======================================================================*/
#include "saclib.h"

Word AFUPBRI(M,I,L)
       Word M,I,L;
{
       Word A1,A2,B1,I1,I11,I21,Lp,Lpp,N,S,S1,S2,Sp,Spp,Ss1,Ss2,T,T1,
            T2,s;
       Word At1,at1,Lt;
       /* hide A1,A2,B1,Lp,Lpp,Sp,Spp,s; */

Step1: /* Compute Ati, an element of Z[alpha,x], similar to Ai. */
       Lp = L;
       Lt = NIL;
       do
         {
         ADV(Lp,&A1,&Lp);
         At1 = AMPSAFP(1,A1);
         Lt = COMP(At1,Lt);
         }
       while (!(Lp == NIL));
       Lt = INV(Lt);

Step2: /* Isolate roots of each Ati. */
       Lp = Lt;
       S = NIL;
       do
         {
         ADV(Lp,&At1,&Lp);
         S1 = AMUPRICS(M,I,At1);
         S = COMP(S1,S);
         }
       while (!(Lp == NIL));
       S = INV(S);

Step3: /* Refine to disjoint isolating intervals. */
       Lp = Lt;
       Sp = S;
       while (RED(Lp) != NIL)
         {
         A1 = FIRST(Lp);
         S1 = FIRST(Sp);
         Lpp = RED(Lp);
         Spp = RED(Sp);
         do
           {
           A2 = FIRST(Lpp);
           S2 = FIRST(Spp);
           AMUPRLS(M,I,A1,A2,S1,S2,&Ss1,&Ss2);
           S1 = Ss1;
           SFIRST(Spp,Ss2);
           Lpp = RED(Lpp);
           Spp = RED(Spp);
           }
         while (!(Lpp == NIL));
         SFIRST(Sp,S1);
         Lp = RED(Lp);
         Sp = RED(Sp);
         }

Step4: /* Prepare to merge intervals. */
       Lp = L;
       Sp = S;
       T = NIL;
       do
         {
         ADV(Lp,&A1,&Lp);
         ADV(Sp,&S1,&Sp);
         T1 = NIL;
         while (S1 != NIL)
           {
           ADV(S1,&I11,&S1);
           T1 = COMP2(A1,I11,T1);
           }
         T = COMP(INV(T1),T);
         }
       while (!(Lp == NIL));
       T = INV(T);

Step5: /* Merge-sort isolating intervals. */
       while (RED(T) != NIL)
         {
         S = NIL;
         while (T != NIL && RED(T) != NIL)
           {
           ADV2(T,&T1,&T2,&T);
           S1 = NIL;
           while (T1 != NIL && T2 != NIL)
             {
             I11 = FIRST(T1);
             I21 = FIRST(T2);
             s = RNCOMP(FIRST(I11),FIRST(I21));
             if (s < 0)
               ADV2(T1,&I1,&B1,&T1);
             else
               ADV2(T2,&I1,&B1,&T2);
             S1 = COMP2(B1,I1,S1);
             }
           if (T1 == NIL)
             T1 = T2;
           S1 = CONC(INV(S1),T1);
           S = COMP(S1,S);
           }
         if (T != NIL)
           S = COMP(FIRST(T),S);
         T = INV(S);
         }
       N = FIRST(T);

Return: /* Prepare for return. */
       return(N);
}
