/*======================================================================
                      PRRESALG()

Process res-alg command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRRESALG()
{
       Word C;

Step1: /* Get the argument. */
       C = CREADB();

Step2: /* Check for the validity. */
       if (C != 'M' && C != 'S' && C != 'B') {
	 SWRITE("Error res-alg: 'B', 'M', or 'S' was expected.\n");
	 goto Step4; }

Step3: /* Set. */
       if (C == 'M')
         PCRESALG = MODULAR;
       else if (C == 'S')
         PCRESALG = SUBRES;
       else
         PCRESALG = BEZOUT;
       goto Return;

Step4: /* Error exit. */
       DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
