/*======================================================================
                      A <- IREAD()

Integer read.

Inputs (from the input stream)
  An integer in external form.
  Let <digit sequence> designate any non-empty word over the alphabet
  {0,1,...,9}.
  Then the input is of the following form
  <digit sequence>
  or
  +<digit sequence>
  or
  -<digit sequence>
  Note that there is no blank between the optional sign and the
  digit sequence; also note that leading zeros are allowed.

Outputs
  A  : The internal representation of the input integer.
       A is either a BETA-digit or a list of more than one BETA-digit
       which are either all non-negative or all non-positive and such
       that the last list element (= the leading BETA-digit) is not 0.

Side effects
  An integer is read from the input stream.
  Any preceding blanks are skipped.
======================================================================*/

#include "saclib.h"

Word IREAD()
{
       Word A,B,C,b,bp,i,s;
       /* hide C,b,bp,i,s; */

Step1: /* Read sign. */
       s = 1;
       C = CREADB();
       if (C == '-')
         s = -1;
       if (C == '+' || C == '-')
         C = CREAD();
       if (DIGIT(C) == 0)
         goto Step6;

Step2: /* Skip leading zeros. */
       while (C == 0)
         C = CREAD();

Step3: /* Is A=0. */
       A = 0;
       if (DIGIT(C) == 0)
         {
         BKSP();
         goto Return;
         }

Step4: /* Compute THETA-digits. */
       B = NIL;
       b = 0;
       i = 0;
       do
         {
         b = 10 * b + C - '0';
         i = i + 1;
         if (i == ETA)
           {
           B = COMP(b,B);
           b = 0;
           i = 0;
           }
         C = CREAD();
         }
       while (!(DIGIT(C) == 0));

Step5: /* Convert to base BETA. */
       B = INV(B);
       while (B != NIL)
         {
         A = IDPR(A,THETA);
         ADV(B,&bp,&B);
         A = ISUM(A,bp);
         }
       if (A != 0)
         A = IDPR(A,EXPF(10,i));
       A = ISUM(A,b);
       if (s < 0)
         A = INEG(A);
       BKSP();
       goto Return;

Step6: /* Error. */
       FAIL("IREAD","Unexpected character",C);

Return: /* Prepare for return. */
       return(A);
}
