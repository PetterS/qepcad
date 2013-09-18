/*======================================================================
FMAOPCOMBINE
======================================================================*/
#include "extlang.h"

Word FMAOPCOMBINE(Word F)
{
      Word L,M,Fp,f,a,b,Lp,Mp,Lb;

  switch(FIRST(F)) {

  case OROP:
    /* Set L to a list of all top level atomic formulas. */
    L = NIL; M = NIL;
    for(Fp = RED(F); Fp != NIL; Fp = RED(Fp)) {
      f = FIRST(Fp);
      if (ISLIST(FIRST(f)))
	L = COMP(f,L);
      else
	M = COMP(f,M); }
    
    /*  Create Lp from L */
    Lp = NIL;
    while(L != NIL) {
      a = FIRST(L);
      if (FMAQEXTAF(a)) { Lp = COMP(a,Lp); L = RED(L); continue; }
      Lb = RED(L);
      for(L = NIL; Lb != NIL; Lb = RED(Lb)) {
	b = FIRST(Lb);
	if (FMAQEXTAF(b) || ! EQUAL(FIRST(b),FIRST(a)))
	  L = COMP(b,L);
	else 
	  a = LIST2(FIRST(a),SECOND(a) | SECOND(b)); }
      if (SECOND(a) > 6)
	Lp = COMP(LIST1(TRUE),Lp);
      else
	Lp = COMP(a,Lp); }

    /* Create Mp from M. */
    for(Mp = NIL; M != NIL; M = RED(M))
      Mp = COMP(FMAOPCOMBINE(FIRST(M)),Mp);

    Fp = COMP(OROP,CCONC(Lp,Mp));
    break;

  case ANDOP:
    Fp = NIL;
    for(L = CINV(RED(F)); L != NIL; L = RED(L))
      Fp = COMP(FMAOPCOMBINE(FIRST(L)),Fp);
    Fp = COMP(ANDOP,Fp);
    break;

  default:
    Fp = F;
  }

  return Fp;
}
   

Word FMAQEXTAF(Word F) 
{
  return (ISLIST(FIRST(F)) && ISLIST(SECOND(F)));
}
