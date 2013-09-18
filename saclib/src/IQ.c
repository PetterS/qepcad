/*======================================================================
                      C <- IQ(A,B)

Integer quotient.  

Inputs
  A,B : in Z. B /= 0.  


Outputs
  C   : the integral part of A/B.
======================================================================*/
#include "saclib.h"

Word IQ(A,B)
       Word A,B;
{
       Word C,R;
       /* hide algorithm */

Step1:
       IQR(A,B,&C,&R);
       goto Return;

Return: /* Prepare for return. */
       return(C);
}
