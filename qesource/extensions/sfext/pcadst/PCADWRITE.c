/*======================================================================
 
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"
#include "stdio.h"

void PCADWRITE(Word Cs, Word Ps)
{
      Word C,l,i,L,k,I;

Step1: /* */
      I = PCADCINDEX(Cs);
      l = LENGTH(I);
      L = LELTI(Cs,SC_CDTV);

Step2: /* */
      SWRITE("\n");
      for(k = 0; k < l; k++)
	SWRITE("    ");
      OWRITE(I);

Step3: /* */
      SWRITE(":");
      SIGNLWR(PCADCSV(Cs,Ps));

Step4: /* */
      if (ISATOM(L)) {
	if (L == 0)
	  SWRITE(":F");
	else if (L == 1)
	  SWRITE(":T");
	else 
	  SWRITE(":?"); }
      else {
	SWRITE(":==>");
	while (L != NIL) {
	  PCADWRITE(FIRST(L),Ps);
	  L = RED(L); } }

Return: /* */
      if (I == NIL) SWRITE("\n");
      return;
}
