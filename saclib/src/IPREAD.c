/*======================================================================
                      IPREAD(; r,A)

Integral polynomial read.

Outputs
  A  : in Z[X1,...Xr]. A is read from the input         
       stream. Blanks are skipped.
  r  : a BETA-digit, r >= 0, the number of variables.
======================================================================*/
#include "saclib.h"

void IPREAD(r_,A_)
     Word *r_,*A_;
{
       Word A,C,Cp,a,e,r,rp,v;
       /* hide A,C,Cpa,e,r,rp,v; */

     Step1: /* r = 0. */
       C = CREADB();
       if (C != '(') {
	 BKSP();
	 A = IREAD();
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
	   a = 1;
	 else 
	   if (DIGIT(C))
	     a = IREAD();
	   else
	     if (C == '(')
	       IPREAD(&rp,&a);
	 goto Step5;
       }

     Step4: /* Read coefficient. */
       C = CREADB();
       if (C != '+' && C != '-')
         goto Step7;
       Cp = LKAHEAD();
       if (LETTER(Cp) || DIGIT(Cp)) {
	 if (LETTER(Cp))
	   a = 1;
	 else
	   a = IREAD();
	 if (C == '-')
	   a = INEG(a);
       }
       if (Cp == '(') {
	 IPREAD(&rp,&a);
	 if (C == '-')
	   a = IPNEG(rp,a);
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
       FAIL("IPREAD","Unexpected character",C);

     Return: /* Prepare for return. */
       *r_ = r;
       *A_ = A;
       return;
}
