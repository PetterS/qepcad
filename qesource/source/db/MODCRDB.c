/*======================================================================
                      MODCRDB(b,S1,Ms,Ns; b1)

MODCR with Database.
======================================================================*/
#include "qepcad.h"

void MODCRDB(Word b, Word S1, Word Ms, Word Ns, Word *b1_)
{
       Word b1;

Step1: /* Process. */
       if (PCDBUSE == 'n')
         {
         MODCR(b,S1,Ms,Ns,&b1);
         goto Return;
         }
       if (DBSRCH(DBMODCR,LIST4(b,S1,Ms,Ns)) == 0)
         {
         MODCR(b,S1,Ms,Ns,&b1);
         DBADD(DBMODCR,LIST4(b,S1,Ms,Ns),LIST1(b1),&DBMODCR);
         }
       else
         b1 = FIRST(DBINFO);
       goto Return;

Return: /* Prepare for return. */
       *b1_ = b1;
       return;
}
