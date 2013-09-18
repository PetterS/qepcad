/*======================================================================
                      d <- RIPROD(I,J)

Rational interval product.

Inputs
  I, J : rational intervals.
Outputs
  K : a rational interval. K=I+J.
======================================================================*/
#include "saclib.h"

Word RIPROD(I,J)
       Word I,J;
{
       Word K;
       Word L,a,a1,a2,b,b1,b2,cp1,cp2,c1,c2;

Step1: /* Extract endpoints. */
       FIRST2(I,&a1,&a2);
       FIRST2(J,&b1,&b2);

Step2: /* a1 >= 0. */
       if (RNSIGN(a1) >= 0)
         {
         if (RNSIGN(b1) >= 0)
           L = LIST4(a1,b1,a2,b2);
         else
           if (RNSIGN(b2) < 0)
             L = LIST4(a2,b1,a1,b2);
           else
             L = LIST4(a2,b1,a2,b2);
         goto Step5;
         }

Step3: /* a2 < 0. */
       if (RNSIGN(a2) < 0)
         {
         if (RNSIGN(b1) >= 0)
           L = LIST4(a1,b2,a2,b1);
         else
           if (RNSIGN(b2) < 0)
             L = LIST4(a2,b2,a1,b1);
           else
             L = LIST4(a1,b2,a1,b1);
         goto Step5;
         }

Step4: /* a1 < 0 <= a2. */
       if (RNSIGN(b1) >= 0)
         L = LIST4(a1,b2,a2,b2);
       else
         if (RNSIGN(b2) < 0)
           L = LIST4(a2,b1,a1,b1);
         else
           L = CONC(LIST4(a1,b2,a1,b1),LIST4(a2,b1,a2,b2));

Step5: /* Compute endpoints of K. */
       ADV2(L,&a,&b,&L);
       c1 = RNPROD(a,b);
       ADV2(L,&a,&b,&L);
       c2 = RNPROD(a,b);
       if (L != NIL)
         {
         ADV2(L,&a,&b,&L);
         cp1 = RNPROD(a,b);
         c1 = RNMIN(c1,cp1);
         ADV2(L,&a,&b,&L);
         cp2 = RNPROD(a,b);
         c2 = RNMAX(c2,cp2);
         }

Step6: /* Compose K. */
       K = LIST2(c1,c2);

Return:
       return(K);
}
