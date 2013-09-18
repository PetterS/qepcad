/*======================================================================
                      Q <- SIMPLIFYSYSLIST(r,L,A)

Simplify List of systems

Inputs
  r : a BDigit
  L : a list of r-variate systems (i.e. a list of lists of r-variate 
      polynomials)
  A : a QEPCAD formula representing assumptions.  Can be normalized or
      unnormalized.

Outputs
  Q : 1 if it is determined that there are no systems in the list that
      are satisfiable given the assuptions.  Otherwise a list
      is systems that is equivalent (but hopefully simpler) given the
      assuptions.
======================================================================*/
#include "qepcad.h"

Word SIMPLIFYSYSLIST(BDigit r, Word L, Word A)
{
  Word Q, Lp, Qp;

Step1: /* Simplify each element individually */
  Q = NIL;
  for(Lp = L; Lp != NIL; Lp = RED(Lp))
  {
    Qp = SIMPLIFYSYS(r,FIRST(Lp),NIL,A);
    if (Qp != 1)
      Q = CCONC(Qp,Q);
  }

Step2: /* Check for inconsistency */
  if (Q == NIL)
    Q = 1;

Step3: /* Remove Sys A if Sys A contained in Sys B */
  if (Q != 1)
    Q = SOSRSUPS(Q);

Return: /* Prepare to return. */
  return Q;
}
