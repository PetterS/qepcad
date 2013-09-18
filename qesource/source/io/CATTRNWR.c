/*======================================================================
                      CATTRNWR(A)

Cell attribute name write.

\Input
  \parm{A} is a cell attribute ID.
======================================================================*/
#include "qepcad.h"

void CATTRNWR(Word A)
{

Step1: /* Write it. */
       switch (A)
         {
         case CALEVEL:     SWRITE("level");     break;
         case CADIMENSION: SWRITE("dimension"); break;
         case CADEGREE:    SWRITE("degree");    break;
         case CALCINDEX:   SWRITE("lcindex");   break;
         case CAPARITY:    SWRITE("parity");    break;
         default:
            SWRITE("index(");
            AWRITE(CAINDEX0 - A);
            SWRITE(")");
            break;
         }

Return: /* Prepare for return. */
       return;
}
