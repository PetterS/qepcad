/*======================================================================
                      t <- MEMBER(a,L)

Membership test.

Inputs
  a  : object
  L  : list.

Outputs
  t  : an integer.
       t has the value 1 if a is a member of L, otherwise has the value 0.
======================================================================*/
#include "saclib.h"

Word MEMBER(a,L)
       Word a,L;
{
       Word Lp,a1,t;
       /* hide algorithm */

Step1: /* Test. */
       t = 0;
       Lp = L;
       while (Lp != NIL)
         {
         ADV(Lp,&a1,&Lp);
         t = EQUAL(a,a1);
         if (t == 1)
           goto Return;
         }

Return: /* Prepare for return. */
       return(t);
}
