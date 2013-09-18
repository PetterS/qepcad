/*  Add  root_k function. 

    kth root of the i-level projection factor referred to by the
    jth position in the signiture list is what's to be added.

*/
#include "extlang.h"

void ADDROOTKFUNC(Word i, Word j, Word k, Word C)
{
       Word S,n,c,s,t,es;

Step1: /* Initialize, and abort if no children. */
       S = LELTI(C,SC_CDTV);
       if (!ISLIST(S))
	 goto Return;

Step2: /* If C's children are of level i. */
       if (i == 1) {
	 for(n = 0; S != NIL; S = RED(S)) {
	   c = FIRST(S);
	   s = LELTI(LELTI(c,SC_SIGN),j);
	   if (s == 0) n++;
	   if (n < k)
	     t = NEGATIVE;
	   else if (n == k && s == 0)
	     t = ZERO;
	   else
	     t = POSITIVE;
	   es = LELTI(c,SC_EXTS);
	   SLELTI(c,SC_EXTS,COMP(t,es)); }
	 if (n < k) {
	   for(S = LELTI(C,SC_CDTV); S != NIL; S = RED(S)) {
	     c = FIRST(S);
	     es = RED(LELTI(c,SC_EXTS));
	     SLELTI(c,SC_EXTS,COMP(FNOTDEF,es)); } } }
       else {

Step3: /* If C's children of level < i, recurse. */
	 while(S != NIL) {
	   ADDROOTKFUNC(i-1,j,k,FIRST(S));
	   S = RED(S); } }

Return: /* Prepare to return. */
       return;
}
