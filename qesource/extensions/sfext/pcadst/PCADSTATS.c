/*======================================================================
                      PCADSTATS(C,P,n)

Pruned CAD statistics.

Inputs
  C  : The partial CAD.
  P  : The pruned projection factor set defining C.
  n  : The level of C

Side Effects
  Statistics are written to standard out.

======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

void PCADSTATS(Word C, Word P, Word n)
{
      Word Ps,l,Lt,Lf;

Step1: /* Pruned projection factor set info. */
      Ps = P;
      for(l = 1; Ps != NIL; Ps = RED(Ps)) {
	SWRITE("Level "); IWRITE(l++); SWRITE(" : ");
	IWRITE(LENGTH(FIRST(Ps))); SWRITE(" projection factors.\n"); }
      SWRITE("\n");

Step2: /* Pruned CAD info. */
      for(l = 1; l <= n; l++) {
	SWRITE("Level "); IWRITE(l); SWRITE(" : ");
	IWRITE(LENGTH(PCADCL(C,l))); SWRITE(" cells.\n"); }
      SWRITE("\n");
      
      LTFOCWTV(C,&Lt,&Lf);
      SWRITE("There are "); IWRITE(LENGTH(Lt) + LENGTH(Lf));
      SWRITE(" cells with determined truth value.\n\n");

Return: /* */
      return;
}
