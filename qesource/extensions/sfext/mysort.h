#include "qepcad.h"

/*======================================================================
                      GIS(A,n,C)

General insertion sort.

Inputs
A : An array of pointers to n words.
n : A positive BETA-digit.
C : A pointer to a function of two arguments returning type Word.
Side Effects
    The n entries of A are sorted with respect to the
    function C using insertion sort. Sort is stable.
  ======================================================================*/

extern void GIS(Word *A,Word m,Word (*C)(Word,Word));

/*======================================================================
                      GIS(A,m,C)

General merge sort.

Inputs
A : An array of pointers to m words.
m : A positive BETA-digit.
C : A pointer to a function of two arguments returning type Word.
Side Effects
    Rearranges the values in A so that they are in sorted order
    with respect to C. Merge sort is used.  Sort is stable.
  ======================================================================*/

extern void GMS(Word *A,Word m,Word (*C)(Word,Word));


/*======================================================================
                      mp <- GMSDS(A,m,C)

General merge sort with duplicate supression.

Inputs
A : An array of m words.
m : A positive BETA-digit.
C : A pointer to a function of two arguments returning type Word.
Outputs
mp: the number of distinct array elements.
Side Effects
    Rearranges the values in A so that the first mp entries are distinct
    and in sorted order.  The set of elements in A is the same as on 
    input.
  ======================================================================*/
Word GMSDS(Word *A, Word m, Word (*C)(Word,Word));


extern Word BVC(Word *u_,Word *v_,Word n);
extern void BVIS(Word **A,Word m,Word n);
extern Word BVCI1(Word *u_,Word *v_,Word n);
extern void BVISI1(Word **A,Word m,Word n);
