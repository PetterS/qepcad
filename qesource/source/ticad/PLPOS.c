/*======================================================================
                         p <- PLPOS(P,i)

Polynomial List Position.
     
\Input
  \parm{P} is a list of polynomials.
  \parm{i} is a positive integer.
 
Output:
  \parm{p} is the position of the polynomial with index i.
           0 if not found.
======================================================================*/
#include "qepcad.h"

Word PLPOS(Word P, Word i)
{
       Word p,P1;

Step1: /* Search. */
       p = 0;
       while (P != NIL)
         {
         ADV(P,&P1,&P);
         p = p + 1;
         if (THIRD(LELTI(P1,PO_LABEL)) == i)
           goto Return;
         }
       p = 0;

Return: /* Prepare for return. */
       return(p);
}




