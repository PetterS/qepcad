/*======================================================================
                      c <- CELLNA(I,D)

Cell index to nearest ancestor.

Inputs
  I : is the index of a cell.
  D : is a partial CAD.

Outputs
  c : is the cell with index I, provided that cell still exists in D.
      If it has been removed from D, its nearest ancestor is returned.      
======================================================================*/
#include "qepcad.h"

Word CELLNA(Word I, Word D)
{
       Word Ip,i,c,s;

Step1: /* Initialize. */
       Ip = I;
       c = D;

Step2: /* Iterate over the components of the index until a cell is 
reached with no children. */
       while(Ip != NIL) {
	 s = LELTI(c,CHILD);
	 if (s == NIL)
	   break;
	 ADV(Ip,&i,&Ip);
	 c = LELTI(s,i); }

Return: /* Prepare to return. */
       return c;
}

