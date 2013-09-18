/*======================================================================
                 LISTOFCWTV(C;Lt,Lf)

List (true/false) of cells with truth values.

Inputs
  C : A CAD cell.

Outputs
  Lt : A list of all true cells.
  Lf : A list of all false cells.
======================================================================*/
#include "qepcad.h"

void LISTOFCWTV(Word C, Word *Lt_, Word *Lf_)
{
      Word L,Cp,Lt,Lf,t,Ltp,Lfp;

Step1: /* If C is undetermined recurse on the children. */
      t = LELTI(C,TRUTH); 
      switch (t) {
      case (TRUE) :
        Lt = LIST1(C); Lf = NIL; break;
      case (FALSE) :
        Lf = LIST1(C); Lt = NIL; break;
      default :
        Lf = NIL; Lt = NIL;
        for(Cp = LELTI(C,CHILD); Cp != NIL; Cp = RED(Cp)) {
          LISTOFCWTV(FIRST(Cp),&Ltp,&Lfp);
          Lt = CONC(Ltp,Lt);
          Lf = CONC(Lfp,Lf); }
        break; }

Return:
      *Lt_ = Lt;
      *Lf_ = Lf;
      return;
}
