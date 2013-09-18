/*======================================================================
                      L <-- ISFECLI(D)

Initialize stack for ECLI

Inputs
  D : is a partial CAD.

Outputs
  L : is a list of the indices of the eligible cells in D, in
      lexicographic order.
======================================================================*/
#include "qepcad.h"

Word QepcadCls::ISFECLI(Word D)
{
       Word S,L,c,s;

Step1: /* Initialize */
       S = LIST1(D);
       L = NIL;

Step2: /* Traverse the tree in lexicographic order, adding each eligible
cell that's encountered to the list L. Then invert L so that its 
elements are in lexicographic order. */
       while(S != NIL) {
	 ADV(S,&c,&S);
	 if (LELTI(c,TRUTH) == UNDET) {
	   s = LELTI(c,CHILD);
	   if (s == NIL) {
	     if (PCUSEDES != 'y' || ISDESIRED(c,PCDESIRED) == 1)
	       L = COMP(LELTI(c,INDX),L); }
	   else
	     S = CCONC(s,S); } }
       L = INV(L);

Return: /* Prepare to return. */
       return L;
}
