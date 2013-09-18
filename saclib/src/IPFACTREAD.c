/*======================================================================
                      IPFACTREAD(r,V; A,t)

Integral polynomial factor read.

Inputs
  r : a positive BETA-digit.
  V : a non-NIL list of r distinct variables.
  
Outputs
  A : in Z[X1,...,Xr], with variables in V.
  t : 1 if successful, 0 otherwise.
======================================================================*/
#include "saclib.h"

void IPFACTREAD(r,V, A_,t_)
       Word r,V, *A_,*t_;
{
       Word A,C,N,i,k,t,v;
       /* hide C,i,k,t; */

Step1: /* Setup and Classify. */
       t = 1;
       C = CREADB();
       if (LETTER(C)) { BKSP(); goto Step2; }
       if (DIGIT(C)) { BKSP(); goto Step3; }
       if (C == '(') goto Step4;
       SWRITE("Error IPFACTREAD: Unexpected character.\n"); goto Step5;

Step2: /* Variable. */
       v = VREAD(); k = VLSRCH(v,V);
       if (k == 0)
         { SWRITE("Error IPFACTREAD: Unknown variable.\n"); goto Step5; }
       A = PFBRE(k-1,1);
       A = LIST2(1,A);
       A = PFBRE(r-k,A);
       goto Return;

Step3: /* Number. */
       N = IREAD();
       A = PFBRE(r,N); goto Return;

Step4: /* Parenthesized expression. */
       IPEXPREAD(r,V,&A,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ')')
         { SWRITE("Error IPFACTREAD: ')' was expected.\n"); goto Step5; }
       goto Return;

Step5: /* Error exit. */
       DIELOC(); t = 0;

Return: /* Prepare for return. */
       *A_ = A;
       *t_ = t;
       return;
}
