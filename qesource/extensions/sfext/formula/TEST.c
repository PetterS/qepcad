/***************************************************
 Set Order
 D - an ESPCAD
 P - the projection factor set for D
 F - a formula
 o - an order
 ***************************************************/
#include "espcad.h"

/***************************************************
 Set cells with true mark to order o
 D - ESPCAD cell
 o - an order
 ***************************************************/
static void mark2order(Word D,Word o)
{
/*   if (ISLIST(LELTI(D,SC_CDTV))) */
/*     for(L = LELTI(D,SC_CDTV); L != NIL; L = RED(L)) */
/*       mark2order(FIRST(L),o); */
/*   else  */
/*     if (LELTI(D,SC_TMPM) == TRUE) */
/*       SLELTI(D,SC_CDTV, o); */
/*   return; */
}

void SETORDERfromFMA(Word D,Word P,Word F,Word o)
{
  SETMARK2FMA(D,F,P);
  mark2order(D,o);
  return;
}

/***************************************************
 D - an ESPCAD
 P - the projection factor set for D
 V - the variable list
 ***************************************************/
void SETORDER(Word D,Word P,Word V)
{
  // Get L = (F_{-1},F_0,F_1,F_2,...,F_{d-1})

  // Set Orders
/*   SETORDERfromFMA(D,P,LIST1(TRUE),d+1); // default to d+1 */
/*   for(Lp = L, o = -1; Lp != NIL; Lp = RED(Lp), o++) */
/*     SETORDERfromFMA(D,P,FIRST(Lp),o); */
  
/*   // Get latest "Formula", i.e. \/ of all partials not zero */
/*   do { */
/*     SWRITE("Enter the disjunction of partials formula:\n"); */
/*     FMAREAD(P,V,&F,&t); */
/*   }while(!t);  */
/*   SETORDERfromFMA(D,P,LIST3(ANDOP,LIST2(NOT,COMP(OROP,L)),F),o); */
    
  // Simplify

  // Write formulas for each of the orders

  return;
}
