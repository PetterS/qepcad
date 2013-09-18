/*======================================================================
                     t <- CTSEQ(as,bs)

Cell truth structure equality.

inputs
  as : A pruned cad cell.
  bs : A pruned cad cell nieghboring a in the stack.
outputs
  t : 1 if as and bs have the same truth structure, 0 otherwise
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

Word CTSEQ(Word as, Word bs)
{
      Word la,lb,T,ca,cb,t;

Step1: /* Get the child/truth value for as and bs. */
      la = LELTI(as,SC_CDTV);
      lb = LELTI(bs,SC_CDTV);


Step2: /* Test for equivalent truth structure according to whether
	  as and bs have children. */
      T = (ISATOM(la) << 1) | ISATOM(lb);
      switch(T) {

      case (0) : /* Both as and bs have children. */
	do {
	  ADV(la,&ca,&la); ADV(lb,&cb,&lb);
	  t = CTSEQ(ca,cb);
	} while((t) && (la != NIL));
	break;

      case (1) : /* as has children, but bs does not. */
	t = CHTVQ(as,lb);
	break;

      case (2) : /* bs has children but as does not. */
	t = CHTVQ(bs,la);
	break;

      case (3) : /* Neither as nor bs have children. */
	t = (la == lb);
	break; }

Return: /* Prepare to return. */
      return (t);
}
