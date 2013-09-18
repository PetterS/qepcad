/*======================================================================
                      IPIIWS(A,L)

Integral polynomial isolating intervals weakly disjoint to strongly disjoint.

Inputs
  A : in Z[X], squarefree, def(A) > 0.
  L : a list (I1,...,Ir) of open or one-point isolating intervals for
      real roots of A. 
      Each Ij is a pair (aj,bj) of binary rational numbers,
      with a1 <= b1 <= ... <= ar <= br. 
      Either a1 = b1 or A(a1) /= 0.

Side effects
  The input list L is modified such that 
    (1) L=(J1,...,Jr) is a list of strongly disjoint isolating intervals 
        for real roots of A
    (2) each Jk is a subinterval of Ik. 
    (3) If Ik is a standard interval then 
        Jk is either a one-point or a standard interval.
======================================================================*/
#include "saclib.h"

void IPIIWS(A,L)
       Word A,L;
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
           /* I1<=I2 adjacent. */
           if (RNCOMP(a,b) < 0)
             {
             /* I1 open interval. */
             /* move I1's right end left. */
             b1 = b;
             t = 0;
             do
               {
               c = RNQ(RNSUM(a,b),r2);
               y3 = IUPBES(A,c);
               if (y3 == 0)
                 {
                 /* zero at c */
                 a = c;
                 b1 = c;
                 }
               else
                 {
                 if (t == 0)
                   {
                   y1 = IUPBES(A,a);
                   t = 1;
                   }
                 if (y1 * y3 < 0)
                   b1 = c;
                 else
                   {
                   /* zero right of c */
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
             /* I1 one-point interval */
             /* move I2's left end right. */
             a1 = ap;
             t = 0;
             do
               {
               c = RNQ(RNSUM(ap,bp),r2);
               y3 = IUPBES(A,c);
               if (y3 == 0)
                 {
                 /* zero at c */
                 a1 = c;
                 bp = c;
                 }
               else
                 {
                 if (t == 0)
                   {
                   y1 = IUPBES(IPDER(1,A,1),ap);
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
         /* Now I1<I2 are strongly disjoint. */
         SFIRST(Lp,I1);
         Lp = RED(Lp);
         SFIRST(Lp,I2);
         }

Return: /* Prepare for return. */
       return;
}
