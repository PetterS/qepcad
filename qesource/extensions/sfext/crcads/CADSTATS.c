/*======================================================================
                      CADSTATS(C,P)

CAD statistics.

Inputs
  C  : The partial CAD.
  P  : The projection factor set defining C.

Side Effects
  Statistics are written to standard out.

======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

void QepcadCls::CADSTATS(Word C, Word P)
{
      Word Ps,l,t,f,L,N;

Step1: /* Pruned projection factor set info. */
      Ps = P;
      for(l = 1; Ps != NIL; Ps = RED(Ps)) {
        SWRITE("Level "); IWRITE(l++); SWRITE(" : ");
        IWRITE(LENGTH(FIRST(Ps))); SWRITE(" projection factors.\n"); }
      SWRITE("\n");

Step2: /* CAD info. */
      t = 0; f = 0;

Step3: /* Loop over each level and get cells for that level. */
      for(l = 1; l <= GVNFV; l++) {
        SWRITE("Level "); IWRITE(l); SWRITE(" : ");
	L = CADCL(C,l);
	N = LENGTH(L);

Step4: /* Collect the true/false stats. */
	while (L != NIL) {
	  switch (LELTI(FIRST(L),TRUTH)) {
	  case (TRUE) : t++; break;
	  case (FALSE): f++; break; }
	  L = RED(L); }
	
        IWRITE(N); SWRITE(" cells.\n"); }
      SWRITE("\n");

Step5: /* Write the true cell stats. */
      SWRITE("There are "); IWRITE(t + f);
      SWRITE(" cells with determined truth value.\n\n");

Return: /* Prepare to return. */
      return;
}
