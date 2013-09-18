/*======================================================================
                      XREADR(; L,t)

Index Read, robust.  

\Output
 \parm{L} is an index which is read in from the input stream.
 \parm{t} is 1 if successful, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void XREADR(Word *L_, Word *t_)
{
       Word C,L,L1,t;
       /* hide C,L1,t; */

Step1: /* Read index elements. */
        L = NIL;
        C = CREADB();
        if (C != '(') { SWRITE("Error XREADR: '(' was expected.\n"); goto Step2; }
        do
          {
          C = CREADB();
          if (C == ')') { t = 1; L = INV(L); goto Return; }
          if (C > '9' || C < '1')
            { SWRITE("Error XREADR: A positive digit was expected.\n"); goto Step2; }
          BKSP(); L1 = AREAD();
          L = COMP(L1,L);
          C = CREADB();
          if (C == ')') BKSP();
          else if (C != ',')
            { SWRITE("Error XREADR: ')' or ',' was expected.\n"); goto Step2; }
          } while (1);

Step2: /* Error exit. */
        DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *L_ = L;
       *t_ = t;
       return;
}
