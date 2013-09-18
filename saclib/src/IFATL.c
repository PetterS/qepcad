/*===========================================================================
		       B <- IFATL(A,m,s)

Integer from array to list.

Inputs
  m  : a positive beta integer.
  A  : An array of length m containing an integer A'.
  s  : +1 or -1.

Output
  B : The integer s * A' in list representation.
===========================================================================*/
#include "saclib.h"

Word IFATL(A,m,s)
       Word *A,m,s;
{
       Word k,n;
       Word B,Bp;

Step1: /* Skip leading zeros. Determine length of A'*/
       for (n = m - 1; n >= 0; n--)
	  if (A[n] != 0)
	     goto Step3;

Step2: /* A' = 0. */
       B = 0;
       goto Return;
       
Step3: /* A' BETA-digit. */
       if (n == 0) {
	  if (s < 0)
	     B = -A[0];
	  else
	     B = A[0];
	  goto Return; }

Step4: /* Copy digits to initial segment of AVAIL. */
       if (AVAIL == NIL)
	  GC();
       B = AVAIL;
       if (s < 0) {
	  for (k = 0; k <= n; k++) {
	     if (AVAIL == NIL) {
	        GC();
	        SRED(Bp,AVAIL); }
	     SFIRST(AVAIL,-A[k]);
	     Bp = AVAIL;
	     AVAIL = RED(AVAIL); } }
       else {
	  for (k = 0; k <= n; k++) {
	     if (AVAIL == NIL) {
                GC();
	        SRED(Bp,AVAIL); }
             SFIRST(AVAIL,A[k]);
	     Bp = AVAIL;
             AVAIL = RED(AVAIL); } }
       SRED(Bp,NIL);

Return: /* Prepare for return. */
       return(B);
}
