/*======================================================================
                      GMSDSL(A,C)

General merge sort with duplicate suppression for lists.

Inputs
A : A list.
C : A pointer to a function of two arguments returning type Word.

Output
Ap: The list A, sorted with respect to C.

  ======================================================================*/
#include "mysort.h"

Word GMSDSL(Word A, Word (*C)(Word,Word))
{
       Word *B,b,Ap,i;

Step1: /* Store A in array B. */
       b = LENGTH(A);
       B = GETARRAY(b);
       i = 0;
       for(Ap = A; Ap != NIL; Ap = RED(Ap))
	 B[i++] = FIRST(Ap);

Step2: /* Sort B, and write its entries to list Ap. */
       b = GMSDS(B,b,C);
       for(i = b; i > 0; Ap = COMP(B[--i],Ap));

Return: /* Deallocate memory and return. */
       FREEARRAY(B);
       return(Ap);
}
