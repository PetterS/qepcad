/*======================================================================
                      AFUPGCDB(M,A,B; C,Ab,Bb)

AFUPGC with Database.
======================================================================*/
#include "qepcad.h"

void AFUPGCDB(Word M, Word A, Word B, Word *C_, Word *Ab_, Word *Bb_)
{
       Word C,Ab,Bb;

Step1: /* Process. */
       if (PCDBUSE == 'n')
         {
         AFUPGC(M,A,B, &C,&Ab,&Bb);
         goto Return;
         }
       if (DBSRCH(DBAFUPGC,LIST3(M,A,B)) == 0)
         {
         AFUPGC(M,A,B, &C,&Ab,&Bb);
         DBADD(DBAFUPGC,LIST3(M,A,B),LIST3(C,Ab,Bb),&DBAFUPGC);
         }
       else
         FIRST3(DBINFO,&C,&Ab,&Bb);
       goto Return;

Return: /* Prepare for return. */
       *C_ = C;
       *Ab_ = Ab;
       *Bb_ = Bb;
       return;
}
