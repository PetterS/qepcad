/*======================================================================
                      RPFACTREAD(r,V; A,t)

Rational polynomial factor read.

Inputs
  r : a positive BETA-digit.
  V : a non-NIL list of r distinct variables.
  
Outputs
  A : a rational polynomial with variables in V.
  t : 1 if successful, 0 otherwise.
======================================================================*/
#include "saclib.h"

void RPFACTREAD(r,V, A_,t_)
       Word r,V, *A_,*t_;
{
       Word A,C,D,N,i,k,t,v;
       /* hide C,i,k,t; */

Step1: /* Setup and Classify. */
       t = 1;
       C = CREADB();
       if (LETTER(C)) { BKSP(); goto Step2; }
       if (DIGIT(C)) { BKSP(); goto Step3; }
       if (C == '(') goto Step4;
       SWRITE("Error RPFACTREAD: Unexpected character.\n"); goto Step5;

Step2: /* Variable. */
       v = VREAD(); k = VLSRCH(v,V);
       if (k == 0)
         { SWRITE("Error RPFACTREAD: Unknown variable.\n"); goto Step5; }
       A = RNRED(1,1);
       A = PFBRE(k-1,A);
       A = LIST2(1,A);
       A = PFBRE(r-k,A);
       goto Return;

Step3: /* Number. */
       N = IREAD();
       C = CREAD();
       if (C != '/')
         { BKSP(); D = 1; }
       else
         {
         C = CREAD();
         if (!DIGIT(C))
           { SWRITE("Error RPFACTREAD: Digit was expected.\n"); goto Step5; }
         BKSP();
         D = IREAD();
         }
       A = RNRED(N,D); A = PFBRE(r,A); goto Return;

Step4: /* Parenthesized expression. */
       RPEXPREAD(r,V,&A,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ')')
         { SWRITE("Error RPFACTREAD: ')' was expected.\n"); goto Step5; }
       goto Return;

Step5: /* Error exit. */
       DIELOC(); t = 0;

Return: /* Prepare for return. */
       *A_ = A;
       *t_ = t;
       return;
}
