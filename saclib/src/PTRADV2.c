/*======================================================================
                      PTRADV2(L; a,b,Lp)

Advance 2. (assuming first two elts of L are pointers)

Inputs
  L   : a list of length 2 or more. (first two elts are pointers)

Outputs
  a   : the first element of L.
  b   : the second element of L. 
  Lp  : the second reductum of L;(assuming a & b are pointers)
======================================================================*/
#include "saclib.h"

void PTRADV2(L,a_,b_,Lp_)
     Word L, **a_, **b_, *Lp_;
{
  Word Lp, *a, *b;
  PTRADV(Lp,&a,&Lp);
  PTRADV(Lp,&b,&Lp);
  *Lp_ = Lp;
  *a_ = a;
  *b_ = b;  
}
