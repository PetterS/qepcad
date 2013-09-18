/*===========================================================================
			       C <- ISUM(A,B)

Integer sum.  

Inputs
  A,B : in Z.

Output
  C   : A + B.
===========================================================================*/
#include "saclib.h"

Word ISUM(A,B)
       Word A,B;
{
       Word Ap,Bp,C,Cb,Cp,Cpp,Cs,a,b,c,cp,s,t,u;

Step1: /* A or B zero. */
       if (A == 0) {
	  C = B;
	  goto Return; }
       if (B == 0) {
	  C = A;
	  goto Return; }

Step2: /* A and B single-precision. */
       if (A < BETA && B < BETA) {
	  c = A + B;
	  if (c >= BETA)
	     C = LIST2(c - BETA,1);
	  else
	     if (c <= -BETA)
		C = LIST2(c + BETA,-1);
	     else
		C = c;
	  goto Return; }

Step3: /* Determine signs of inputs. */
       s = ISIGNF(A);
       t = ISIGNF(B);

Step4: /* A or B single-precision. */
       if (A < BETA)
	  Ap = LIST1(A);
       else
	  Ap = A;
       if (B < BETA)
	  Bp = LIST1(B);
       else
	  Bp = B;

Step5: /* Initialize and branch on signs. */
       if (AVAIL == NIL)
	  GC();
       C = AVAIL;
       Cpp = C;       
       if (s != t)
	  goto Step8;
       else
	  if (s < 0)
	     goto Step7;

Step6: /* A and B both positive, add with carry. */
       cp = 0;
       do {
	  Cp = Cpp;
	  if (Ap != NIL) {
	     a = FIRST(Ap);
	     Ap = RED(Ap); }
	  else
	     a = 0;
	  if (Bp != NIL) {
	     b = FIRST(Bp);
	     Bp = RED(Bp); }
	  else
	     b = 0;
	  c = a + b;
	  c = c + cp;
	  if (c >= BETA) {
	     c = c - BETA;
	     cp = 1; }
	  else
	     cp = 0;
	  SFIRST(Cp,c);
	  Cpp = RED(Cp); 
	  if (Cpp == NIL) {
	     AVAIL = NIL;
	     GC();
	     Cpp = AVAIL; 
	     SRED(Cp,Cpp); } }
       while (cp != 0 || (Ap != NIL && Bp != NIL));
       if (Ap == NIL)
	  Ap = Bp;
       AVAIL = Cpp;
       SRED(Cp,Ap);
       goto Return;

Step7: /* A and B both negative, add with carry. */
       cp = 0;
       do {
	  Cp = Cpp;
	  if (Ap != NIL) {
	     a = FIRST(Ap);
	     Ap = RED(Ap); }
	  else
	     a = 0;
	  if (Bp != NIL) {
	     b = FIRST(Bp);
	     Bp = RED(Bp); }
	  else
	     b = 0;
	  c = a + b;
	  c = c + cp;
	  if (c <= -BETA) {
	     c = c + BETA;
	     cp = -1; }
	  else
	     cp = 0;
	  SFIRST(Cp,c);
	  Cpp = RED(Cp); 
	  if (Cpp == NIL) {
	     AVAIL = NIL;
	     GC();
	     Cpp = AVAIL; 
	     SRED(Cp,Cpp); } }
       while (cp != 0 || (Ap != NIL && Bp != NIL));
       if (Ap == NIL)
	  Ap = Bp;
       AVAIL = Cpp;
       SRED(Cp,Ap);
       goto Return;

Step8: /* Opposite signs, add without carry. */
       u = 0;
       do {
	  Cp = Cpp;
	  a = FIRST(Ap);
	  Ap = RED(Ap); 
	  b = FIRST(Bp);
	  Bp = RED(Bp); 
	  c = a + b;
	  if (c != 0)
	     u = c;
	  SFIRST(Cp,c);
	  Cpp = RED(Cp); 
	  if (Cpp == NIL) {
	     AVAIL = NIL;
	     GC();
	     Cpp = AVAIL; 
	     SRED(Cp,Cpp); } }
       while (Ap != NIL && Bp != NIL);
       if (Ap == NIL) {
	  Ap = Bp;
	  s = t; }

Step9: /* Sum zero. */
       if (u == 0 && Ap == NIL) {
	  AVAIL = C;
	  C = 0;
	  goto Return; }

Step10: /* Continue with longer input. */
       if (u == 0 || (Ap != NIL && s != SIGN(u))) {
	  do {
	     Cp = Cpp;
	     a = FIRST(Ap);
	     Ap = RED(Ap); 
	     SFIRST(Cp,a);
	     Cpp = RED(Cp); 
	     if (Cpp == NIL) {
		AVAIL = NIL;
		GC();
		Cpp = AVAIL; 
		SRED(Cp,Cpp); } }
	  while (a == 0);       
	  u = a; }
       AVAIL = Cpp;
       SRED(Cp,NIL);

Step11: /* Normalize the sum. */
       Cb = C;
       cp = 0;
       if (u < 0)
	  do {
	     c = FIRST(Cb);
	     c = c + cp;
	     if (c > 0) {
		c = c - BETA;
		cp = 1; }
	     else
		cp = 0;
	     if (c != 0)
		Cs = Cb;
	     SFIRST(Cb,c);
	     Cb = RED(Cb); }
	  while (Cb != NIL);
       else
	  do {
	     c = FIRST(Cb);
	     c = c + cp;
	     if (c < 0) {
		c = c + BETA;
		cp = -1; }
	     else
		cp = 0;
	     if (c != 0)
		Cs = Cb;
	     SFIRST(Cb,c);
	     Cb = RED(Cb); }
	  while (Cb != NIL);

Step12: /* Concatenate or delete leading zeros. */
       if (Ap == NIL)
	  SRED(Cs,NIL);
       else
	  SRED(Cp,Ap);
       if (RED(C) == NIL)
	  C = FIRST(C);

Return: /* Prepare for return. */
       return(C);
}
