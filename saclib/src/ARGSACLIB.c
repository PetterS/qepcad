/*======================================================================
		  ARGSACLIB(argc,argv; ac,av)

Process the command line arguments.

Inputs
  argc : the number of command line arguments.
  argv : the command line arguments.

Outputs
    ac : the number of remaining command line arguments (i.e. argc minus
         the number of SACLIB command line arguments).
    av : the non-SACLIB command line arguments.

Side effects
  Various saclib global variables are initialized according
  to the command line arguments.
======================================================================*/
#include "saclib.h"

void ARGSACLIB(argc,argv,ac_,av_)
       int argc;
       char **argv;
       int *ac_;
       char ***av_;
{
       Word gcm,nsprime,nmprime,nlprime,nu,nup,rho,nptr1;
       int  ac,i,j;
       char **av;

Step1: /* Store the default values of certain global variables. */ 
       nu = NU;
       nup = NUp;
       gcm = GCM;
       rho = RHO;
       nsprime = NSPRIME;
       nmprime = NMPRIME;
       nlprime = NLPRIME;
       nptr1 = NPTR1;

Step2: /* Initialize return values. */ 
       ac = 1;
       av = (char **)malloc(argc*sizeof(char *));
       av[0] = argv[0];

Step3: /* Parse command line arguments. */ 
       for (i=1; i < argc; i++)
	 if (argv[i][0] == '+') {
           switch(argv[i][1]) {
             case 'N': 
               if (argv[i][2] == 'p') nup = atoi(argv[i]+3); 
               else                   nu  = atoi(argv[i]+2);
	       break;
             case 'G': gcm    = atoi(argv[i]+2); break; 
             case 'R': rho    = atoi(argv[i]+2); break;
	     case 'S': nsprime = atoi(argv[i]+2); break;
	     case 'M': nmprime = atoi(argv[i]+2); break; 
             case 'L': nlprime = atoi(argv[i]+2); break; 
	     case 'T': nptr1 = atoi(argv[i]+2); break;
             case 'h': INFOSACLIB(argv[0]); exit(0);  
             default : INFOSACLIB(argv[0]); exit(0);
           }
	 }  
	 else {
	   av[ac] = argv[i];
	   ac++;
	 }

Step4: /* Set the global variables to their new values. */ 
       NU     = nu;
       NUp    = nup;
       GCM    = gcm;
       RHO    = rho;
       NSPRIME = nsprime;
       NMPRIME = nmprime;
       NLPRIME = nlprime;
       NPTR1 = nptr1;

Return: /* Prepare for return. */
       *ac_ = ac;
       *av_ = av; 
       return;
}
