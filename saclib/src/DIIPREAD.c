/*======================================================================
                      A <- DIIPREAD(V)

Distributive integral polynomial read.

Inputs
  V  : a variable list.

Outputs
  A  : in Z[X1,...Xr], distributive representation,
       where r=length(V), r >= 0.
       Any preceding blanks and blanks separating coefficients, 
       variables, exponents and the symbols *,+,- and ^ are skipped.
======================================================================*/
#include "saclib.h"

Word DIIPREAD(V)
       Word V;
{
       Word A,C,Cp,E,a,e,i,j,k,r,s,v;
       /* hide C,e,i,j,k,r,s; */

Step1: /* Rl=0. */
       if (V == NIL) {
         A = IREAD();
         goto Return;
       }

Step2: /* Initialize. */
       C = CREADB();
       if (C != '(')
         goto Step6;
       A = NIL;
       r = LENGTH(V);


Step3: /* Read first coefficient */
       C = LKAHEAD();
       if (LETTER(C) || DIGIT(C)) {
	 if (LETTER(C))
	   a = 1;
	 else
	   a = IREAD();
	 A = COMP(a,A);
	 goto Step5;
       }
	 
Step4: /* Read coefficient. */
       C = CREADB();
       if (C != '+' && C != '-')
	 goto Step7;
       Cp = LKAHEAD();
       if (DIGIT(Cp))
	 a = IREAD();
       else
	 a = 1;
       if (C == '-')
	 a = INEG(a);
       A = COMP(a,A);

Step5: /* Read monic monomial. */
       E = NIL;
       i = 1;
       do {
	 C = LKAHEAD();
	 if (!LETTER(C))
	   goto Step6;
         v = VREAD();
         j = VLSRCH(v,V);
         if (j < i)
           goto Step7;
         for (k = i; k <= j - 1; k++)
           E = COMP(0,E);
         C = LKAHEAD();
         if (C == '^') {
           C = CREAD();
           e = AREAD();
	 }
	 else
	   e = 1;
	 E = COMP(e,E);
         i = j + 1;
       } while (!(i > r));

Step6: /* Complete exponent vector. */
       for (k = i; k <= r; k++)
         E = COMP(0,E);
       A = COMP(E,A);
       C = CREADB();
       if (C == '+' || C == '-') {
         BKSP();
         goto Step4;
       }
       if (C == ')') {
         A = INV(A);
         goto Return;
       }

Step7: /* Error. */
       FAIL("DIIPREAD","Unexpected character",C);

Return: /* Prepare for return. */
       return(A);
}
