/*======================================================================
                 LTFOCALWTV(C;Lt,Lf)

List (true/false) of cells with truth values.

Inputs
  C : A pruned partial cad.
  n : a level (i.e. non-negative BETA-digit.

Outputs
  Lt : A list of all true cells.
  Lf : A list of all false cells.
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

void LTFOCALWTV(Word C, Word n, Word *Lt_, Word *Lf_)
{
      Word L,Cp,Lt,Lf,t,Ltp,Lfp;

Step1: /* If C is undetermined recurse on the children. */
      t = LELTI(C,SC_CDTV); 
      switch (t) {
      case (TRUE) :
	Lt = LIST1(C); Lf = NIL; break;
      case (FALSE) :
	Lf = LIST1(C); Lt = NIL; break;
      default :
	Lf = NIL; Lt = NIL;
	if (!ISLIST(t) || n == 0) break;
	for(Cp = t; Cp != NIL; Cp = RED(Cp)) {
	  LTFOCALWTV(FIRST(Cp),n-1,&Ltp,&Lfp);
	  Lt = CONC(Ltp,Lt);
	  Lf = CONC(Lfp,Lf); }
	break; }

Return:
      *Lt_ = Lt;
      *Lf_ = Lf;
      return;
}
