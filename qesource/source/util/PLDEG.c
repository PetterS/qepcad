/*======================================================================
                      D <- PLDEG(P)

Polynomial List Degree

\Input
  \parm{P} is a list of polynomials.
  
\Output
  \parm{D} is the list of the degrees of the polynomials in P.
======================================================================*/
#include "qepcad.h"

Word PLDEG(Word P)
{
       Word D, P1;

Step1: /* Do it. */
       D = NIL;
       while (P != NIL)
         {
         ADV(P,&P1,&P);
         D = COMP(P1 == 0 ? -1 : PDEG(P1),D); /* I modified this so deg(0) = -1 */
         }
       D = INV(D);

Return: /* Prepare for return. */
       return(D);
}
