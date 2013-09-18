/*======================================================================

Cell 1D to edge list.

I need a function that gives a list of edges for base cells
cl, cm, and cr.

======================================================================*/
#include "truthbytop.h"
#include "adj2D.h"

Word C1DTOEDGELIST(Word cl, Word cm, Word cr)
{
  Word E,L,i,Ll,Lr,l,a,b,t;

Step1: /* Initialize. */
  E = NIL;

Step2: /* Get adjacencies for (cl,cm) and (cr,cm). */
  L = FIRST(ADJ_2D_PART(cm,cl,cr,P,J));
  i = LAST(LELTI(cm,INDX));
  Ll = NIL; Lr = NIL;
  while(L != NIL) {
    ADV(L,&l,&L);
    FIRST2(l,&a,&b);
    if (FIRST(a) == i) {
      t = a; a = b; b = t; }
    if (FIRST(a) < i)
      Ll = COMP(LIST2(a,b),Ll); 
    else
      Lr = COMP(LIST2(a,b),Lr); }

Step3: /* Get edges from adjacency info. */
  E = CONC(ADJ2DITOEL(Ll,cl,cm),E);
  E = CONC(ADJ2DITOEL(Lr,cr,cm),E);
    
Return: /* Prepare to return. */
  return E;
}

/* Adjacecy 2D information to edge list. */
Word ADJ2DITOEL(L,c1,c0)
       Word L,c1,c0;
{
  Word *A, E,n,l,s,a,b,k1,k0,i,itop,ibot;

Step1: /* Initialize & Special Case. */
  E = NIL;
  n = LENGTH(LELTI(c1,CHILD));
  if (n == 0)
    goto Return;

Step2: /* Store adjacency info. */
  A = GETARRAY(n+1);
  while (L != NIL) {
    ADV(L,&l,&L);
    FIRST2(l,&a,&b);
    A[SECOND(a)] = SECOND(b); }

Step3: /* Put section adjacency info. into list. */
  k1 = FIRST(LELTI(c1,INDX));
  k0 = FIRST(LELTI(c0,INDX));
  for(i = 2; i <= n; i += 2)
    if (A[i] != AD2D_Infy && A[i] != AD2D_N_In)
      E = COMP(LIST2(LIST2(k1,i),LIST2(k0,A[i])),E);

Step4: /* Put sector adjacency info. into list. */
  for(i = n; i > 1 && A[i-1] == AD2D_Infy; i-=2);
  for(itop = LENGTH(LELTI(c0,CHILD)); i > 1 && A[i-1] != AD2D_N_In; i-=2)
    for(ibot = A[i-1]; itop > ibot; itop -= 2)
      E = COMP(LIST2(LIST2(k1,i),LIST2(k0,itop)),E);
  for(; itop > 0; itop -= 2)
      E = COMP(LIST2(LIST2(k1,i),LIST2(k0,itop)),E);

Return: /* Prepare to return. */
  FREEARRAY(A);
  return E;
}
