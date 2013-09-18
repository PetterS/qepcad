/*======================================================================
                      PCADWR(c)

Partial CAD write.

\Input
  \parm{c} is a cell whose subtree will be written out to
           the output stream.
======================================================================*/
#include "qepcad.h"

void PCADWR(Word c)
{
       Word M,cb,cp,p,s;
       /* hide p; */

Step1: /* common. */
       LWRITE(LELTI(c,INDX));
       if (LELTI(c,LEVEL) > 0)
         {
         s = LELTI(c,SAMPLE);
         if (ISPRIMIT(s)) CWRITE('p'); else CWRITE('e');
         GWRITE(CELLDEG(c));
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
       PCADWR(cp);
       while (cb != NIL)
         {
         TAB(p);
         ADV(cb,&cp,&cb);
         SWRITE("---");
         PCADWR(cp);
         }

Return: /* Prepare for return. */
       return;
}

