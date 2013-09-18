/* Projection factor position in projection factor list. */
#include "qepcad.h"

Word PFPIPFL(Word p, Word L)
{
      Word i_p,i,Lp;

      i_p = RED(LELTI(p,PO_LABEL));

      i = 1; Lp = L;
      while ( Lp != NIL && ( ! EQUAL(i_p,RED(LELTI(FIRST(Lp),PO_LABEL))))) { 
	Lp = RED(Lp); i++; }

      if ( Lp == NIL )
	i = 0;

      return (i);
}
