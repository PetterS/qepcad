/*======================================================================
                      A <- GCAMALLOC(s,f)

Garbage collected array memory allocation.

Inputs
  s : a BETA-digit, the size of the array in Words.
  f : a BETA-digit. 
      f = GC_CHECK, if the array will contain list or GCA handles,
      f = GC_NO_CHECK, otherwise.

Outputs  
  A : a GCA handle (NOT the memory pointer) for the array.

Side effects
  A cell is taken from GCAAVAIL, an array of s Words is allocated from
  the heap. If GCAAVAIL is empty, GC() is called.
======================================================================*/
#include "saclib.h"

Word GCAMALLOC(s,f)
       Word s,f;
{
       Word A;

Step1: /* Is GCAAVAIL empty? */
       if (GCAAVAIL == NIL) 
         GC();
   
Step2: /* Get new cell. */
       A = GCAAVAIL; 
       GCAAVAIL = GCASPACEBp[A].next;
       GCASPACEBp[A].next = NIL;

Step3: /* Allocate memory. */
       GCASPACEBp[A].array = (Word *)malloc((unsigned)(sizeof(Word)*s));
       if (GCASPACEBp[A].array == (Word *)0)
	 FAIL("GCAMALLOC","Out of memory.");
       GCASPACEBp[A].len = s;
       GCASPACEBp[A].flag = f;

Return: /* Prepare for return. */
       return(A);
}
