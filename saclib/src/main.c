/*======================================================================
                      main(argc,argv)

Default main routine.

Inputs
  argc : the number of command line arguments.
  argv : the command line arguments.
======================================================================*/
#include "saclib.h"

extern int sacMain  P__((int ac, char **av));


void main(argc, argv)
       int argc;
       char **argv;
{
       int    ac,r;
       char **av;

Step1: /* Process command line arguments. */
       ARGSACLIB(argc,argv,&ac,&av);

Step2: /* Initialize SACLIB. */
       BEGINSACLIB((Word *)&argc);

Step3: /* Start real main routine. */
       r = sacMain(ac,av);

Step4: /* Cleanup. */
       ENDSACLIB(SAC_FREEMEM);

Return: /* Exit. */
       exit(r);
}
