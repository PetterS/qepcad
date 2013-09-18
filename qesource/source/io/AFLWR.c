/*======================================================================
                      AFLWR(M,I,N,a,A,d)

Algebraic number field elements list write.

\Input
  \parm{M} is a minimal polynomial for alpha.
  \parm{I} is the isolating interval for alpha.
  \parm{N} is the base name for the coordinates.
  \parm{a} is the variable name for the algebraic number alpha.
  \parm{A} is the list of elements of Q(alpha).
  \parm{d} number of digits in decimal write
======================================================================*/
#include "qepcad.h"

void AFLWR(Word M, Word I, Word N, Word a, Word A, Word d)
{
       Word A1,Ap,i,l,L,j;
       /* hide i; */

Step1: /* Write. */
       Ap = A;
       i = 0;
       l = LENGTH(N);
       L = NIL;
       for (j=1; j<=l; j++)
          L = COMP(' ',L);
       while (Ap != NIL)
         {
         ADV(Ap,&A1,&Ap);
         i = i + 1;
         CLOUT(N); GWRITE(i); SWRITE(" = "); 
         AFWR(A1,a); SWRITE("\n");
         CLOUT(L); SWRITE("  = ");
         AFDWRITE(M,I,A1,d); SWRITE("\n");
         }

Return: /* Prepare for return. */
       return;
}
