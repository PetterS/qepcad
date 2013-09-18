/*==================================================================
                       t <- TSVSLI(A,I)

Test sign variation on standard logarithmic interval.

Inputs
   A : a univariate integral polynomial of positive degree.
   I : a standard logarithmic binary rational interval.

Outputs
   t : 0 if A has no sign variations on I, 1 otherwise.
=================================================================*/
#include "saclib.h"

Word TSVSLI(A,I)
        Word A,I;
{
        Word As,c,cp,k,t;

Step1: /* Let I = (c / 2^k, (c+1) / 2^k). */
        SLIWE(I,&k,&c,&cp);

Step2: /* Map I to (0,1). */
        As = IUPBHT(A,-k);
        As = IUPTR(As,c);

Step3: /* Return if A* has no variations. */
        t = IUPVART(As);
        if (t == 0)
           goto Return;

Step4: /* Map (0,1) to (0,\inf). */
        t = IPVCHTP(As);
        if (t == 2)
           t = 1;

Return: /* Return. */
        return(t);
}
