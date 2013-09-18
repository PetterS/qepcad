/*======================================================================
                      C <- DMAFUPNR(p,A,B)

Dense modular algebraic number field univariate polynomial 
natural remainder.

Input
  p : a BETA-digit, p a prime.
  M : in Z/(p)[x].
  A,B : in (Z/(p)[x])/(M)[y], A,B non-zero, deg(A) >= deg(B).

Output
  C : in (Z/(p)[x])/(M)[y].  If ldcf(B) is invertible in Z/(p)[x]/(M)
      then C is the natrual remainder of A and B.  Otherwise, C = NIL.

Side effects
  The list for A is modified.
======================================================================*/
#include "qepcad.h"

Word DMAFUPNR(Word p, Word M, Word A, Word B)
{
       Word Ap,App,As,Bp,Bpp,Bs,C,a,b,bp,c,k,m,n;

Step1: /* deg(B) = 0. */
       n = PDEG(B);
       if (n == 0) {
	 if (MAFINV(p,M,PLDCF(B)) != NIL)
	   C = 0;
	 else
	   C = NIL;
         goto Return;
       }

Step2: /* Invert leading coefficient of B. */
       Bp = RED(B);
       ADV(Bp,&b,&Bs);
       bp = MAFINV(p,M,b);
       if (bp == NIL) {
	 C = NIL;
	 goto Return;
       }

Step3: /* Division loop. */
       As = A;
       do {
         ADV(As,&k,&Ap);
         m = -1;
         ADV(Ap,&a,&App);
         c = MAFPROD(p,M,a,bp);
         Bpp = Bs;
         do {
           ADV(Bpp,&b,&Bpp);
           b = MAFPROD(p,M,b,c);
           a = FIRST(App);
           a = MAFDIF(p,a,b);
           k = k - 1;
           if (m < 0 && a != 0) {
             m = k;
             As = Ap;
	   }
           SFIRST(App,a);
           Ap = App;
           App = RED(Ap);
	 } while (Bpp != NIL);
         while (m < 0 && App != NIL) {
           k = k - 1;
           if (FIRST(App) != 0) {
             m = k;
             As = Ap;
	   }
           Ap = App;
           App = RED(Ap);
	 }
         if (m >= 0)
           SFIRST(As,m);
       } while (m >= n);
       if (m >= 0)
         C = As;
       else
         C = 0;

Return: /* Prepare for return. */
       return(C);
}
