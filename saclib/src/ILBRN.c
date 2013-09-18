/*===========================================================================
                               L <- ILBRN(I)

Integer to logarithmic binary rational number.

Inputs
  I  : in Z.

Outputs
  L  : the logarithmic binary rational representation of L.
===========================================================================*/
#include "saclib.h"

Word ILBRN(I)
       Word I;
{
  Word L,n,Ip;

  if (I == 0)
    L = 0;
  else {
    n = IORD2(I);
    Ip = IDP2(I,n);
    L = LIST2(Ip,-n);}

  return L;
}
