/*========================================================================
                           AISUM(A,B,C)

Array integer sum.

Inputs
   A, B: array integers.
   C : an array which must be at least as long as the maximum
       of the lengths of A and B  plus 3.

Effect
   The sum of A and B is placed in C.
========================================================================*/
#include "saclib.h"

void AISUM(A,B,C)
	BDigit *A,*B,*C;
{
	BDigit *Ap,*As,*Bp,*Bs,*Cs;
	BDigit c,d,e,i,k,m,n,s;

Step1: /* A or B zero. */
	if (A[0] == 0) {
	   AICOPY(B,C);
	   goto Return; }
	if (B[0] == 0) {
	   AICOPY(A,C);
	   goto Return; }

Step2: /* Make the first addend be the longer. */
	if (A[1] >= B[1]) {
	   Ap = A;
	   Bp = B; }
	else {
	   Ap = B;
	   Bp = A; }
	m = Ap[1];
	n = Bp[1];
	As = Ap + 2;
        Bs = Bp + 2;
        Cs = C + 2;

Step3: /* The inputs have the same sign. */
	if (A[0] != B[0])
	   goto Step4;
	c = 0;
	for (i = 0; i < n; i++) {
	   d = As[i] + Bs[i] + c;
	   if (d >= BETA) {
	      Cs[i] = d - BETA;
	      c = 1; }
	   else {
	      Cs[i] = d;
	      c = 0; } }
	for (i = n; i < m; i++) {
	   d = As[i] + c;
	   if (d == BETA) {
	      Cs[i] = 0;
	      c = 1; }
	   else {
	      Cs[i] = d;
	      c = 0; } }
	if (c != 0) {
	   Cs[m] = c;
	   m = m + 1; }
	C[1] = m;
	C[0] = A[0];
	goto Return;
	
Step4: /* The inputs have opposite signs and different lengths. */
	if (m == n)
	   goto Step5;
	s = Ap[0];
	c = 0;
	for (i = 0; i < n; i++) {
	   d = As[i] - Bs[i] + c;
	   if (d < 0) {
	      Cs[i] = d + BETA;
	      c = -1; }
	   else {
	      Cs[i] = d;
	      c = 0; } }
	for (i = n; i < m; i++) {
	   d = As[i] + c;
	   if (d < 0) {
	      Cs[i] = d + BETA;
	      c = -1; }
	   else {
	      Cs[i] = d;
	      c = 0; } }
	i = i - 1;
	while (Cs[i] == 0)
	   i = i - 1;
	C[1] = i + 1;
	C[0] = s;
	goto Return;

Step5: /* A and B have opposite signs and equal lengths. */
	k = m - 1;
	while (k >= 0 && As[k] == Bs[k])
	   k = k - 1;
	if (k == -1) {
	   C[0] = 0;
	   C[1] = 0;
	   C[2] = 0;
	   goto Return; }
	e = As[k] - Bs[k];
	if (e > 0)
	   C[0] = A[0];
	else
	   C[0] = B[0];
	c = 0;
	if (e > 0) {
	   for (i = 0; i <= k; i++) {
	      d = As[i] - Bs[i] + c;
	      if (d < 0) {
	         Cs[i] = d + BETA;
	         c = -1; }
	      else {
	         Cs[i] = d;
	         c = 0; } } }
	else {
	   for (i = 0; i <= k; i++) {
              d = Bs[i] - As[i] + c;
              if (d < 0) {
                 Cs[i] = d + BETA;
                 c = -1; }
              else {
                 Cs[i] = d;
                 c = 0; } } }
	while (Cs[k] == 0)
	   k = k - 1;
	C[1] = k + 1;

Return: /* Return. */
	return;
}
