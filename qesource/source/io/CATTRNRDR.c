/*======================================================================
                      CATTRNRDR(; V,t)

Cell attribute name read, robust.

\Output  
  \parm{V} is an attribute, read from the input stream.
  \parm{t} is 1 if successful, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void CATTRNRDR(Word *V_, Word *t_)
{
       Word C,V,W,t,i;
       /* hide C,V,t,i; */

Step1: /* Read in a word. */
       t = 1;
       W = GETWORD();
    
Step2: /* Get the internal representation. */
       if      (EQUAL(W,LFS("dimension"))) V = CADIMENSION;
       else if (EQUAL(W,LFS("degree")))    V = CADEGREE;
       else if (EQUAL(W,LFS("level")))     V = CALEVEL;
       else if (EQUAL(W,LFS("lcindex")))   V = CALCINDEX;
       else if (EQUAL(W,LFS("parity")))    V = CAPARITY;
       else if (EQUAL(W,LFS("index")))     
          {
          C = CREADB(); 
          if (C != '(') 
            {SWRITE("Error CATTRNRDR: '(' expected!\n"); goto Step3;}
          i = AREAD();
          C = CREADB();
          if (C != ')') 
            {SWRITE("Error CATTRNRDR: ')' expected!\n"); goto Step3;}
          V = CAINDEX0 - i;
          }
       else {SWRITE("Error CATTRNRDR: No such attribute!\n"); goto Step3;}
       goto Return;

Step3: /* Error exit. */
       DIELOC(); t = 0;

Return: /* Prepare for return. */
       *V_ = V;
       *t_ = t;
       return;
}
