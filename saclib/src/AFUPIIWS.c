/*======================================================================
                      AFUPIIWS(M,I,A,L)

Algebraic number field univariate polynomial isolating intervals 
weakly disjoint to strongly disjoint.

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  I : an acceptable isolating interval for alpha.
  A : in Q(alpha)[x], squarefree, deg(A) > 0.
  L : a list (I1,...,Ir) of open or one-point isolating intervals for
      real roots of A. Each Ij is a pair (aj,bj) of binary rational 
      numbers, with a1 <= b1 <= ... <= ar <= br. Either a1 = b1 or 
      A(a1) not zero.

Side effects
  The input list L is modified such that L = (J1,...,Jr) is a list of
  strongly disjoint isolating intervals for real roots of A such that
  each Jk is a subinterval of Ik. If Ik is a standard interval then 
  Jk is either a one-point or a standard interval.
======================================================================*/
#include "saclib.h"

void AFUPIIWS(M,I,A,L)
       Word M,I,A,L;
{
       Word I1,I2,Lp,a,a1,ap,b,b1,bp,c,r2,t,y1,y3;
       /* hide t,y1,y3; */

Step1: /* Make intervals strongly disjoint. */
       Lp = L;
       r2 = RNINT(2);
       while (L != NIL && RED(Lp) != NIL)
         {
         I1 = FIRST(Lp);
         I2 = SECOND(Lp);
         FIRST2(I1,&a,&b);
         FIRST2(I2,&ap,&bp);
         if (RNCOMP(b,ap) == 0)
           {
           if (RNCOMP(a,b) < 0)
             {
             b1 = b;
             t = 0;
             do
               {
               c = RNQ(RNSUM(a,b),r2);
               y3 = AFSIGN(M,I,AFPEMV(1,M,A,AFFRN(c)));
               if (y3 == 0)
                 {
                 a = c;
                 b1 = c;
                 }
               else
                 {
                 if (t == 0)
                   {
                   y1 = AFSIGN(M,I,AFPEMV(1,M,A,AFFRN(a)));
                   t = 1;
                   }
                 if (y1 * y3 < 0)
                   b1 = c;
                 else
                   {
                   a = c;
                   y1 = y3;
                   }
                 }
               }
             while (!(RNCOMP(b1,b) < 0));
             I1 = LIST2(a,b1);
             }
           else
             {
             a1 = ap;
             t = 0;
             do
               {
               c = RNQ(RNSUM(ap,bp),r2);
               y3 = AFSIGN(M,I,AFPEMV(1,M,A,AFFRN(c)));
               if (y3 == 0)
                 {
                 a1 = c;
                 bp = c;
                 }
               else
                 {
                 if (t == 0)
                   {
                   y1 = AFSIGN(M,I,AFPEMV(1,M,AFPDMV(1,M,A),AFFRN(ap)));
                   t = 1;
                   }
                 if (y1 * y3 > 0)
                   a1 = c;
                 else
                   bp = c;
                 }
               }
             while (!(RNCOMP(ap,a1) < 0));
             I2 = LIST2(a1,bp);
             }
           }
         SFIRST(Lp,I1);
         Lp = RED(Lp);
         SFIRST(Lp,I2);
         }

Return: /* Prepare for return. */
       return;
}
