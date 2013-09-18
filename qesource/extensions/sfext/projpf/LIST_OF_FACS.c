/*======================================================================
                       L <- LIST_OF_FACS(Q,P)

List of projection factors which are factors of given projection 
polynomial.

Input:
 Q : a projection polynomial.
 P : the projection factor structure.

Output:
 L : a list of all projection factors which are factors of Q.

Note:  The PO_PARENT field is a little nasty in that, if there's a
unique history, it is the PO_PARENT field, rather than a list 
containing that history.
======================================================================*/
#include "qepcad.h"

Word LIST_OF_FACS(Word Q, Word P_)
{
      Word L,l,P,Pp,p,D,a,b,c;

Step1: /* Initialization. */
      L = NIL;
      l = LELTI(Q,PO_LABEL);

Step2: /* Loop over the levels of the projection factor structure. */
      for(P = P_; P != NIL; P = RED(P)) {

Step3: /* Loop over the elements of a given level. */
	for(Pp = FIRST(P); Pp != NIL; Pp = RED(Pp)) {
	  p = FIRST(Pp);

Step4: /* Loop over the elements of the history. */
	  for(D = LELTI(p,PO_PARENT); D != NIL; D = RED(D)) {
	    if ( ISATOM(FIRST(D)) )
	      FIRST3(D,&a,&b,&c);
	    else
	      FIRST3(FIRST(D),&a,&b,&c);
	    if (a == PO_FAC && EQUAL(l,LELTI(c,PO_LABEL))) {
	      L = COMP(p,L); break; }
	    if ( ISATOM(FIRST(D)) )
	      break; } } }

Return: /* Return. */
      return (CINV(L));
}
    
      
