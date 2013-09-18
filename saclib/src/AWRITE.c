/*======================================================================
                      AWRITE(A)

Atom write.

Inputs
  A : atom.

Outputs
  none

Side effects
  The atom A is written in the output stream.
======================================================================*/
#include "saclib.h"

void AWRITE(A)
       Word A;
{
       Word Ap,D[21],N,Q;
       /* hide algorithm */

Step1: /* Write minus sign. */
       if (A < 0)
         {
         Ap = -A;
         CWRITE('-');
         }
       else
         Ap = A;

Step2: /* Convert to decimal. */
       N = 0;
       do
         {
         Q = Ap / 10;
         N = N + 1;
         D[N] = Ap - 10 * Q;
         Ap = Q;
         }
       while (!(Ap == 0));

Step3: /* Write digits. */
       do
         {
         CWRITE(D[N] + '0');
         N = N - 1;
         }
       while (!(N == 0));
       goto Return;

Return: /* Prepare for return. */
       return;
}
