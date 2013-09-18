/*===========================================================================
			       C <- IDPR(A,b)

Integer-digit product.

Inputs
  A  : in Z.
  b  : BETA-digit.

Outputs
  C  : the product of A and b.
===========================================================================*/
#include "saclib.h"

Word IDPR(A,b)
       Word A,b;
{
       Word  Ap,C,Cp,Cpp,a,c,cp,e,f,s,t;

Step1: /* A or b zero. */
       if (A == 0 || b == 0) {
	  C = 0;
	  goto Return; }

Step2: /* A single-precision. */
       if (A < BETA) {
	  DPR(A,b,&e,&f);
	  if (e == 0)
	     C = f;
	  else
	     C = LIST2(f,e); 
	  goto Return; }

Step3: /* Determine signs of inputs. */
       s = ISIGNF(A);
       t = signm(b);

Step4: /* Initialize and branch on signs. */
       if (AVAIL == NIL) 
	  GC();
       C = AVAIL;
       Cpp = C;  
       Ap = A;
       if (s != t)
	  goto Step6;

Step5: /* Positive product. */
       cp = 0;
       do {
	  Cp = Cpp;
	  a = FIRST(Ap);
	  Ap = RED(Ap); 
	  DPR(a,b,&e,&f);
	  c = f + cp;
	  cp = e;
	  if (c >= BETA) {
	     c = c - BETA;
	     cp = cp + 1; }
	  SFIRST(Cp,c);
	  Cpp = RED(Cp); 
	  if (Cpp == NIL) {
	     AVAIL = NIL;
	     GC();
	     Cpp = AVAIL; 
	     SRED(Cp,Cpp); } }
       while (Ap != NIL);
       if (cp != 0) {
	  SFIRST(Cpp,cp);
	  AVAIL = RED(Cpp);
	  SRED(Cpp,NIL);}
       else {
	  AVAIL = Cpp;
	  SRED(Cp,NIL);}
       goto Return; 

Step6: /* Negative product. */
       cp = 0;
       do {
	  Cp = Cpp;
	  a = FIRST(Ap);
	  Ap = RED(Ap); 
	  DPR(a,b,&e,&f);
	  c = f + cp;
	  cp = e;
	  if (c <= -BETA) {
	     c = c + BETA;
	     cp = cp - 1; }
	  SFIRST(Cp,c);
	  Cpp = RED(Cp); 
	  if (Cpp == NIL) {
	     AVAIL = NIL;
	     GC();
	     Cpp = AVAIL; 
	     SRED(Cp,Cpp); } }
       while (Ap != NIL);
       if (cp != 0) {
	  SFIRST(Cpp,cp);
	  AVAIL = RED(Cpp);
	  SRED(Cpp,NIL);}
       else {
	  AVAIL = Cpp;
	  SRED(Cp,NIL);}

Return: /* Prepare for return. */
       return(C);
}
