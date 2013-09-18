/*======================================================================
                      INPUTRD(; Fs,V)

Input formula read.

\Output
   \parm{F*} is a formula.
   \parm(V)  is a variable list.
======================================================================*/
#include "qepcad.h"

void INPUTRD(Word *Fs_,Word *V_)
{
       Word C,Fs,V,f,r,t;
       /* hide C,r,t; */

Step1: /* Read in a description. */
       do
         {
         PROMPT(); SWRITE("Enter an informal description ");
         SWRITE(" between '[' and ']':\n"); 
         C = CREADB();
         if (C != '[')
           {
           SWRITE("Error INPUTRD: '[' was expected.\n");
           FILINE();
           t = 0;
           }
         else
           t = 1;
         }
       while (!(t == 1));
       BKSP();  GVMCOMM = COMMNT();

Step2: /* Read a variable list. */
       do
         {
         PROMPT(); SWRITE("Enter a variable list:\n"); FILINE();
         VLREADR(&V,&t);
         if (t == 1 && ISNIL(V))
           {
           SWRITE("Error INPUTRD: There should be at least one variable.\n");
           t = 0;
           }
         }
       while (!(t == 1));
       r = LENGTH(V);

Step3: /* Read in the number of free variables. */
       do
         {
         PROMPT(); SWRITE("Enter the number of free variables:\n"); FILINE();
         GREADR(&f,&t);
         if (t == 1 && f < 0)
           {
           SWRITE("Error INPUTRD: the number of free variables must be non-negative.\n");
           t = 0;
           }
         if (t == 1 && f > r)
           {
           SWRITE("Error INPUTRD: the number of free variables must be <= ");
           GWRITE(r); SWRITE(".\n");
           t = 0;
           }
         }
       while (!(t == 1));

Step4: /* Read in a formula. */
       do
         {
         PROMPT(); SWRITE("Enter a prenex formula:\n"); FILINE();
         FREADR(V,f,&Fs,&t);
         }
       while (!(t == 1));
       SWRITE("\n\n=======================================================\n");

Return: /* Prepare for return. */
       *Fs_ = Fs;
       *V_ = V;
       return;
}




