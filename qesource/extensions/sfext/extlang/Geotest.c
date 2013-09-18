/*

Test program for constructing a solution formula "geometrically".

*/
#include "extlang.h"

Word GEOTEST(Word P, Word C)
{
  Word Cs,ECs,F;

  Cs = SCADDSCON(C,NIL,GVNFV);
  /*  ECs = SCAD2ESCAD(P,P,Cs,NIL); */
  ECs = PCAD2ESPCAD(P,P,Cs,NIL);

  SWRITE("\n\n");
  /*  FMAIWRITE(SC_test(ECs,P,GVNFV)); */
  SWRITE("\n\n");
  F = SC_test(ECs,P,GVNFV);
  FMAWRITE(F,P,GVVL);
  SWRITE("\n\n");
  FMAWRITE(FMASMOOTH(F),P,GVVL);
  SWRITE("\n\n");

  return 0;
}
