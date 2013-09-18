/*======================================================================
                      INFOSACLIB(s)

Write out usage information for SACLIB.

Inputs
  s : a character string; the name of the executable program.

Side effects
  The standard command line usage is written to the output stream.
======================================================================*/
#include "saclib.h"

void INFOSACLIB(s)
       const char *s;
{
Step1: /* Write out the usage. */
       SWRITE("Usage:\n  ");
       SWRITE(s); SWRITE(" <SACLIB options>\n");
       SWRITE("\nSACLIB Options:\n");
       SWRITE("  +h     : print this usage information.");
       SWRITE("\n  +N<n>  : NU      <- <n>.  default = "); GWRITE(NU);
       SWRITE("\n  +Np<n> : NUp     <- <n>.  default = "); GWRITE(NUp);
       SWRITE("\n  +G<n>  : GCM     <- <n>.  default = "); GWRITE(GCM);
       SWRITE("\n  +R<n>  : RHO     <- <n>.  default = "); GWRITE(RHO);
       SWRITE("\n  +S<n>  : NSPRIME <- <n>.  default = "); GWRITE(NSPRIME);
       SWRITE("\n  +M<n>  : NMPRIME <- <n>.  default = "); GWRITE(NMPRIME);
       SWRITE("\n  +L<n>  : NLPRIME <- <n>.  default = "); GWRITE(NLPRIME);
       SWRITE("\n  +T<n>  : NPTR1   <- <n>.  default = "); GWRITE(NPTR1);
       SWRITE("\n");
}
