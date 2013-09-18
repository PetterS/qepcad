/*======================================================================
                    t <- SCFILTER(c,d)

SC Filter

Inputs
c,d : ESCAD cells of the same level.

Outputs
t   : 1 if the children of c that are marked true can be distinguished
      from the children of d that are marked false and the children of
      c that are marked false can be distinguished from the children
      of d that are marked true.  0 otherwise.

======================================================================*/
#include "extlang.h"

Word SCFILTER(Word c, Word d)
{
  Word cLt,cLf,dLt,dLf,t;

Step1: /* Get true-marked and false-marked cell lists. */
  LTFOCWTVMARK(c,&cLt,&cLf);
  LTFOCWTVMARK(d,&dLt,&dLf);
  
Step2: /* Look for a conflict. */
  if (SCCONFLICTQ(cLt,dLf) || SCCONFLICTQ(cLf,dLt))
    t = 0;
  else
    t = 1;

Return: /* Prepare to return. */
  return t;
}
