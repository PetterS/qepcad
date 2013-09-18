/*======================================================================
                      FINDRATCOORD(S;t,R,P)

Find rational coordinate

Inputs:
  S : a list (S_1,...,S_r), S_i a list of primitive irreducible 
      i-variate saclib pols

Outputs:
  t : a BDigit
  R : a rational number
  P : SACLIB polynomial
  If some element of some S_i is a x_i + b, a,b \in Z, then 
  t = i, R = -b/a and P = a x_i + b (as an element of Z[x_1,...,x_t]).
  Otherwise t = 0.
======================================================================*/
#include "qepcad.h"

void FINDRATCOORD(Word S, Word* t_, Word *R_, Word *P_)
{
  Word r, i, L, R;
  r = LENGTH(S);
  for(i = 1; i <= r; i++)
  {
    for(L = LELTI(S,i); L != NIL; L = RED(L))
    {
      R = IPRSOL(i,FIRST(L));
      if (R != NIL)
      {
	*t_ = i;
	*R_ = R;
	*P_ = FIRST(L);
	return;
      }
    }
  }
  
  *t_ = 0;
  return;
}

