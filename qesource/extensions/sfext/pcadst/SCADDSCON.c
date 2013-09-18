/*======================================================================
                      Cs <- SCADDSCON(C,A)

Sub-CAD data structure construct.

Inputs
  C : A partial cad.
  A : The ancestor of C.
  n : The highest level to allow the CAD to go.

Outputs
  Cs: A sub-CAD data structure representing the input cad.

Note:  The sub-cad data structure:

(c,L,a,i,S)  SC_REP 1  SC_PAR 2  SC_INX 3  SC_CDTV 4

c : A cell in C which represents c.
a : The ancestor of c (NIL if c is the root cell)
i : The index of c in its stack.
L : If c has children then a list of its children (each element being
    a sub-cad cell structure).  If c has no children, then its truth 
    value.

This is a recursive data structure, so trying to 'OWRITE' it, for
example, would be bad.
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

Word SCADDSCON(Word C, Word A, Word n)
{
      Word c,a,i,Cs,X,L,t;

Step1: /* Construct a preliminary version of Cs, with all but the child
	  list filled in. */
      c = C;
      a = A;
      if (A == NIL)
	i = 0;
      else 
	i = LAST(LELTI(C,INDX));
      if (n == 0) {
	Cs = LIST4(c,a,i,CATV(C));
	goto Return; }
      else
	Cs = LIST4(c,a,i,NIL);

Step2: /* Fill in the child list, using the list handle for Cs for
	  recursive calls to SCADDSCON. */
      X = LELTI(C,CHILD);
      if (X == NIL)
	L = LELTI(C,TRUTH);
      else {
	X = CINV(X);
	L = NIL;
	while (X != NIL) {
	  L = COMP(SCADDSCON(FIRST(X),Cs,n-1),L);
	  X = RED(X); } }

Step3: /* Set the SC_CDTV element to L as constructed in Step2. */
      SLELTI(Cs,SC_CDTV,L);

Return: /* Prepare to return. */
      return (Cs);

}
