/*======================================================================
                      QFRDR(; q,t)

Quantifier Read, robust.

\Ouput
  \parm{q} is a quantifier, read in from the input stream.
  \parm{t} is 1 if successful, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void QFRDR(Word *q_, Word *t_)
{
       Word C,q,t,k;
       /* hide C,q,t; */

Step1: /* Read in. */
       t = 1;
       C = CREADB();
       if (C == 'A')
         q = UNIVER;
       else if (C == 'E')
         q = EXIST;
       else if (C == 'C')
	 q = CONTQ;
       else if (C == 'F')
	 q = FULLDE;
       else if (C == 'G')
	 q = FULLDA;
       else if (C == 'X')
       {
	 GREADR(&k,&t);
	 if (!t || k <= 0)
	   { SWRITE("Error QFRDR: Positive integer expected.\n"); goto Step2; }
	 q = LIST2(EXISTk,k);
       }
       else
         { SWRITE("Error QFRDR: Quantifier was expected.\n"); goto Step2; }
       goto Return;

Step2: /* Error exit. */
       DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *q_ = q;
       *t_ = t;
       return;
}
