#include "cad2d.h"
#include <iostream>
#include "db/convenientstreams.h"
#include <signal.h>
#include "db/CAPolicy.h"

static void SIGINT_handler(int i, siginfo_t *sip,void* uap);
static void init_SIGINT_handler();

/*====================================================================
                 main(argc,argv)

Main Algorithm which drives the QEPCAD sytem. 
====================================================================*/
int main(int argc, char **argv)
{
       Word Fs,F_e,F_n,F_s,V,t,ac;
       char **av;

Step1: /* Set up the system. */
       ARGSACLIB(argc,argv,&ac,&av);
       BEGINSACLIB((Word *)&argc);
       BEGINQEPCAD(ac,av);
       init_SIGINT_handler(); /* A special handler for SIGINT is needed
                                 to shut down child processes. Also used
			         for SIGTERM. */

Step2: /* Read input, create CAD, write result */
       PCCONTINUE = FALSE;
       PRINTCAD2DBANNER();
       do {
	 // Reinitialize system in between runs
	 if (PCCONTINUE == TRUE) 
	 { 
	   INITSYS();
	   PCCONTINUE = FALSE;
	 }
	 INPUTRD(&Fs,&V);
	 QepcadCls2D Q(V,Fs);
	 BTMQEPCAD = ACLOCK();
	 Q.CAD2D(Fs,&t,&F_e,&F_n,&F_s);
       } while (PCCONTINUE == TRUE);
       
Step3: /* Clean up the system. */
       SWRITE("\n=====================  The End  =======================\n");
       STATSACLIB();
       ENDQEPCAD();
       ENDSACLIB(SAC_FREEMEM);
       free(av); /* Frees the array malloc'd by ARGSACLIB */

Return: /* Prepare for return. */
       return 0;
}

static void SIGINT_handler(int i, siginfo_t *sip,void* uap)
{  
  ENDQEPCAD(); // Kill child CAServer processes
  ENDSACLIB(SAC_FREEMEM);
  exit(1);
}

static void init_SIGINT_handler() 
{
  struct sigaction *p;
  p = (struct sigaction *)malloc(sizeof(struct sigaction));
  p->sa_handler = NULL;
  p->sa_sigaction = SIGINT_handler;
  sigemptyset(&(p->sa_mask));
  p->sa_flags = SA_SIGINFO;
  sigaction(SIGINT,p,NULL);
  sigaction(SIGTERM,p,NULL);
  free(p);
}
