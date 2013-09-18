/*

ForMulA write.

*/

#include "extlang.h"

void FMAWRITE(Word F, Word P, Word V)
{
  Word L,E,i,j,k,op,t,Fp,O,A;

  switch(FTYPEINFO(F)) {

  case ANDOP: case OROP:
      ADV(F,&O,&Fp);
      do {
        ADV(Fp,&A,&Fp);
        t = FTYPEINFO(A);
        if (t != NIL && t != O) { SWRITE("[ "); 
	FMAWRITE(A,P,V); SWRITE(" ]"); }
        else FMAWRITE(A,P,V);
      if (Fp == NIL) break;
        if (O == OROP)  SWRITE(" \\/ ");
        if (O == ANDOP) SWRITE(" /\\ ");
      } while(1);
      break;
    
  case TRUE : SWRITE("TRUE"); break;
    
  case FALSE: SWRITE("FALSE"); break;

  case NIL :
    FIRST2(FIRST(F),&i,&j);
    j = POLINDEX2SIGINDEX(LELTI(P,i),j);
    if (ISATOM(SECOND(F))) {
      IPDWRITE(i,LELTI(LELTI(LELTI(P,i),j),PO_POLY),V);
      switch(SECOND(F)) {
      case (LTOP) : SWRITE(" < 0"); break;
      case (LEOP) : SWRITE(" <= 0"); break;
      case (GTOP) : SWRITE(" > 0"); break;
      case (GEOP) : SWRITE(" >= 0"); break;
      case (EQOP) : SWRITE(" = 0"); break;
      case (NEOP) : SWRITE(" /= 0"); break; }      
    }
    else {
      FIRST2(SECOND(F),&op,&k);
      VWRITE(LELTI(V,i));
      switch(op) {
      case (LTOP) : SWRITE(" < _root_"); break;
      case (LEOP) : SWRITE(" <= _root_"); break;
      case (GTOP) : SWRITE(" > _root_"); break;
      case (GEOP) : SWRITE(" >= _root_"); break;
      case (EQOP) : SWRITE(" = _root_"); break;
      case (NEOP) : SWRITE(" /= _root_"); break; }
      IWRITE(k); SWRITE(" ");
      IPDWRITE(i,LELTI(LELTI(LELTI(P,i),j),PO_POLY),V); }
    break; }
  return;
}
