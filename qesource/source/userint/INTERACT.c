/*======================================================================
                      t <- INTERACT()

Interact with the user?

\Ouput
  \parm{t} is 1 if the interaction with the user is requested,
           0 otherwise.
======================================================================*/
#include "qepcad.h"

Word QepcadCls::INTERACT()
{
       Word t;
       /* hide t; */

Step1: /* Interact? */
       if (PCSEARCHOK == 'y') { t = 1; PCSEARCHOK = 'n'; goto Return; }
       if (PCFINISH == 'y')   { t = 0; goto Return; }
       if (PCNSTEP == 0)      { t = 0; goto Return; }
       if (PCNSTEP > 1)       { PCNSTEP = PCNSTEP - 1; t = 0; goto Return; }
       t = 1; 

Return: /* Prepare for return. */
       return(t);
}
