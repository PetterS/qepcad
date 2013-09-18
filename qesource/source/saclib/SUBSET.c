/*======================================================================
                      t <- SUBSET(A,B)

Subset

Inputs
  A : List of objects
  B : List of objects

Outputs
  t  : an integer.
       t has the value 1 if A is a subset of B, 0 otherwise
======================================================================*/
#include "qepcad.h"

BDigit SUBSET(Word A, Word B)
{
  Word Ap;
  for(Ap = A ;Ap != NIL && MEMBER(FIRST(Ap),B); Ap = RED(Ap));
  return Ap == NIL;
}
