/*======================================================================
                      AFCSBMDB(M,Ps; Bs,Es)

AFCSBM with Database.
======================================================================*/
#include "qepcad.h"

void AFCSBMDB(Word M, Word Ps, Word *Bs_, Word *Es_)
{
       Word Bs,Es;

Step1: /* Process. */
       if (PCDBUSE == 'n')
         {
         AFCSBM(M,Ps,&Bs,&Es);
         goto Return;
         }
       if (DBSRCH(DBAFCSBM,LIST2(M,Ps)) == 0)
         {
         AFCSBM(M,Ps,&Bs,&Es);
         DBADD(DBAFCSBM,LIST2(M,Ps),LIST2(Bs,Es),&DBAFCSBM);
         }
       else
         FIRST2(DBINFO,&Bs,&Es);
       goto Return;

Return: /* Prepare for return. */
       *Bs_ = Bs;
       *Es_ = Es;
       return;
}
