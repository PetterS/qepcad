/*======================================================================
                      d <- CELLDIM(c)

Cell dimension.  

\Input
  \parm{c} is a cell.
  
\Output
  \parm{d} is the dimension of the cell.
======================================================================*/
#include "qepcad.h"

Word CELLDIM(Word c)
{
       Word I,Ip,d,i,k,r;
       /* hide d,i,r; */

Step1: /* Compute. */
       I = LELTI(c,INDX);
       d = 0; r = LENGTH(I); Ip = I;
       for (i = 1; i <= r; i++) 
         {
         ADV(Ip,&k,&Ip); 
         d = d + ODD(k); 
         }

Return: /* Prepare for return. */
       return(d);
}
