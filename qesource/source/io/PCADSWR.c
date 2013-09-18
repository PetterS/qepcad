/*======================================================================
                      PCADSWR(c)

Partial CAD signature write.

\Input
  \parm{c} is a cell whose subtree (with signature) will be written out to
           the output stream.
======================================================================*/
#include "qepcad.h"

void PCADSWR(Word c)
{
       Word M,cb,cp,p,s,S;
       /* hide p; */

Step1: /* common. */
       LWRITE(LELTI(c,INDX));
       if (LELTI(c,LEVEL) > 0)
         {
         s = LELTI(c,SAMPLE);
	 
         if (ISPRIMIT(s)) CWRITE('p'); else CWRITE('e');
	 if (s == NIL) CWRITE('?'); else
         GWRITE(CELLDEG(c));
         S = FIRST(LELTI(c,SIGNPF));
         if (S != 0)
           SIGNLWR(S);
         }
       cb = LELTI(c,CHILD);

Step2: /* c is a leaf. */
       if (cb == NIL)
         {
         SWRITE(" ");
         TRUTHWR(LELTI(c,TRUTH));
         SWRITE("\n");
         goto Return;
         }

Step3: /* c is not a leaf. */
       p = OPOS;
       ADV(cb,&cp,&cb);
       SWRITE("---");
       PCADSWR(cp);
       while (cb != NIL)
         {
         TAB(p);
         ADV(cb,&cp,&cb);
         SWRITE("---");
         PCADSWR(cp);
         }

Return: /* Prepare for return. */
       return;
}

