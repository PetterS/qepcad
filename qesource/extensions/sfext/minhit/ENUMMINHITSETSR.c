/*======================================================================
                      C <- ENUMHITSETSRDR(A,B)

Enumerates all hitting sets.  With some special conditions.

Inputs
  A  : A list (l_1, ..., l_n), each l_i is a list of BETA-digits,
       given in ascending order.
  B  : A BETA-Digit.

Output
  C  : MC_FAIL [ 0 ] if no hit set of size B or less exists.  B < 0 is
       used to indicate positive infinity by the way. Otherwise, we get
       a list of all hitting sets, with a strange restriction.  If i 
       and j are both in a hitting set, then 
       rem((i-1)/3) /= rem((j-1)/3).
======================================================================*/
#include "qepcad.h"
#define BDCOMP(a,b)  ((a) > (b) ? 1 : ((a) < (b) ? -1 : 0))
#define MC_FAIL 0

static Word comp(Word a, Word b) { return BDCOMP(LENGTH(a),LENGTH(b)); }
     
Word ENUMMINHITSETSRDR(Word A, Word B)
{
      Word n,*N,i,Ap,L;

Step1: /* Quick decisions. */
      if (A == NIL) return (NIL);
      if ((B == 0) || (FIRST(A) == NIL)) return (MC_FAIL);

Step2: /* Sort Rows. */
      n = LENGTH(A);
      N = GETARRAY(n);
      i = 0;
      for(L = A; L != NIL; L = RED(L))
        N[i++] = FIRST(L);
      GMS(N,n,comp);
      
Step3: /* Reconstruct list. */
      Ap = NIL;
      for(i = n - 1; i >= 0; i--)
        Ap = COMP(N[i],Ap);

Return: /* Return. */
      FREEARRAY(N);
      return (ENUMMINHITSET(Ap,B,NIL));
}
