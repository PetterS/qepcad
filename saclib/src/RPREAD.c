/*======================================================================
                      RPREAD(; r,A)

Rational polynomial read.

Outputs
  A  : in Q[X1,...Xr]. A is read from the input stream.
       Any preceding blanks and blanks separating coefficients, 
       variables, exponents and the symbols *,+,- and ^ are skipped.
  r  : a BETA-digit, r >= 0, the number of variables.
======================================================================*/
#include "saclib.h"

void RPREAD(r_,A_)
     Word *r_,*A_;
{
       Word A,C,Cp,a,e,r,rp,v;
       /* hide A,C,Cpa,e,r,rp,v; */

     Step1: /* r = 0. */
       C = CREADB();
       if (C != '(') {
	 BKSP();
	 A = RNREAD();
	 r = 0;
	 goto Return;
       }

     Step2: /* Initialize. */
       A = NIL;
       rp = 0;
       
     Step3: /* Read first coefficient. */
       C = LKAHEAD();
       if (LETTER(C) || DIGIT(C) || (C == '(')) {
	 if (LETTER(C))
	   a = RNINT(1);
	 else 
	   if (DIGIT(C))
	     a = RNREAD();
	   else
	     if (C == '(')
	       RPREAD(&rp,&a);
	 goto Step5;
       }

     Step4: /* Read coefficient. */
       C = CREADB();
       if (C != '+' && C != '-')
         goto Step7;
       Cp = LKAHEAD();
       if (LETTER(Cp) || DIGIT(Cp)) {
	 if (LETTER(Cp))
	   a = RNINT(1);
	 else
	   a = RNREAD();
	 if (C == '-')
	   a = RNNEG(a);
       }
       if (Cp == '(') {
	 RPREAD(&rp,&a);
	 if (C == '-')
	   a = RPNEG(rp,a);
       }
     
     Step5: /* Read variable and exponent. */
       C = LKAHEAD();
       if (LETTER(C)) {
	 v = VREAD();
	 C = CREADB();
	 if (C != '^') {
	   e = 1;
	   BKSP();
	 }
	 else {
	   C = LKAHEAD();
	   if (DIGIT(C))
	     e = AREAD();
	   else
	     goto Step7;
	 }
       }
       else 
	 e = 0;

     Step6: /* Check for end. */
       A = COMP2(a,e,A);
       C = CREADB();
       if (C != ')') {
	 BKSP();
	 goto Step4;
       }
       else
         r = rp + 1;
       A = INV(A);
       goto Return;
       
     Step7: /* Error. */
       FAIL("RPREAD","Unexpected character",C);

     Return: /* Prepare for return. */
       *r_ = r;
       *A_ = A;
       return;
}

