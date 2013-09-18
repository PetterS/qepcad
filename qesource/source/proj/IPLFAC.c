/*======================================================================
                      R <- IPLFAC(k,J)

Integral Polynomial List Factorization.

\Input
  \parm{k} is a positive $\beta$--integer.
  \parm{J} is a list of $k$--variate integral polynomials.
  
\Output
  \parm{R} is a list of all distinct positive
           irreducible factors of positive degree in at least one
           variable
======================================================================*/
#include "qepcad.h"

Word IPLFAC(Word k, Word J)
{
       Word J1,Jp,Jp1,L,L1,P,R,W,c,e,s;
       /* hide s; */

Step1: /* Factorize. */
       R = NIL;
       Jp = J;
       while (Jp != NIL)
         {
         ADV(Jp,&J1,&Jp);

	 /* Projection points! */
	 if (LELTI(J1,PO_TYPE) == PO_POINT) {
	   W = MPOLY(LELTI(J1,PO_POLY),NIL,LIST1(LIST3(PO_FAC,1,J1)),PO_POINT,PO_KEEP);
	   R = COMP(W,R);
	   continue;
	 }

         Jp1 = LELTI(J1,PO_POLY);
         if (!PCONST(k,Jp1))
           {
           IPFACDB(k,Jp1,&s,&c,&L);
           while (L != NIL)
             {
             ADV(L,&L1,&L);
             FIRST2(L1,&e,&P);
             W = MPOLY(P,NIL,LIST1(LIST3(PO_FAC,e,J1)),PO_OTHER,PO_KEEP);
             R = COMP(W,R);
             }
           }
         }
       R = INV(R); goto Return;

Return: /* Prepare for return. */
       return(R);
}
