/*======================================================================
                      FNDTSDB(Mb,Nb; t,S,U)

FNDTS with Database.
======================================================================*/
#include "qepcad.h"

void FNDTSDB(Word Mb, Word Nb, Word *t_, Word *S_, Word *U_)
{
       Word S,U,t;
       /* hide t; */

Step1: /* Process. */
       if (PCDBUSE == 'n')
         {
         FNDTS(Mb,Nb,&t,&S,&U);
         goto Return;
        }
       if (DBSRCH(DBFNDTS,LIST2(Mb,Nb)) == 0)
         {
         FNDTS(Mb,Nb,&t,&S,&U);
         DBADD(DBFNDTS,LIST2(Mb,Nb),LIST3(t,S,U),&DBFNDTS);
         }
       else
         FIRST3(DBINFO,&t,&S,&U);
       goto Return;

Return: /* Prepare for return. */
       *t_ = t;
       *S_ = S;
       *U_ = U;
       return;
}
