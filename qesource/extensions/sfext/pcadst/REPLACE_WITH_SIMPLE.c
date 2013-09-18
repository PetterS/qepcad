/*======================================================================
                         REPLACE_WITH_SIMPLE(D,P,flag)

Replaces QEPCAD's CAD with a simplified CAD.  If the lowest order bit
of flag is set, then the simplification is based solely on truth
values of cells of full dimension.  Otherwise the usual method is used.
If the second lowest order bit of flag is set, then the CAD will be
replaced by a simplified CAD only if the simplified CAD is
projection definable.

======================================================================*/
#include "qepcad.h"

void QepcadCls::REPLACE_WITH_SIMPLE(Word D, Word P, Word flag)
{
      Word Ps,Cs,Db;

Step1: /* Check for the trivial cases. */
      switch( DOPFSUFF(P,LIST1(D)) ) {
      case (TRUE) : SWRITE("\n\nInput is identically TRUE.\n\n");
                    goto Return;
      case (FALSE): SWRITE("\n\nInput is identically FALSE.\n\n");
                    goto Return; 
      default     : break; }

Step2: /* Construct the simple CAD. */
      if (flag & 1)
	CCADCONmod(GVNFV,P,D,&Ps,&Cs);
      else
	CCADCON(GVNFV,P,D,&Ps,&Cs);

Step3: /* Replace if appropriate. */
      Db = CADFPCAD(Cs,Ps,NIL,NIL,P);
      if (!(flag & 2) || (DOPFSUFF(Ps,LIST1(Db)) != NIL)) { 
	GVPC = Db;
	P = REDI(P,LENGTH(Ps));
	P = CCONC(Ps,P);
	GVPF = P; } 
      else {
	SWRITE("CAD is not projection-definable -- no replacement.\n"); }

Return: /* Prepare to return. */
      return;
}
