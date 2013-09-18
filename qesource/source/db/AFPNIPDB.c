/*======================================================================
                      N <- AFPNIPDB(Mb,B)

AFPNIP with Database.
======================================================================*/
#include "qepcad.h"

Word AFPNIPDB(Word Mb, Word B)
{
       Word N;

Step1: /* Process. */
       if (PCDBUSE == 'n')
         {
         N = AFPNIP(Mb,B);
         goto Return;
         }
       if (DBSRCH(DBAFPNIP,LIST2(Mb,B)) == 0)
         {
         N = AFPNIP(Mb,B);
         DBADD(DBAFPNIP,LIST2(Mb,B),LIST1(N),&DBAFPNIP);
         }
       else
         N = FIRST(DBINFO);
       goto Return;

Return: /* Prepare for return. */
       return(N);
}
