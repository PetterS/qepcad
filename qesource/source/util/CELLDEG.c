/*======================================================================
                      d <- CELLDEG(c)

Cell degree.  

\Input
  \parm{c} is a cell.
  
\Output
  \parm{d} is the presumed degree of the cell.
======================================================================*/
#include "qepcad.h"

Word CELLDEG(Word c)
{
       Word I,M,Mp,Ip,bp,b,d,m,mp,s;
       /* hide d,m,mp; */

Step1: /* Root cell. */
       if (LELTI(c,LEVEL) == 0)
         {
         d = 1;
         goto Return;
         } 

Step2: /* Non-root cell. */
       s = LELTI(c,SAMPLE);
       if (ISPRIMIT(s))
         {
         FIRST3(s,&M,&I,&b);
         m = PDEG(M);
         mp = 1;
         }
       else
         {
         FIRST5(s,&M,&I,&Mp,&Ip,&bp);
         m = PDEG(M);
         mp = PDEG(Mp);
         }
       d = mp * m;

Return: /* Prepare for return. */
       return(d);
}
