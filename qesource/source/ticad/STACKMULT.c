/*=====================================================================
                       M <- STACKMULT(c)

Stack multiplicity list.

Inputs
   c : a cell over which a stack has been constructed.

Outputs
   M : a list (M_1,...,M_k), where k is the number of
       sections in the stack over c.  M_i is the list
       (2 * i,m_i), where 2 * i is the last index of
       the i-th section in the stack over c and m_i 
       is the list of multiplicities of the substituted
       projection factors for the i-th section.
======================================================================*/
#include "qepcad.h"

Word STACKMULT(Word c)
{
	Word d,i,m,p,M,S;

Step1: /* Get the stack over c. */
	S = LELTI(c,CHILD);

Step2: /* Construct the stack multiplicity list. */
	M = NIL;
	if (S == NIL)
	   goto Return;
	S = RED(S);
	if (S == NIL)
	   goto Return;
	i = 2;
	while (S != NIL) {
	   d = FIRST(S);
	   m = LELTI(d,MULSUB);
	   p = LIST2(i,m);
	   M = COMP(p,M);
	   i = i + 2;
	   S = RED2(S); }
	M = INV(M);

Return: /* Return M. */
	return (M);
}
