/*======================================================================
                      t <- LETTER(C)

Letter.  

Inputs
  C : a character.  

Outputs
  t : If C is a letter then t=1 and otherwise t=0.
======================================================================*/
#include "saclib.h"

Word LETTER(C)
       Word C;
{
       Word t;
       /* hide algorithm */

Step1: /* Decide. */
       if ((C >= 'A' && C <= 'Z') ||  (C >= 'a' && C <= 'z'))
         t = 1;
       else
         t = 0;

Return: /* Prepare for return. */
       return(t);
}
