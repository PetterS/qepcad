/*============================================
    Sample program calling SACLIB
  =============================================*/

#include "saclib.h"

int sacMain(argc, argv)
        int argc;
        char **argv;
{
        Word    I1,I2,I3,t;
        Word    i,n;

Step1:  /* Input. */
        SWRITE("Please enter the first integer: "); I1 = IREAD();
        SWRITE("Please enter the second integer: "); I2 = IREAD();
        SWRITE("How many iterations? "); n = GREAD();

Step2:  /* Processing. */
        t = CLOCK();
        for (i=0; i<n; i++)
          I3 = IPROD(I1,I2);
        t = CLOCK() - t;

Step3:  /* Output. */
        IWRITE(I1); SWRITE(" * "); IWRITE(I2); SWRITE(" =\n"); IWRITE(I3);
        SWRITE("\nRepeating the above computation "); GWRITE(n);
	SWRITE(" times took\n"); GWRITE(t); SWRITE(" milliseconds.\n");

Return:
	return(0);
}
