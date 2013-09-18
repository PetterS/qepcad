/*======================================================================
                      s <- AMSIGN(M,I,b)

Algebraic module sign.

Inputs
  M : the minimal integral polynomial of a real algebraic
      number alpha.
  I : an acceptable isolating interval for alpha.
  b : an element of Z[alpha].

Outputs
  s  : sign(b).
======================================================================*/
#include "saclib.h"

Word AMSIGN(M,I,b)

       Word M,I,b;
{
       Word s,Is;

Step1:
      AMSIGNIR(M,I,b,&s,&Is);

Return:
       return(s);
}
