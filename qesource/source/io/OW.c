/*===========================================================================
                         OW(S,A)

Object write with newline.
===========================================================================*/
#include "qepcad.h"

void OW(char *S, Word A)
{
   SWRITE(S);
   SWRITE(" = ");
   OWRITE(A);
   SWRITE("\n\n");
}
