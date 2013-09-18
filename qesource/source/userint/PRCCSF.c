/*======================================================================
                      PRCCSF()

Process Cell Choice Strategy command (for cell of level < f).
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRCCSF()
{
       Word C,S,S1,W;
       /* hide C,S1; */

Step0: /* If fast-cell-choice is used, we cannot honor the strategy! */
       if (PCCHFLAG)
       {
	 SWRITE("The \"fast-cell-choice\" strategy is now switched off!\n");
	 PCCHFLAG = 0;
       }

Step1: /* Read in the strategy. */
       S = NIL;
       C = CREADB();
       if (C != '(') { SWRITE("Error PRCCSF: '(' was expected.\n"); goto Step3; }
       do
         {
         W = GETWORD();
         if (EQUAL(W,LFS("TC"))) S1 = TCORD;
         else if (EQUAL(W,LFS("NC"))) S1 = NCORD;
         else if (EQUAL(W,LFS("LD"))) S1 = LDORD;
         else if (EQUAL(W,LFS("GD"))) S1 = GDORD;
         else if (EQUAL(W,LFS("SR"))) S1 = SRORD;
         else if (EQUAL(W,LFS("SN"))) S1 = SNORD;
         else if (EQUAL(W,LFS("HL"))) S1 = HLORD;
         else if (EQUAL(W,LFS("LL"))) S1 = LLORD;
         else if (EQUAL(W,LFS("GI"))) S1 = GIORD;
         else if (EQUAL(W,LFS("LI"))) S1 = LIORD;
         else { SWRITE("Error PRCCSF: A partial ordering was expected.\n"); goto Step3; }
         S = COMP(S1,S);
         C = CREADB();
         if (C != ',' && C != ')')
           { SWRITE("Error PRCCSF: ',' or ')' was expected.\n"); goto Step3; }
         }
       while (!(C == ')'));
       S = INV(S);

Step2: /* Set. */
       PCCCSF = S; goto Return;

Step3: /* Error exit. */
       DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
