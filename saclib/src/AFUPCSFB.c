/*======================================================================
                      B <- AFUPCSFB(M,A)

Algebraic number field univariate polynomial coarsest squarefree basis.

Inputs
  M : in Z[x], the integral minimal polynomial of an algebraic number alpha.  
  A : a list (A1,...,An), n >= 0, Ai in Q(alpha)[x], is a monic polynomial 
      of positive degree.
Outputs
  B : a list of polynomials in Q(alpha)[x], a coarsest squarefree basis 
      for A.
======================================================================*/
#include "saclib.h"

Word AFUPCSFB(M,A)
  Word M,A;
{
  Word B;
  Word Ap,A1,As,L,L1,Ap1;


Step1: /* Compute. */
  As = NIL;
  Ap = A;
  while (Ap != NIL)
    {
    ADV(Ap,&A1,&Ap);
    L = AFUPSF(M,A1);
    do
      {
      ADV(L,&L1,&L);
      Ap1 = SECOND(L1);
      As = COMP(Ap1,As);
      }
    while (L != NIL);
    }
  B = AFUSPSFB(M,As);
  goto Return;

Return: /* Prepare for return. */
  return(B);
}
