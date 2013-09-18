/*======================================================================
                      a <- GREAD()

C integer read.  

Outputs
  a : a C integer read from the input stream.  
      Any preceding white spaces are skipped.
======================================================================*/
#include "saclib.h"

Word GREAD()
{
       Word C,S,a;

Step1: /* Skip blanks and read sign, if any. */
       S = 1;
       C = CREADB();
       if (C == '+')
	  C = CREADB();
       else
	  if (C == '-') {
	     C = CREADB();
	     S = -1; }
       if (DIGIT(C) == 0)
	  goto Step3;

Step2: /* Read digits and convert. */
       a = 0;
       do {
	  a = 10 * a + C - '0';
	  C = CREAD(); }
       while (DIGIT(C) != 0);
       BKSP();
       a = S * a;
       goto Return;

Step3: /* Error. */
       FAIL("GREAD","Unexpected character",C);

Return: /* Prepare for return. */
       return(a);
}
