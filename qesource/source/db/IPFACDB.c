/*======================================================================
                      IPFACDB(r,P; s,c,L)

IPFAC with Database.
======================================================================*/
#include "qepcad.h"

#include "db/CAPolicy.h"

void IPFACDB(Word r, Word P, Word *s_, Word *c_, Word *L_)
{
       Word L,c,s;
       /* hide s; */

       GVCAP->IPFAC(r,P,s_,c_,L_);
       return;
       
Step1: /* Process. */
       if (PCDBUSE == 'n')
       {
         IPFAC(r,P,&s,&c,&L);
         goto Return;
       }
       if (DBSRCH(DBIPFAC,LIST2(r,P)) == 0)
       {
         IPFAC(r,P,&s,&c,&L);
         DBADD(DBIPFAC,LIST2(r,P),LIST3(s,c,L),&DBIPFAC);
       }
       else
         FIRST3(DBINFO,&s,&c,&L);
       goto Return;
       
Return: /* Prepare for return. */
       *s_ = s;
       *c_ = c;
       *L_ = L;
       return;
}

