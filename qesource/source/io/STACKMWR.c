/*=====================================================================
                         STACKMWR(M)

Stack multiplicities write.

Inputs
   M : a list of the sections in a stack and their adjacencies
       such as is produced by STACKMULT.

Effect
   The sections and their multiplicity lists are written out.
======================================================================*/
#include "qepcad.h"

void STACKMWR(Word M)
{
	Word f,i,L,m,p,P;

Step1: /* Write the section numbers and their multiplicity
          lists. */
	if (M== NIL) {
	   SWRITE("No sections in stack.\n");
	   goto Return; }
	i = 1;
	while (M != NIL) {
	   P = FIRST(M);
	   SWRITE("Section ");
	   IWRITE(i);
	   SWRITE("\n");
	   L = SECOND(P);
	   while (L != NIL) {
	      p = FIRST(L);
	      FIRST2(p,&f,&m);
	      SWRITE("   proj. factor ");
	      IWRITE(f);
	      SWRITE("   mult. ");
	      IWRITE(m);
	      SWRITE("\n");
	      L = RED(L); }
	   M = RED(M);
	   i = i + 1; }

Return: /* Return. */
	return;
}
