/* Pruned CAD cell HOWTV value.
   C : A pruned CAD cell.
   P : The projection factor set which defines the signitures of the actual
       CAD cells referenced in C.
   Ps: The projection factor set for the PCAD in which C resides. 
*/
#include "qepcad.h"

Word PCELLHOWTV(Word C, Word P, Word Ps)
{
      Word L,l,h;

      h = UNDET;
      L = CELLSCPCELL(C,P,Ps);
      while (L != NIL) {
	ADV(L,&l,&L);
	if (LELTI(l,HOWTV) == BYPRP ) {
	  h = BYPRP;
	  break; } }
      return (h);
}
