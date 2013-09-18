/*======================================================================
                      mp <- GMSDS(A,m,C)

General merge sort with duplicate supression.

Inputs
A : An array of m words.
m : A positive BETA-digit.
C : A pointer to a function of two arguments returning type Word.
Outputs
mp: the number of distinct array elements.
Side Effects
    Rearranges the values in A so that the first mp entries are distinct
    and in sorted order.  The set of elements in A is the same as on 
    input.
  ======================================================================*/
#include "mysort.h"
static Word G23VSDS(Word *v,Word m,Word (*C)(Word,Word));

Word GMSDS(Word *A, Word m, Word (*C)(Word,Word))       
{
       Word *T,*T1,*T2,*A1,*A2,m1,m1p,m2,m2p,mp,k,l;

Step1: /* Split. */
       m1 = m >> 1;
       m2 = m1 + ODD(m);
       A1 = A;
       A2 = A + m1;

Step2: /* Sort sublists. */
       if (m1 < 4) { 
	 m1p = G23VSDS(A1,m1,C); }
       else m1p = GMSDS(A1,m1,C);
       if (m2 < 4) {
	 m2p = G23VSDS(A2,m2,C); }
       else m2p = GMSDS(A2,m2,C);

Step3: /* Copy A1 into a temporary array. */
       T1 = GETARRAY(m1);
       for(k = 0; k < m1; k++) T1[k] = A1[k];
       A1 = T1;

Step4: /* Copy A2 into a temporary array. */
       T2 = GETARRAY(m2);
       for(k = 0; k < m2; k++) T2[k] = A2[k];
       A2 = T2;

Step5: /* Merge A1 and A2 until one or both is exhausted. */
       mp = m;
       for(k = 0; (m1p > 0) && (m2p > 0); k++) {
	 switch(C(A1[0],A2[0])) {
	 case (1) : A[k] = A2[0]; A2++; m2p--; break;
	 case (0) : A[k] = A1[0]; A1++; m1p--;
	            A[--mp] = A2[0];A2++; m2p--; break;
	 case (-1): A[k] = A1[0]; A1++; m1p--; break; } }

Step6: /* Complete merge. */
       while (m1p > 0) {
	 A[k++] = A1[0]; A1++; m1p--; }
       while (m2p > 0) {
	 A[k++] = A2[0]; A2++; m2p--; }

Step7: /* Write suppressed duplicates to end. */
       for(T = T1 + m1 -1; T >= A1; T--) {
	 A[--mp] = T[0]; }
       for(T = T2 + m2 -1; T >= A2; T--) {
	 A[--mp] = T[0]; }


Return: /* Prepare to return. */
       FREEARRAY(T1);
       FREEARRAY(T2);
       return (mp);
}

/* General 2 or 3 element vector sort with duplicate suppression. */
static Word G23VSDS(Word *v,Word m,Word (*C)(Word,Word))
{
      Word mp,temp;

Step1: /* A 3 element vector. */
      mp = m;
      if (mp == 3) {
	switch (C(v[1],v[2])) {
	case (0) : mp--; goto Step2;
	case (1) : temp = v[2]; v[2] = v[1]; v[1] = temp; break; }
	switch (C(v[0],v[1])) {
	case (0) : temp = v[2]; v[2] = v[1]; v[1] = temp; mp--; goto Return;
	case (1) : temp = v[0]; v[0] = v[1]; v[1] = temp;
	  if (mp == 3) {
	    switch(C(v[1],v[2])) {
	    case (0) : mp--; break;
	    case (1) : temp = v[2]; v[2] = v[1]; v[1] = temp; break; } }
	  goto Return; } }
	
Step2: /* A 2 element vector. */
      if (mp == 2) {
	switch(C(v[0],v[1])) {
	case (0) : mp--; break;
	case (1) : temp = v[1]; v[1] = v[0]; v[0] = temp; break; } }

Return: /* Return. */
      return (mp);
}
