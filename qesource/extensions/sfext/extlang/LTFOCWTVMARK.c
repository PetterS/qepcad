/*======================================================================
                 LTFOCWTVMARK(C;Lt,Lf)

List (true/false) of cells 1 level above C with truth values from 
mark (SC_TMPM).

Inputs
  C : A pruned partial cad.

Outputs
  Lt : A list of cells marked TRUE.
  Lf : A list of cells marked FALSE.
======================================================================*/
#include "extlang.h"

void LTFOCWTVMARK(Word C, Word *Lt_, Word *Lf_)
{
      Word Lt,Lf,S,c;

Step1: /* */
      Lt = NIL;
      Lf = NIL;
      S = LELTI(C,SC_CDTV);
      if (!ISLIST(S))
	goto Return;
      while(S != NIL) {
	ADV(S,&c,&S);
	if (LELTI(c,SC_TMPM) == TRUE)
	  Lt = COMP(c,Lt);
	else
	  Lf = COMP(c,Lf); }

Return: /* Prepare to return. */
      *Lt_ = Lt;
      *Lf_ = Lf;
      return;
}
