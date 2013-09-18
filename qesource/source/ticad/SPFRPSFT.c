/*===========================================================================
                      SPFRPSFT(P,c,k; R,F)

Substituted Projection Factor Relative Prime / Square Free Test.
     
\Input
  \parm{P} is the list~$(P_1,\ldots,P_r)$, 
           where $P_i$ is the list of
           $i$--level projection factors.
  \parm{c} is a cell.
  \parm{k} is the level of the cell~$c$.
 
Output:
  \parm{R} is a (upper triangular) matrix $(R_{i,j})$ where 
           $R_{i,j} = 1$ if $P_{k+1,i}(s)$ and $P_{k+1,j}(s)$ are
           relatively prime, 0 otherwise,  where $s$ is the sample
           point of $c$.
  \parm{F} is a list $(F_i)$ where $F_i = 1$ if $P_{k+1,i}(s)$ is 
           squarefree, 0 otherwise.
===========================================================================*/
#include "qepcad.h"

void SPFRPSFT(Word P, Word c, Word k, Word *R_, Word *F_)
{
       Word R,F,Pk1,l,R1,i,j,S,Si,Pi,Sij,Pij,G,g;
       Word H,h,f1,f2,f3,f4,f5,f6,n,n1,n2,L,L1,L2;

Step1: /* Initialize. */
       Pk1 = LELTI(P,k+1);
       l = LENGTH(Pk1);

       R = NIL;
       for (i=1; i<=l; i++) {
	  R1 = NIL;
	  for (j=1; j<=l; j++)
	     R1 = COMP(1,R1);
	  R = COMP(R1,R); }

       F = NIL;
       for (i=1; i<=l; i++)
	  F = COMP(1,F);

       if (l == 0) goto Return;

Step2: /* Update. */
       S = LELTI(c,SIGNPF);
       S = CINV(S);
       for (i=1; i<=k; i++) {
	  ADV(S,&Si,&S);
	  ADV(P,&Pi,&P);
	  while (Si != NIL) {
	     ADV(Si,&Sij,&Si);
	     ADV(Pi,&Pij,&Pi);
	     if (Sij != 0) continue;
	     G = LELTI(Pij,PO_PARENT);
	     while (G != NIL) {
		ADV(G,&g,&G);
		if (FIRST(g) != PO_FAC) continue;
		H = LELTI(THIRD(g),PO_PARENT);
		while (H != NIL) {
		   ADV(H,&h,&H);
		   switch(FIRST(h)) {
                   case PO_LCO:
		      FIRST3(h,&f1,&f2,&f3);
		      if (f2 != 0) break;
		      L = LELTI(f3,PO_LABEL);
		      if (SECOND(L) != k+1) break;
		      n = PLPOS(Pk1,THIRD(L));
		      if (n == 0) FAIL("SPFRPSFT","PO_LCO");
		      SLELTI(F,n,0);               
		      break;
	           case PO_DIS:
		      FIRST4(h,&f1,&f2,&f3,&f4);
		      if (f2 != 0 || f3 != 0) break;
		      L = LELTI(f4,PO_LABEL);
		      if (SECOND(L) != k+1) break;
		      n = PLPOS(Pk1,THIRD(L));
		      if (n == 0) FAIL("SPFRPSFT","PO_DIS");
		      SLELTI(F,n,0);                   
		      break;
                   case PO_RES:
		      FIRST6(h,&f1,&f2,&f3,&f4,&f5,&f6);
		      if (f2 != 0 || f3 != 0 || f5 != 0) break;
		      L1 = LELTI(f4,PO_LABEL);
		      if (SECOND(L1) != k+1) break;
		      L2 = LELTI(f6,PO_LABEL);
		      if (SECOND(L2) != k+1)
			 FAIL("SPFRPSFT","resultant of diff level");
		      n1 = PLPOS(Pk1,THIRD(L1));
		      if (n1 == 0) FAIL("SPFRPSFT","PO_RES: n1");
		      n2 = PLPOS(Pk1,THIRD(L2));
		      if (n2 == 0) FAIL("SPFRPSFT","PO_RES: n2");
		      if (n2 > n1)
			 SLELTI(LELTI(R,n1),n2,0);
		      else
			 FAIL("SPFRPSFT","n2 <= n1");
		      break; } } } } }

Return: /* Prepare for return. */
       *R_ = R;
       *F_ = F;
       return;
}




