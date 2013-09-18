/*======================================================================

Truth value closure (closure of open set) between stacks via adjacency
information.

This function is only assigning truth values based on information
between cells of different stacks.  It's assumed that everything that
can be assigned between cells of the same stack has already been done.

======================================================================*/
#include "truthbytop.h"
#include "adj2D.h"



static int indextrans(Word i, Word n)
{ /* i: a cell index from AD2D, n: the number of cells in the stack. */
  if (i == AD2D_N_In)
    return 0;
  if (i == AD2D_Infy)
    return n + 1;
  return i;
}


void TVCCOSBSVAI(Word C0, Word C1, Word L)
{
  Word S0,S1,S,n0,n1,i,j,a,b,s,Lp,*A0,*A1,*T0,*T1;

Step1: /* Initialize. */
  S0 = LELTI(C0,CHILD); n0 = LENGTH(S0);
  S1 = LELTI(C1,CHILD); n1 = LENGTH(S1);
  A0 = GETARRAY(n0+2); T0 = GETARRAY(n0+2);
  A1 = GETARRAY(n1+2); T1 = GETARRAY(n1+2);
  for(i = 0; i < n1+2; i++) {
    A1[i] = AD2D_ErrI;
    T1[i] = UNDET; }
  for(i = 0; i < n0+2; i++) {
    A0[i] = AD2D_ErrI;
    T0[i] = UNDET; }
  
Step3: /* Add truth information. */
  for(S = S0; S != NIL; S = RED(S)) {
    s = FIRST(S);
    T0[LAST(LELTI(s,INDX))] = LELTI(s,TRUTH); }
  for(S = S1; S != NIL; S = RED(S)) {
    s = FIRST(S);
    T1[LAST(LELTI(s,INDX))] = LELTI(s,TRUTH); }

Step2: /* Add adjacency information. */
  for(Lp = L; Lp != NIL; Lp = RED(Lp)) {
    FIRST2(FIRST(Lp),&a,&b);
    if (ODD(FIRST(a))) {
      A1[indextrans(SECOND(a),n0)] = SECOND(b);
      A0[indextrans(SECOND(b),n1)] = SECOND(a); }
    else {
      A0[indextrans(SECOND(a),n1)] = SECOND(b);
      A1[indextrans(SECOND(b),n0)] = SECOND(a); } }
  A1[indextrans(AD2D_Infy,n1)] = AD2D_Infy;
  A0[indextrans(AD2D_Infy,n0)] = AD2D_Infy;

Step4: /* Assign sector adjacencies. */
  if (A1[2] == AD2D_N_In)
    A1[1] = AD2D_N_In;
  else {
    A1[1] = 1;
    A0[1] = 1; }
  if (A1[n1-1] == AD2D_Infy)
    A1[n1] = AD2D_Infy;
  else {
    A1[n1] = n0;
    A0[n0] = n1; }
  for(i = 3; i < n1; i+= 2) {
    if (A1[i-1] == A1[i+1])
      A1[i] = A1[i-1];
    else {
      A1[i] = indextrans(A1[i+1],n0) - 1;
      A0[A1[i]] = i; } }

Step4b:/*  */
  for(i = n1; A1[i] == AD2D_Infy; i--);
  A0[n0] = i;
  for(i = n0 - 1; i > 0; i--)
    if (A0[i] == AD2D_ErrI) {
      j = indextrans(A0[i+1],n1);
      A0[i] = ODD(j) ? j : j - 1; }

Step5: /* Closure of true cells. */
  for(i = 1; i <= n1; i++)
    if (T1[i] == TRUE)
      for(j = indextrans(A1[i],n0); A0[j] == i; j--)
	T0[j] = TRUE;

Step6: /* Cells whose closure includes a false cell must be false. */
  for(i = 1; i < n0; i++)
    if (T0[i] == FALSE) {
      j = indextrans(A0[i],n1);
      do {
	T1[j] = FALSE;
	j--;
      } while(j > 0 && A1[j] == i); }
	

Step7: /* Change truth values in stacks accordingly. */
  for(S = S0; S != NIL; S = RED(S)) {
    s = FIRST(S);
    if (LELTI(s,TRUTH) == UNDET && T0[LAST(LELTI(s,INDX))] != UNDET) {
      SLELTI(s,TRUTH,T0[LAST(LELTI(s,INDX))]);
      SLELTI(s,HOWTV,TOPINF); } }

  for(S = S1; S != NIL; S = RED(S)) {
    s = FIRST(S);
    if (LELTI(s,TRUTH) == UNDET && T1[LAST(LELTI(s,INDX))] != UNDET) {
      SLELTI(s,TRUTH,T1[LAST(LELTI(s,INDX))]);
      SLELTI(s,HOWTV,TOPINF); } }

Return: /* Prepare to return. */
  FREEARRAY(A0);
  FREEARRAY(A1);
  FREEARRAY(T0);
  FREEARRAY(T1);
  return;
}
