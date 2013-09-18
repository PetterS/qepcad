/*======================================================================
                      IPLLDWRMOD(V,A)

Integral Polynomial, List of Lists, Distributed Write, modified.

\Input
  \parm{V} is a non-null list of $r$ variables.
  \parm{A} is a list $(A_1, \ldots, A_r)$ where $A_i$ is a list of 
           integral polynomials.
======================================================================*/
#include "qepcad.h"

void IPLLDWRMOD(Word V, Word A)
{
       Word A1,A11,i,P,L,H;
       /* hide i,j,n,r; */

Step1: /* Write. */
       while (A != NIL)
         {
         ADV(A,&A1,&A);
         while (A1 != NIL)
           {
           ADV(A1,&A11,&A1);
	   i = SECOND(LELTI(A11,PO_LABEL));
           PLABELWR(A11);
           TAB(7);
           SWRITE("= "); 
           H = LELTI(A11,PO_PARENT);
           PARENTWR(H);
           if (LELTI(A11,PO_STATUS) == PO_REMOVE)
             SWRITE("  *** Removed ***  ");
           if (LELTI(A11,PO_TYPE) == PO_ECON)
             SWRITE("  *** Equational Constraint ***  ");
           P = LELTI(A11,PO_POLY);
           SWRITE("\n");
           TAB(7);
           SWRITE("= "); 
           IPDWRITE(i,P,V); 
           SWRITE("\n");
           }
         if (A != NIL)
           SWRITE("\n");
         }

Return: /* Prepare for return. */
       return;
}
