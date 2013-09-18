/*======================================================================
                      j <- NORMAL(s)

NORMAL of Loos.

\Input
  \parm{s}  is an extended sample point of a cell c.

\Output
  \parm{sh} is a normalized sample point of the cell c.
======================================================================*/
#include "qepcad.h"

Word NORMAL(Word s)
{
       Word I,J,Js,M,N,g,gs,j,sh,b;
       Word g1;
       /* hide j; */

Step1: /* Setup. */
       FIRST5(s,&g,&J,&M,&I,&b);

Step2: /* Normalize. */
       N = AFPNIPDB(M,g);
       g = AFPICR(1,g);
       IPSRP(2,g,&g1,&g);
       AMUPMPR(M,I,g,J,N,&Js,&j);
       gs = LELTI(N,j); Js = IPSIFI(gs,Js);
       sh = LIST5(gs,Js,M,I,b);

Return: /* Prepare for return. */
       return(sh);
}
