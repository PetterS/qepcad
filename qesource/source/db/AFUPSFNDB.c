/*======================================================================
                      AFUPSFNDB(M,B;t,Bt,F)

AFUPSFN with Database.
======================================================================*/
#include "qepcad.h"

Word AFUPSFNDB(Word M, Word B, Word *t_, Word *Bt_, Word *F_)
{
       Word t,Bt,F;

Step1: /* Process. */
       if (PCDBUSE == 'n')
         {
         AFUPSFN(M,B,&t,&Bt,&F);
         goto Return;
         }
       if (DBSRCH(DBAFUPSFN,LIST2(M,B)) == 0)
         {
         AFUPSFN(M,B,&t,&Bt,&F);
         DBADD(DBAFUPSFN,LIST2(M,B),LIST3(t,Bt,F),&DBAFUPSFN);
         }
       else
         FIRST3(DBINFO,&t,&Bt,&F);
       goto Return;

Return: /* Prepare for return. */
       *t_ = t;
       *Bt_ = Bt;
       *F_ = F;
}
