/*======================================================================
                      M <- IPLRRI(L)

Integral polynomial list real root isolation.

Inputs
  L : a non-empty list (A1,...,An) of polynomials in Z[X] which are
      positive, of positive degree, squarefree, and pairwise relatively
      prime.

Outputs
  M : a list (I1,B1,...,Im,Bm), where I1 < I2 < ... < Im 
      are strongly disjoint isolating intervals 
      for all of the real roots of A = A1...An.  
      Each Ii has binary rational number endpoints, and 
      is either left-open and right-closed or is a one-point interval.  
      Bi is the unique Aj which has a root in Ii.
======================================================================*/
#include "saclib.h"

Word IPLRRI(L)
       Word L;
{
       Word A1,A2,B1,I1,I11,I21,Lp,Lpp,M,S,S1,S2,Sp,Spp,Ss1,Ss2,T,T1,
            T2,s;
       /* hide A1,A2,B1,Lp,Lpp,M,Sp,Spp,s; */

Step1: /* Isolate roots of each A_i. */
       Lp = L;
       S = NIL;
       do
         {
         ADV(Lp,&A1,&Lp);
         S1 = IPRIM(A1);
         S = COMP(S1,S);
         }
       while (!(Lp == NIL));
       S = INV(S);

Step2: /* Refine to disjoint isolating intervals. */
       Lp = L;
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
           IPRRLS(A1,A2,S1,S2,&Ss1,&Ss2);
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

Step3: /* Prepare to merge intervals. */
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

Step4: /* Merge-sort isolating intervals. */
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
       M = FIRST(T);

Return: /* Prepare for return. */
       return(M);
}
