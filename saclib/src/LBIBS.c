/*======================================================================
                      LBIBS(L)

List of BETA-integers bubble sort.

Inputs
  L  : an arbitrary list of BETA-integers, with possible repetitions.

Side effects
  L is sorted into non-decreasing order by the bubble-sort method.
  The list L, though not its location, is modified.
======================================================================*/
#include "saclib.h"

void LBIBS(L)
       Word L;
{
       Word Lp,Lpp,M,Mp,ap,app;
       /* hide algorithm */

Step1: /* Trivial case. */
       if (L == NIL)
         goto Return;

Step2: /* General case. */
       M = NIL;
       do
         {
         Lp = L;
         Lpp = RED(Lp);
         ap = FIRST(Lp);
         Mp = NIL;
         while (Lpp != M)
           {
           app = FIRST(Lpp);
           if (ap > app)
             {
             SFIRST(Lp,app);
             SFIRST(Lpp,ap);
             Mp = Lpp;
             }
           else
             ap = app;
           Lp = Lpp;
           Lpp = RED(Lp);
           }
         M = Mp;
         }
       while (!(M == NIL));

Return: /* Prepare for return. */
       return;
}
