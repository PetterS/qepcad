/*======================================================================
                      FREADR(V,f; Fs,t)

Formula read, robust.

\Input 
  \parm{V} is a non-null list of distinct variables.
  \parm{f} is a $\beta$--integer with $0 \leq f \leq r$,
              where $r$ is the length of the list $V$. 
              It is the number of free variables in the formula
              to be read in. 
  
\Output
  \parm{F*} is a formula with $r-f$ quantifiers whose variables 
               all occur in $V$, read from the input stream. 
  \parm{t}  is 1 if successful, 0 othewise.
======================================================================*/
#include "qepcad.h"

void FREADR(Word V, Word f, Word *Fs_, Word *t_)
{
       Word C,F,Fs,Q,i,q,r,t,v;
       /* hide C,i,q,r,t; */

Step1: /* Read quantifier list. */
       t = 1; Q = NIL; r = LENGTH(V);
       for (i = f + 1; i <= r; i++)
         {
         C = CREADB();
         if (C != '(')
           { SWRITE("Error FREADR: '(' was expected.\n"); goto Step3; }
         QFRDR(&q,&t); if (t == 0) goto Return;
         Q = COMP(q,Q);
         VREADR(&v,&t); if (t == 0) goto Return;
         if (!EQUAL(v,LELTI(V,i)))
           { SWRITE("Error FREADR: Variable '"); VWRITE(LELTI(V,i));
            SWRITE("' was expected.\n"); goto Step3; }
         C = CREADB();
         if (C != ')')
           { SWRITE("Error FREADR: '(' was expected.\n"); goto Step3; }
         }
       Q = INV(Q);

Step2: /* Read unquantified matrix. */
       QFFRDR(V,&F,&t); if (t == 0) goto Return;
       if (CREADB() != '.')
         { SWRITE("Error FREADR: '.' was expected.\n"); goto Step3; }
       Fs = LIST4(r,f,Q,F); goto Return;

Step3: /* Error exit. */
       DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *Fs_ = Fs;
       *t_ = t;
       return;
}
