/*======================================================================
                      DIPINS(a,d,A; t,B)

Distributive polynomial, insert term.

Inputs
  A  : in Z[X1,...,Xr], distributive representation 
       r >= 0, or the null list.
  a  : in Z, the coefficient of the term in r variables
       to be inserted.
  d  : the degree vector of the term in r variables
       to be inserted.


Outputs
  t  : an integer, t = 1 if d does not already occur in A,
       t = 0 if d already occurs in A.
  B  : in Z[X1,...,Xr] the distributive polynomial 
       resulting from inserting the term.     
       If d does already occur in A, then B = A.
======================================================================*/
#include "saclib.h"

void DIPINS(a,d,A, t_,B_)
       Word a,d,A, *t_,*B_;
{
       Word Ap,B,ap,b,dp,t;
       /* hide Ap,ap,b,dp,t; */

Step1: /* A empty. */
       t = 1;
       if (A == NIL)
         {
         B = LIST2(a,d);
         goto Return;
         }
       B = A;

Step2: /* A nonempty. */
       Ap = A;
       ADV2(Ap,&ap,&dp,&Ap);
       b = DVCMP(d,dp);
       if (b == 0)
         {
         t = 0;
         goto Return;
         }
       if (b > 0)
         {
         B = COMP2(a,d,A);
         goto Return;
         }
       B = LIST2(dp,ap);
       while (Ap != NIL)
         {
         ADV2(Ap,&ap,&dp,&Ap);
         b = DVCMP(d,dp);
         if (b == 0)
           {
           B = A;
           t = 0;
           goto Return;
           }
         if (b > 0)
           {
           B = COMP4(dp,ap,d,a,B);
           B = INV(B);
           B = CONC(B,Ap);
           goto Return;
           }
         B = COMP2(dp,ap,B);
         }
       B = COMP2(d,a,B);
       B = INV(B);

Return: /* Prepare for return. */
       *t_ = t;
       *B_ = B;
       return;
}
