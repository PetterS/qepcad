/*======================================================================
                      v <- CELLATTR(c,A)

Cell attribute

\Input
  \parm{c} is a cell.
  \parm{A} is an attribute ID.

\Output
  \parm{v} is the attribute value of the cell c.
           It is cell to NIL if such attribute does not exist.
======================================================================*/
#include "qepcad.h"

Word CELLATTR(Word c, Word A)
{
       Word v,i;
       /* hide v,i; */

Step1: /* Get the value of the attribute. */
       switch(A)
         {
         case CALEVEL:     v = LELTI(c,LEVEL);   break;
         case CADIMENSION: v = CELLDIM(c);      break;
         case CADEGREE:    v = CELLDEG(c);      break;
         case CALCINDEX:   v = FIRST(LASTCELL(LELTI(c,INDX)));   break;
         case CAPARITY:    v = FIRST(LASTCELL(LELTI(c,INDX))) % 2; break;
         default:
            i = CAINDEX0 - A;
            if (1 <= i && i <= LELTI(c,LEVEL))
              v = LELTI(LELTI(c,INDX),i);
            else
              v = NIL;
         }

Return: /* Prepare for return. */
       return(v);
}
