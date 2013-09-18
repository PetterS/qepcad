/*======================================================================
                      t <- DIGIT(C)

Digit.  

Inputs
  C : a character.  

Outputs
  t : t = 1 if C is a digit, 0 otherwise.
======================================================================*/
#include "saclib.h"
#include <ctype.h>

Word DIGIT(C)
       Word C;
{
       Word t;
       /* hide algorithm */

Step1: /* Decide. */
       if (isdigit(C))
         t = 1;
       else
         t = 0;

Return: /* Prepare for return. */
       return(t);
}
