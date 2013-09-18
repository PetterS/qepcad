/*======================================================================
                      AIFAN(M; mh,Mh)

Algebraic integer from algebraic number. 

Input:
   M : in Z[x], the minimal polynomial for an algebraic number alpha.

Output: 
  mh : in Z. mh = ldcf(M).
  Mh : in Z[x]. Mh = mh^{deg(Mh)-1} M(x/mh).
======================================================================*/
#include "saclib.h"

void AIFAN(M, mh_,Mh_)
       Word M, *mh_,*Mh_;
{
       Word D,Mh,Mp,c,e,f,m,mh;

Step1: /* Compute Mh, mh. */
       Mp = M;
       ADV2(Mp,&f,&mh,&Mp);
       if (mh == 1)
         {
         Mh = M;
         goto Return;
         }
       D = 1;
       Mh = LIST2(1,f);
       f = f - 1;
       do
         {
         ADV2(Mp,&e,&m,&Mp);
         D = IPROD(D,IEXP(mh,f - e));
         f = e;
         c = IPROD(m,D);
         Mh = COMP2(c,e,Mh);
         }
       while (!(Mp == NIL));
       Mh = INV(Mh);

Return: /* Prepare for return. */
       *mh_ = mh;
       *Mh_ = Mh;
       return;
}
