/*======================================================================
                      DBADD(D,K,C; Dp)

Database Add.

\Input
  \parm{D} is the database where an item is to be added.
  \parm{K} is the key of the item to be added.
  \parm{C} is the information of the item to be added.

\Output
  \parm{D'} is obtained from $D$ by adding the new item.
======================================================================*/
#include "qepcad.h"

void DBADD(Word D, Word K, Word C, Word *Dp_)
{
       Word D1,Dp,T;
       /* hide T; */

Step1: /* Add. */
       T = ACLOCK() - DBTIME;
       if (T < PCDBLIMIT) { Dp = D; goto Return; }
       D1 = LIST4(K,C,T,0);
       Dp = COMP(D1,D);
       goto Return;

Return: /* Prepare for return. */
       *Dp_ = Dp;
       return;
}
