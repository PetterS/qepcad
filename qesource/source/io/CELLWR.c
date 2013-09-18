/*======================================================================
                      CELLWR(c)

Cell Write.

Write out the information about the cell c.
======================================================================*/
#include "qepcad.h"

void QepcadCls::CELLWR(Word c)
{
       Word S,S1,k,t,i,D,M;
       /* hide t; */

Step1: /* Heading. */
       k = LELTI(c,LEVEL);
       SWRITE("---------- Information about the cell "); LWRITE(LELTI(c,INDX));
       SWRITE(" ----------\n\n");

Step2: /* Level. */
       SWRITE("Level                       : ");
       GWRITE(LELTI(c,LEVEL)); SWRITE("\n");

Step3: /* Dimension. */
       if (k == 0) goto Step4;
       SWRITE("Dimension                   : ");
       GWRITE(CELLDIM(c)); SWRITE("\n");

Step4: /* Number of children. */
       SWRITE("Number of children          : ");
       GWRITE(LENGTH(LELTI(c,CHILD))); SWRITE("\n");

Step5: /* Truth value. */
       SWRITE("Truth value                 : ");
       TRUTHWR(LELTI(c,TRUTH)); 
       t = LELTI(c,HOWTV);
       if (t == BYPRP)
         SWRITE("    by propagation.");
       else if (t == BYTEV)
         SWRITE("    by trial evaluation.");
       else if (t == BYEQC)
         SWRITE("    by equational constraint.");
       SWRITE("\n");

Step6: /* Degrees of the substituted polys. */
       SWRITE("Degrees after substitution  : ");
       D = LELTI(c,DEGSUB);
       if (D == NIL) 
         SWRITE("Not known yet or No polynomial.");
       else
         LWRITE(D);
       SWRITE("\n");

Step7: /* Multiplicities of the projection factors. */
       SWRITE("Multiplicities              : ");
       M = LELTI(c,MULSUB);
       LWRITE(M);
       SWRITE("\n");

Step8: /* Signs of Projection Factors. */
       SWRITE("Signs of Projection Factors\n");
       S = LELTI(c,SIGNPF);
       for (i = 1; i <= k; i++)
         {
         S1 = LELTI(S,k-i+1);
         SWRITE("Level "); GWRITE(i); SWRITE("  : ");
         if (S1 == 0)
           SWRITE("Not determined");
         else
           SIGNLWR(S1);
         SWRITE("\n");
         }

Step9: /* Sample point. */
       if (k == 0) goto Step10;
       SWRITE("----------   Sample point  ---------- \n");
       SAMPLEWR(c);

Step10: /* Finish. */
       SWRITE("\n----------------------------------------------------\n");
       goto Return;

Return: /* Prepare for return. */
       return;
}

