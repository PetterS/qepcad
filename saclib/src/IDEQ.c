/*===========================================================================
			       C <- IDEQ(A,b)

Integer-digit exact quotient.   

Inputs
  A : in Z.  
  b : a non-zero BETA-digit which is a divisor of A.

Output
  C : the quotient A/b.
===========================================================================*/
#include "saclib.h"
#define IDEQ_SIZE 100

Word IDEQ(A,b)
       Word A,b;
{
       Word *Ah,Ap[IDEQ_SIZE],C;
       Word a,ap,bp,bpp,c,cp,g,i,l,m,N,n,s,s1,s2,o,r;

Step1: /* A single-precision. */
       if (A < BETA)  { 
	  C = A / b;
          goto Return; }

Step2: /* Copy |A| into arrays, determine lengths and signs. */
       IFLTA(A,Ap,IDEQ_SIZE,&Ah,&n,&s1,&o);
       s2 = signm(b);
       if (s2 > 0)
	  s = s1;
       else
	  s = -s1;
       bp = absm(b);

Step3: /* Divide b by a power of 2. */
       l = 0;
       while ((bp & 01) == 0) {
	  l = l + 1;
	  bp = bp >> 1; }

Step4: /* Divide B by the same power of t. */
       if (l == 0) goto Step5;
       r = 00;
       m = ZETA - l;
       N = (01 << l) - 1;
       for (i = n - 1; i >= 0; i--) {
	  a = Ah[i];
	  ap = (a >> l) | r; 
	  r = (a & N) << m;
	  Ah[i] = ap; }

Step5: /* Compute modular inverse */
       bpp = MDINVB(bp);

Step6: /* Divide by Jebelean's method. */
       g = 0;
       for (i = 0; i < n - 1; i++) { 
	  if (Ah[i] == 0) continue;
	  DPR(Ah[i],bpp,&cp,&Ah[i]);
	  DPR(Ah[i],bp,&c,&cp);
	  a = Ah[i + 1];
	  a = a - g - c;
	  if (a < 0) {
	     a = a + BETA;
	     g = 1; }
	  else
	     g = 0;
	  Ah[i + 1] = a; }
       DPR(Ah[i],bpp,&c,&Ah[i]);
	  
Step7: /* Copy result to a list. */
       C = IFATL(Ah,n,s);

Step8: /* Free dynamic array */
       if (n > IDEQ_SIZE) 
	  FREEARRAY(Ah);

Return: /* Prepare for return */
	return(C);
}
