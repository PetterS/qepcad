/*======================================================================
                      FINDEQCONSTS()

Find Equational Constraints

Input
 F : a normalized formula

Output 
 C : a normalized formula of the following form:
     (p1,1 = 0 \/ ...\/ p1,n1 = 0) /\ ... /\ (pm,1 = 0 \/ ...\/ pm,nm = 0)
     which expresses the constraints that must hold.

======================================================================*/
#include "qepcad.h"

Word FINDEQCONSTS(Word F)
{
  /* Atomic formula */
  if (ISATOMF(F))
  {
    if (FIRST(F) == EQOP) 
      return LIST2(ANDOP,F);
    else
      return LIST1(ANDOP);
  }

  if (FIRST(F) == ANDOP)
  {
    
  }
}

