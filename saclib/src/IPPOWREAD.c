/*======================================================================
                      IPPOWREAD(r,V; A,t)

Integral polynomial power read.

Inputs
  r : a positive BETA-digit.
  V : a non-NIL list of r distinct variables.
  
Outputs
  A : in Z[X1,...,Xr], with variables in V.
  t : 1 if successful, 0 otherwise.
======================================================================*/
#include "saclib.h"

void IPPOWREAD(r,V, A_,t_)
       Word r,V, *A_,*t_;
{
       Word A,A1,C,e,i,t;
       /* hide C,i,t; */

Step1: /* Setup. */
       t = 1; A = PFBRE(r,1);

Step2: /* Read in a factor. */
       IPFACTREAD(r,V,&A1,&t); if (t == 0) goto Return;

Step3: /* Read in an optional exponent. */
       C = CREADB();
       if (C != '^')
         { BKSP(); e = 1; }
       else
         {
         C = CREADB();
         if (!DIGIT(C))
           { SWRITE("Error IPPOWREAD: Digit was expected.\n"); goto Step5; }
         BKSP(); e = IREAD();
         if (e >= BETA)
           { SWRITE("Error IPPOWREAD: Exponent is too big.\n"); goto Step5; }
         }

Step4: /* Carry out the exponentiation. */
       for (i = 1; i <= e; i++) A = IPPROD(r,A,A1);
       goto Return;

Step5: /* Error exit. */
       DIELOC(); t = 0; 

Return: /* Prepare for return. */
       *A_ = A;
       *t_ = t;
       return;
}
