/*======================================================================
                      RPEXPREAD(r,V; A,t)

Rational polynomial expression read.

Inputs
  r : a positive BETA-digit.
  V : a non-NIL list of r distinct variables.

Outputs
  A : in Q[X1,...,Xr], with variables in V.
  t : 1 if successful, 0 otherwise.
======================================================================*/
#include "saclib.h"

void RPEXPREAD(r,V, A_,t_)
       Word r,V, *A_,*t_;
{
       Word A,A1,C,t;
       /* hide C,t; */

Step1: /* Setup. */
       t = 1; A = 0;

Step2: /* Read in terms. */
       do
        {
        RPTERMREAD(r,V,&A1,&t); if (t == 0) goto Return;
        A = RPSUM(r,A,A1);
        C = CREADB(); BKSP();
        }
       while (!(C != '+' && C != '-'));

Return: /* Prepare for return. */
       *A_ = A;
       *t_ = t;
       return;
}
