/*

ForMulA write.

*/

#include "extlang.h"

#define OFF 2

void FMAWRITENEWLINE(Word F, Word P, Word V, Word n)
{
  Word L,E,i,j,k,op,t,Fp,O,A;

  switch(FTYPEINFO(F)) {

  case ANDOP: case OROP:
      ADV(F,&O,&Fp);
      do {
        ADV(Fp,&A,&Fp);
        t = FTYPEINFO(A);
        if (t != NIL && t != O) { TAB(n); SWRITE("[\n"); 
	FMAWRITENEWLINE(A,P,V,n+OFF); SWRITE("\n"); TAB(n); SWRITE("]"); }
        else FMAWRITENEWLINE(A,P,V,n);
      if (Fp == NIL) break;
      if (O == OROP)  { SWRITE("\n"); TAB(n); SWRITE("\\/\n"); }
      if (O == ANDOP) { SWRITE("\n"); TAB(n); SWRITE("/\\\n"); }
      } while(1);
      break;
    
  case TRUE : TAB(n); SWRITE("TRUE"); break;
    
  case FALSE: TAB(n); SWRITE("FALSE"); break;

  case NIL :
    TAB(n);
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


void FMAWRITENEWLINEp(Word F, Word P, Word V, Word flag)
{
  Word L,E,i,j,k,op,t,Fp,O,A;

  switch(FTYPEINFO(F)) {

  case ANDOP: case OROP:
      ADV(F,&O,&Fp);
      do {
        ADV(Fp,&A,&Fp);
        t = FTYPEINFO(A);
        if (t != NIL && t != O) { SWRITE("[ "); 
	FMAWRITENEWLINEp(A,P,V,flag); SWRITE(" ]"); }
        else FMAWRITENEWLINEp(A,P,V,flag);
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
