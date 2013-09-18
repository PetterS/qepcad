/*======================================================================
                      MARK(L)

Mark.  

Inputs
  L : a non-null list or GCA handle such that every cell of L which is 
      accessible from an already marked cell of L is itself already marked.   

Side effects
  MARK marks every unmarked cell of L.
======================================================================*/
#include "saclib.h"

void MARK(L)
       Word L;
{
       Word I,Lp,o,*a,i,l;
       /* hide I,Lp,o,a,l; */

Step1: /* Check for list/GCA handle. */
       if (L > BETAp)
	 goto Step3;

Step2: /* Recursively mark a list. */
       Lp = L;
       while (Lp != NIL) {
         I = Lp;
         Lp = SPACEB[Lp];
         if (Lp < 0)
           goto Return;
         SPACEB[I] = -Lp;
         o = SPACEB1[I];
         if ((ISLIST(o) || ISGCA(o)) && !ISNIL(o)) MARK(o);
       }
       goto Return;

Step3: /* Recursively mark a GCA handle. */
       Lp = L;
       while (Lp != NIL) {
         I = Lp;
         Lp = GCASPACEBp[Lp].next;
         if (Lp < 0)
           goto Return;
         GCASPACEBp[I].next = -Lp;
	 if (GCASPACEBp[I].flag == GC_NO_CHECK)
	   goto Return;
         a = GCASPACEBp[I].array;
         l = GCASPACEBp[I].len;
	 for (i=0;i<l;i++) {
	   o = a[i];
           if ((ISLIST(o) || ISGCA(o)) && !ISNIL(o)) MARK(o);
	 }
       }

Return: /* Prepare for return. */
        return;
}
