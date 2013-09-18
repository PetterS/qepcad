/*======================================================================
                      ESPIWR(T1,T0)

Espresso Input  Write.

\Input
  \parm{T1} is the signature table of solution cells.
  \parm{T0} is the signature table of non-solution cells.
  
\Ouput
  Espresso input is written.
======================================================================*/
#include "qepcad.h"

void ESPIWR(Word T1, Word T0)
{
       Word T01,T011,T11,T111,Tp0,Tp1,i,n;
       /* hide i,n; */

Step1: /* Setup. */
       n = LENGTH(FIRST(T1));
       SWRITE("# MVLMA Input produced by QEPCAD.\n");
       SWRITE(".type fr\n");
       SWRITE(".mv "); GWRITE(n + 1); SWRITE(" 0 ");
       for (i = 1; i <= n; i++) SWRITE("3 ");
       SWRITE("1\n");

Step2: /* Produce ONSET. */
       Tp1 = T1;
       while (Tp1 != NIL)
         {
         ADV(Tp1,&T11,&Tp1);
         while (T11 != NIL)
           {
           ADV(T11,&T111,&T11);
           switch (T111)
             {
             case UNDET: SWRITE(" 111"); break;
             case POSITIVE: SWRITE(" 001"); break;
             case ZERO: SWRITE(" 010"); break;
             case NEGATIVE: SWRITE(" 100"); break;
             }
           }
         SWRITE(" 1\n");
         }

Step3: /* Produce OFFSET. */
       Tp0 = T0;
       while (Tp0 != NIL)
         {
         ADV(Tp0,&T01,&Tp0);
         while (T01 != NIL)
           {
           ADV(T01,&T011,&T01);
           switch (T011)
             {
             case UNDET: SWRITE(" 111"); break;
             case POSITIVE: SWRITE(" 001"); break;
             case ZERO: SWRITE(" 010"); break;
             case NEGATIVE: SWRITE(" 100"); break;
             }
           }
         SWRITE(" 0\n");
         }

Step4: /* End. */
       SWRITE(".e\n");

Return: /* Prepare for return. */
       return;
}






