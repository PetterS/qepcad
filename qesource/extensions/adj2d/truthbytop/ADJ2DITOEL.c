/*======================================================================

Adjacecy 2D information to edge list.

Inputs
  L  : a list of adjacency assingments between cells over c1 and cells
       over c0.
  c1 : a sector cell in the CAD 1-space.
  c0 : a section cell adjacent to c1.

Output
  E  : a list of all edges in the graph of the CAD from vertices
       corresponding to cells in c1 to vertices corresponding to
       cells in c0.

======================================================================*/
#include "truthbytop.h"
#include "adj2D.h"

int bc(int a, int b)
{
  if (a < 0 || a >= b) {
    SWRITE("Out of bounds!!\n");
  }
  return a;
}

Word ADJ2DITOEL(Word L, Word c1, Word c0)
{
  Word *A, E,n,l,s,a,b,k1,k0,i,itop,ibot,S;

Step1: /* Initialize & Special Case. */
  E = NIL;
  n = LENGTH(LELTI(c1,CHILD));
  k1 = FIRST(LELTI(c1,INDX));
  k0 = FIRST(LELTI(c0,INDX));
  if (n == 1)
  {
    S = LELTI(c0,CHILD);
    E = COMP(LIST2(LIST2(k1,1),LIST2(k0,1)),E);
    for(S = RED(S), i = 3; S != NIL; S = RED2(S), i += 2)
      E = COMP(LIST2(LIST2(k1,1),LIST2(k0,i)),E);
    goto Return;
  }
  if (n == 0 || L == NIL)
    goto Return;

Step2: /* Store adjacency info. */
  A = GETARRAY(n+1);
  while (L != NIL) {
    ADV(L,&l,&L);
    FIRST2(l,&a,&b);
    A[bc(SECOND(a),n+1)] = SECOND(b); }

Step3: /* Put section adjacency info. into list. */
  for(i = 2; i <= n; i += 2)
    if (A[bc(i,n+1)] != AD2D_Infy && A[bc(i,n+1)] != AD2D_N_In)
      E = COMP(LIST2(LIST2(k1,i),LIST2(k0,A[bc(i,n+1)])),E);

Step4: /* Put sector adjacency info. into list. */
  for(i = n; i > 1 && A[bc(i-1,n+1)] == AD2D_Infy; i-=2);
  for(itop = LENGTH(LELTI(c0,CHILD)); i > 1 && A[bc(i-1,n+1)] != AD2D_N_In; i-=2)
    for(ibot = A[bc(i-1,n+1)]; itop > ibot; itop -= 2)
      E = COMP(LIST2(LIST2(k1,i),LIST2(k0,itop)),E);
  for(; itop > 0; itop -= 2)
      E = COMP(LIST2(LIST2(k1,i),LIST2(k0,itop)),E);

Step5: /* Clean-up. */
  FREEARRAY(A);

Return: /* Prepare to return. */
  return E;
}
