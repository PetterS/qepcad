/*===========================================================================
                      Ps <- APPENDEC(P,k,R)

Append, equational constraint version.

\Input 
  \parm{P} is a list $(P_1,\ldots,P_r)$ where each $P_i$
           is a list of distinct $i$--level integral polynomials, $ r > 0$.
  \parm{k} is a positive $\beta$--integer, $k \leq r$.
  \parm{R} is a list of $k$--variate integral polynomials
           of positive degree in at least one variable.
  
\Output
  \parm{P*} is a list $(P^*_1,\ldots,P^*_r)$ where each $P^*_i$
            is a list obtained from $P_i$ by appending all the
            $i$--level polynomials in $R$ if there are not 
            already there.
   F : a list of all elements in R in the same format as the elements in P^*_i.

\SideEffect
  \parm{P}  is modified.
===========================================================================*/
#include "qepcad.h"

void APPENDEC(Word P, Word k, Word R, Word *Ps_, Word *F_)
{
       Word F,Ph,P1,Ph1,Ps,R1,Rp,Rp1,Rs1,i,ks,t;

Step1: /* Append. */
       F = NIL;
       Ps = P; Rp = R;
       while (Rp != NIL) {
	  ADV(Rp,&R1,&Rp);
	  Rp1 = LELTI(R1,PO_POLY);
	  PSIMREP(k,Rp1,&ks,&Rs1);
	  Ph = LELTI(P,ks);
	  t = 0;
	  while (Ph != NIL) {
	     ADV(Ph,&P1,&Ph);
	     Ph1 = LELTI(P1,PO_POLY);
	     if (EQUAL(Rs1,Ph1)) {
		SLELTI(P1,PO_PARENT,
		       CONC(LELTI(P1,PO_PARENT),LELTI(R1,PO_PARENT)));
		F = COMP(P1,F);
		t = 1;
		break; } }
	  if (t == 0) {
	     Ph = LELTI(P,ks);
	     i = LENGTH(Ph) + 1;
	     SLELTI(R1,PO_LABEL,LIST3(LFS("P"),ks,i));
	     SLELTI(R1,PO_POLY,Rs1);
	     Ph = SUFFIX(Ph,R1);
	     F = COMP(R1,F);
	     SLELTI(P,ks,Ph); } }

Return: /* Prepare for return. */
       *Ps_ = Ps;
       *F_ = F;
       return;
}
