/*======================================================================
                      M <- MKMUL(E,k)

Make a multiplicity list.

\Input
  \parm{E} is a multiplicity matrix.
  \parm{k} is a positive integer.

\Output
  \parm{M} is the mutiplicity list.
======================================================================*/
#include "qepcad.h"

Word MKMUL(Word E, Word k)
{
       Word M,E1,m,i;

Step1: /* Make it. */
       M = NIL;
       i = 0;
       while (E != NIL)
         {
         i = i + 1;
         ADV(E,&E1,&E);
         m = LELTI(E1,k);
         if (m != 0)
           M = COMP(LIST2(i,m),M);
         }
       M = INV(M);

Return: /* Prepare for return. */
       return(M);
}


