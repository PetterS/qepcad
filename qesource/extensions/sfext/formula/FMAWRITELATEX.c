/*

ForMulA write.

*/

#include "extlang.h"

void FMAWRITELATEX(Word F, Word P, Word V)
{
  Word L,E,i,j,k,op,t,Fp,O,A;

  switch(FTYPEINFO(F)) {

  case ANDOP: case OROP:
      ADV(F,&O,&Fp);
      do {
        ADV(Fp,&A,&Fp);
        t = FTYPEINFO(A);
        if (t != NIL && t != O) { SWRITE("\\left[ "); 
	FMAWRITELATEX(A,P,V); SWRITE(" \\right]"); }
        else FMAWRITELATEX(A,P,V);
      if (Fp == NIL) break;
        if (O == OROP)  SWRITE(" \\vee ");
        if (O == ANDOP) SWRITE(" \\wedge ");
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
      case (LEOP) : SWRITE(" \\leq 0"); break;
      case (GTOP) : SWRITE(" > 0"); break;
      case (GEOP) : SWRITE(" \\geq 0"); break;
      case (EQOP) : SWRITE(" = 0"); break;
      case (NEOP) : SWRITE(" \\neq 0"); break; }      
    }
    else {
      FIRST2(SECOND(F),&op,&k);
      VWRITE(LELTI(V,i));
      switch(op) {
      case (LTOP) : SWRITE(" < root_{"); break;
      case (LEOP) : SWRITE(" <= root_{"); break;
      case (GTOP) : SWRITE(" > root_{"); break;
      case (GEOP) : SWRITE(" >= root_{"); break;
      case (EQOP) : SWRITE(" = root_{"); break;
      case (NEOP) : SWRITE(" /= root_{"); break; }
      IWRITE(k); SWRITE("} ");
      IPDWRITELATEX(i,LELTI(LELTI(LELTI(P,i),j),PO_POLY),V); }
    break; }
  return;
}


void FMAWRITELATEXp(Word F, Word P, Word V, Word flag)
{
  Word L,E,i,j,k,op,t,Fp,O,A;

  switch(FTYPEINFO(F)) {

  case ANDOP: case OROP:
      ADV(F,&O,&Fp);
      do {
        ADV(Fp,&A,&Fp);
        t = FTYPEINFO(A);
        if (t != NIL && t != O) { SWRITE("[ "); 
	FMAWRITELATEXp(A,P,V,flag); SWRITE(" ]"); }
        else FMAWRITELATEXp(A,P,V,flag);
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
      if (flag) {
	IPDWRITE(i,LELTI(LELTI(LELTI(P,i),j),PO_POLY),V); }
      else {
	SWRITE("P_("); IWRITE(i); SWRITE(","); IWRITE(j); SWRITE(")"); }
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
      if (flag) {
	IPDWRITE(i,LELTI(LELTI(LELTI(P,i),j),PO_POLY),V); }
      else {
	SWRITE("P_("); IWRITE(i); SWRITE(","); IWRITE(j); SWRITE(")"); }
    }
    break; }
  return;
}
