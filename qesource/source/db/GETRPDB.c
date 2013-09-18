/*======================================================================
                      GETRPDB(S1,t,U; Ms,Ns)

GETRP with Database.
======================================================================*/
#include "qepcad.h"

void GETRPDB(Word S1, Word t, Word U, Word *Ms_, Word *Ns_)
{
       Word Ms,Ns;

Step1: /* Process. */
       if (PCDBUSE == 'n')
         {
         GETRP(S1,t,U,&Ms,&Ns);
         goto Return;
         }
       if (DBSRCH(DBGETRP,LIST3(S1,t,U)) == 0)
         {
         GETRP(S1,t,U,&Ms,&Ns);
         DBADD(DBGETRP,LIST3(S1,t,U),LIST2(Ms,Ns),&DBGETRP);
         }
       else
         FIRST2(DBINFO,&Ms,&Ns);
       goto Return;

Return: /* Prepare for return. */
       *Ms_ = Ms;
       *Ns_ = Ns;
       return;
}
