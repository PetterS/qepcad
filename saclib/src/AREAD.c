/*======================================================================
                      A <- AREAD()

Atom read.

Outputs
  A  : an atom read from the input stream.
       Any preceding blanks are skipped.
======================================================================*/
#include "saclib.h"

Word AREAD()
{
       Word A,C,S;
       /* hide algorithm */

Step1: /* Skip blanks and read sign, if any. */
       S = 1;
       C = CREADB();
       if (C == '+')
         C = CREAD();
       else
         if (C == '-')
           {
           C = CREAD();
           S = -1;
           }
         else
           if (DIGIT(C) == 0)
             goto Step3;

Step2: /* Read digits and convert. */
       A = 0;
       do
         {
         if (A > BETA / 10)
           goto Step3;
         A = 10 * A + C - '0';
         if (A >= BETA)
           goto Step3;
         C = CREAD();
         }
       while (DIGIT(C) != 0);
       A = S * A;
       BKSP();
       goto Return;

Step3: /* Error. */
       FAIL("AREAD","Unexpected character",C);

Return: /* Prepare for return. */
       return(A);
}
