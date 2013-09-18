/* 

ForMulA index write.

*/
#include "extlang.h"

void FMAIWRITE(Word F)
{
  Word L,E;

  switch(FIRST(F)) {
  case ANDOP:
    SWRITE("[ ");
    L = RED(F);
    do {
      ADV(L,&E,&L);
      FMAIWRITE(E);
    if (L == NIL) break;
      SWRITE(" /\\ ");
    }while(1);
    SWRITE(" ]");
    break;

  case OROP:
    SWRITE("[ ");
    L = RED(F);
    do {
      ADV(L,&E,&L);
      FMAIWRITE(E);
    if (L == NIL) break;
      SWRITE(" \\/ ");
    }while(1);
    SWRITE(" ]");
    break;
    
  case TRUE : SWRITE("TRUE"); break;
    
  case FALSE: SWRITE("TRUE"); break;

  default:
    SWRITE("P_");
    OWRITE(FIRST(F));
    switch(SECOND(F)) {
    case (LTOP) : SWRITE(" < 0"); break;
    case (LEOP) : SWRITE(" <= 0"); break;
    case (GTOP) : SWRITE(" > 0"); break;
    case (GEOP) : SWRITE(" >= 0"); break;
    case (EQOP) : SWRITE(" = 0"); break;
    case (NEOP) : SWRITE(" /= 0"); break; }
    break;
  }
  
  return;
}
