/*======================================================================
                   H <- ESPORD()

Espresso Output read.

\Ouput
  H is a sum-of-product read from Espresso output.
======================================================================*/
#include "qepcad.h"

Word ESPORD()
{
       Word i,n,m,C,H,H1,H11;

Step1: /* Read in the number of variables. */
       do C = CREAD(); while (!DIGIT(C));
       BKSP(); n = GREAD() - 1;
       FILINE();
       FILINE();

Step2: /* Read in the rows. */
       H = NIL;
       for (;;)
         {
         C = CREAD(); BKSP(); if (C == '.')  break;
         H1 = NIL;
         for (i=1; i<=n; i++)
           {
           m = GREAD();
           switch(m)
             {
             case   1: H11 = GTOP;  break; 
             case  10: H11 = EQOP;  break; 
             case  11: H11 = GEOP;  break; 
             case 100: H11 = LTOP;  break; 
             case 101: H11 = NEOP;  break; 
             case 110: H11 = LEOP;  break;
             case 111: H11 = TAOP;  break; 
             default: FAIL("ESPORD","Illegal output from espresso.");
             }
           H1 = COMP(H11,H1);
           }
         FILINE();
         H1 = INV(H1);
         H = COMP(H1,H);         
         }
       H = INV(H);
       FILINE();

Return: /* Prepare for return. */
       return(H);
}




