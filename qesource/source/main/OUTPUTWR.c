/*======================================================================
                      OUTPUTWR(t,F_e,F_n,F_s,V)

Write out the output formula.
 
\Input
  \parm{t}  is either \c{EQU} or \c{INEQU}.
  \parm{Fe} is a quantifier-free formula equivalent to the input formula
            if \v{t} is \c{EQU}, otherwise \v{Fe} is undefined.
  \parm{Fn} is a quantifier-free formula necssary for the input formula
            if \v{t} is \c{INEQU}, otherwise \v{Fn} is undefined.
  \parm{Fs} is a quantifier-free formula sufficient for the input formula
            if \v{t} is \c{INEQU}, otherwise \v{Fs} is undefined.
======================================================================*/
#include "qepcad.h"

void OUTPUTWR(Word t,Word F_e,Word F_n,Word F_s,Word V)
{

Step1: /* t = EQU. */
       SWRITE("\n=======================================================\n");
       if (t == INEQU) goto Step2;
       SWRITE("\n\nAn equivalent quantifier-free formula:\n\n");
       if (PCSIMPLIFY == 'b') 
         QFFWR(V,F_e); 
       else
         DNFWR(V,F_e);  
       SWRITE("\n\nIn other words,\n\n");
       if (PCSIMPLIFY == 'b')
         QFFLPWR(LFS("P"),V,F_e);
       else
         DNFLPWR(LFS("P"),V,F_e);
       SWRITE("\n");
       goto Return;

Step2: /* t = INEQU. */
       SWRITE("\n\nA necessary condition: \n\n");
       if (PCSIMPLIFY == 'b') 
         QFFWR(V,F_n); 
       else
         DNFWR(V,F_n); 
       SWRITE("\n\nIn other words,\n\n");
       if (PCSIMPLIFY == 'b')
         QFFLPWR(LFS("P"),V,F_n);
       else
         DNFLPWR(LFS("P"),V,F_n);

       SWRITE("\n\nA sufficient condition:\n\n");
       if (PCSIMPLIFY == 'b') 
         QFFWR(V,F_s); 
       else
         DNFWR(V,F_s); 
       SWRITE("\n\nIn other words,\n\n");
       if (PCSIMPLIFY == 'b')
         QFFLPWR(LFS("P"),V,F_s);
       else
         DNFLPWR(LFS("P"),V,F_s);
       goto Return;

Return: /* Prepare for return. */
       return;
}

