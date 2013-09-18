/*======================================================================
                      CPLEXN(L; I,M)

Cartesian product, lexicographically next.

Inputs
  L = (L1,L2,...,L_{2n}), n >= 1, is a list such that 
      L_{2i} is a non-null list, and 
      L_{2i-1} is a non-null reductum of L_{2i}, 
      for 1 <= i <= n.

Outputs
  I : is the element (first(L1),first(L3),...,first(L_{2n-1})) of the 
      cartesian product of L2,L4,...,L_{2n}.
  M : If I is not the last element (in the inverse lexicographic ordering)
      of this cartesian product, then M is a list (M1,M2,...,M_{2n}),
      with M_{2i} = L_{2i}, M_{2i-1} a non-null reductum of M_{2i},
      for 1 <= i <= n, and (first(M1),first(M3),...,first(M_{2n-1}))
      the lexicographically next element.
      If I is the last element, then M = ().

Side effects  
  The list L is modified.
======================================================================*/
#include "saclib.h"

void CPLEXN(L, I_,M_)
       Word L, *I_,*M_;
{
       Word A,I,L1,L2,Lp,M,t;
       /* hide A,L1,L2,Lp,t; */

Step1: /* Compute. */
       t = 1;
       I = NIL;
       Lp = L;
       do
         {
         FIRST2(Lp,&L1,&L2);
         if (t == 1)
           {
           ADV(L1,&A,&L1);
           if (L1 != NIL)
             {
             SFIRST(Lp,L1);
             t = 0;
             }
           else
             SFIRST(Lp,L2);
           }
         else
           A = FIRST(L1);
         I = COMP(A,I);
         Lp = RED2(Lp);
         }
       while (!(Lp == NIL));
       I = INV(I);
       if (t == 0)
         M = L;
       else
         M = NIL;

Return: /* Prepare for return. */
       *I_ = I;
       *M_ = M;
       return;
}
