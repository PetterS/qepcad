/*======================================================================
                      B <- AFUSPSFB(M,A)

Algebraic number field univariate squarefree polynomial squarefree 
basis.

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  A : a list (A1,...,An), n >= 0, Ai is monic, squarefree, of positive
      degree.
Outputs
  B : a list of polynomials in Q(alpha)[x], a coarsest squarefree basis 
      for A.
======================================================================*/
#include "saclib.h"

Word AFUSPSFB(M,A)
  Word M,A;
{
  Word B;
  Word Ap,A1;


Step1:
  B = NIL;
  Ap = A;
  while (Ap != NIL)
    {
    ADV(Ap,&A1,&Ap);
    B = AFUPSFBA(M,A1,B);
    }
  goto Return;

Return:
  return(B);
}
