/*======================================================================
                      W <- GETWORD()

Get a word.

\Output
  \parm{W} is a list of alphanumeric characters  read from the input stream.
           The leading blanks are skipped. (- and _ are considered to be
           alphbetics)
======================================================================*/
#include "qepcad.h"

Word GETWORD()
{
       Word C,W;
       /* hide C; */

Step1: /* Get a word. */
       C = CREADB();
       W = LIST1(C);
       C = CREAD();
       while (('A' <= C && C <= 'Z') || 
              ('a' <= C && C <= 'z') || 
              ('0' <= C && C <= '9') || 
              C == '-' ||
              C == '_' )
         {
         W = COMP(C,W);
         C = CREAD();
         }
       BKSP(); W = INV(W); goto Return;

Return: /* Prepare for return. */
       return(W);
}
