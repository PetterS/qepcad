/*======================================================================
                      Ls <- IIC(A,Ap,I,L)

Isolating interval conversion.

Inputs
  A : in Z[X], squarefree.
  Ap : in Z[X], the derivative of A.
  I : a left open right closed interval (a,b) with binary rational
      endpoints represented by the list (a,b).
  L : a list of isolating intervals with binary rational 
      endpoints for the real roots of A in I.
      L=((a1,b1),...,(ak,bk)) with a1 <= b1 <= ... <= ak <= bk and
      (ai,bi) represents the open interval (ai,bi) if ai < bi,
      the closed interval (ai,bi) if ai = bi.

Outputs
  Ls : a list ((as_1,bs_1),...,as_k,bs_k)) of isolating intervals
       for the same roots and satisfying the same conditions
       except that each pair (as_i,bs_i) represents the left open
       right closed interval (as_i,bs_i).
======================================================================*/
#include "saclib.h"

Word IIC(A,Ap,I,L)
       Word A,Ap,I,L;
{
       Word I1,I2,Lp,Ls,a1,a2,b1,b2,c,s,s1;
       /* hide I1,I2,a1,a2,b1,b2,s,s1; */

Step1: /* Initialize. */
       Lp = CINV(L);
       Ls = NIL;

Step2: /* Finish. */
       if (Lp == NIL)
         goto Return;

Step3: /* I2 open. */
       ADV(Lp,&I2,&Lp);
       FIRST2(I2,&a2,&b2);
       s = RNCOMP(a2,b2);
       if (s != 0)
         {
         Ls = COMP(I2,Ls);
         goto Step2;
         }

Step4: /* L' empty. */
       if (Lp == NIL)
         {
         a2 = FIRST(I);
         Ls = COMP(LIST2(a2,b2),Ls);
         goto Return;
         }

Step5: /* I1 not adjacent. */
       I1 = FIRST(Lp);
       FIRST2(I1,&a1,&b1);
       s = RNCOMP(b1,a2);
       if (s != 0)
         {
         a2 = b1;
         Ls = COMP(LIST2(a2,b2),Ls);
         goto Step3;
         }

Step6: /* Bisect I1. */
       Lp = RED(Lp);
       s1 = IUPBES(A,a1);
       if (s1 == 0)
         s1 = IUPBES(Ap,a1);
       c = a1;
       do
         {
         c = RIB(c,b1);
         s = IUPBES(A,c);
         }
       while (!(s1 * s <= 0));

Step7: /* Adjoint two intervals. */
       Ls = COMP(LIST2(c,b1),Ls);
       Ls = COMP(LIST2(a1,c),Ls);
       goto Step2;

Return: /* Prepare for return. */
       return(Ls);
}
