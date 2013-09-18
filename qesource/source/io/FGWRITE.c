/*======================================================================
                      FGWRITE(A,n)

Formatted Gamma Integer Write.

\Input
  \parm{A} is a $\gamma$--integer.
  \parm{n} is a $\gamma$--integer.

\Output
  $A$ is written right justified within $n$ spaces.
  If $A$ cannot be fit in $n$ spaces, it will be written left justified.
======================================================================*/
#include "qepcad.h"

void FGWRITE(Word A, Word n)
{
       Word Ap,D[32],N,Np,Q,i,t;
       /* hide Ap,N,Np,Q,i,t; */

Step1: /* Minus sign. */
        if (A < 0) { Ap = -A; t = -1; } else { Ap = A; t = 1; }

Step2: /* Convert to decimal. */
        N = 0;
        do
          { Q = Ap / 10; N = N + 1; D[N] = Ap - 10 * Q; Ap = Q; }
        while (!(Ap == 0));

Step3: /* Padd leading blanks. */
        if (t == -1) Np = N + 1; else Np = N;
        for (i = 1; i <= n - Np; i++) CWRITE(' ');

Step4: /* Write minus sign. */
        if (t == -1) CWRITE('-');

Step5: /* Write digits. */
        do { CWRITE(D[N] + '0'); N = N - 1; } while (!(N == 0));
        goto Return;

Return: /* Prepare for return. */
       return;
}
