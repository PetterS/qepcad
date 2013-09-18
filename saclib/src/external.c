/*===========================================================================
			     external variables
===========================================================================*/
#include "sacsys.h"
#include "sactypes.h"


/*-------------------------------------------
  External Variables
-------------------------------------------*/

/* Version. */

char SACLIBVERSION[] = "SACLIB 2.2.5";


/* List processing */
Word AVAIL;
char *BACSTACK;
Word GCC = 0;
Word GCCC = 0;
Word GCGLOBALS = BETA;
Word GCAC = 0;
Word GCM = 0;
Word NU = NU_;
Word RHO = RHO_;
Word *SPACE;
Word *SPACEB;
Word *SPACEB1;
Word GCAAVAIL;
GCArray *GCASPACE;
GCArray *GCASPACEBp;
Word NUp = NUp_;
Word BETAp;
Word BETApp;


/* Timing */

Word TAU = 0;
Word TAU0;
Word TAU1;


/* Integer arithmetic */

Word DELTA;
Word EPSIL;
Word ETA;
Word RINC;
Word RMULT;
Word RTERM;
Word TABP2[65];
Word THETA;
Word TMI[128];
Word ZETA;


/* Miscellaneous */

Word NPFDS = NPFDS_;
Word NSPRIME = NSPRIME_;
Word SPRIME;
Word NMPRIME = NMPRIME_;
Word MPRIME;
Word NLPRIME = NLPRIME_;
Word LPRIME;
Word UZ210;
Word NPTR1 = NPTR1_;
Word GCAPTR1;
BDigit *FFPLUS1;
BDigit FFSIZE;


/* Input/Output */

Word LASTCHAR;
