/*======================================================================
                      Tp <- NEGRLOP(T)

Negate Relational Operator.

\Input
  \parm{T} is a relational operator.

\Output
  \parm{T'} is a realational opeator 
            equivalent to  $-$\v{T}.
======================================================================*/
#include "qepcad.h"

Word NEGRLOP(Word T)
{
       Word Tp;
       /* hide Tp; */

Step1: /* Negate. */
       switch (T)
         {
         case EQOP: Tp = EQOP; break;
         case NEOP: Tp = NEOP; break;
         case LTOP: Tp = GTOP; break;
         case LEOP: Tp = GEOP; break;
         case GTOP: Tp = LTOP; break;
         case GEOP: Tp = LEOP;
         break; }
       goto Return;

Return: /* Prepare for return. */
       return(Tp);
}
