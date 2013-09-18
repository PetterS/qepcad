/*======================================================================
                      DBSTATWR(D,M)

Database Statistics Write.

\Input
  \parm{D} is a database.
  \parm{M} is the header for the output.

\Ouput
  Write the statistics on the database usage.
======================================================================*/
#include "qepcad.h"

void DBSTATWR(Word D, Word M)
{
       Word C1,D1,Dp,K1,T1,f1,i,t;
       /* hide i,t; */

Step1: /* Setup. */
        i = 0;
        SWRITE("\n--------------------------\n");
        CLOUT(M);
        SWRITE("\n--------------------------\n");
        TAB(1); SWRITE("item");
        TAB(10); SWRITE("time");
        TAB(20); SWRITE("#");
        TAB(25); SWRITE("saving\n");
        Dp = CINV(D);
        t = 0;

Step2: /* Write. */
        while (Dp != NIL)
          {
          ADV(Dp,&D1,&Dp);
          FIRST4(D1,&K1,&C1,&T1,&f1); i = i + 1;
          TAB(1); GWRITE(i);
          TAB(10); GWRITE(T1);
          TAB(20); GWRITE(f1);
          TAB(25); GWRITE(T1 * f1);
          SWRITE("\n");
          t = t + T1 * f1;
          }
        TAB(16); SWRITE("Total:");
        TAB(25); GWRITE(t); SWRITE("\n\n");
        goto Return;

Return: /* Prepare for return. */
       return;
}
