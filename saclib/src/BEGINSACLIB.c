/*===========================================================================
			 BEGINSACLIB(p)

Begin SACLIB.

Inputs
  p : a C pointer, the address of the first element on the system stack.

Side effects
  Various data structures are initialized.
===========================================================================*/
#include "saclib.h"

void BEGINSACLIB(p)
       Word *p; 
{
       Word L,i,m,n,t;

Step1: /* Remember the startup time. */
       TAU0 = CLOCK();

Step2: /* Allocate memory for the SPACE and GCASPACE arrays. */
       NU = NU + (NU % 2);
       SPACE = (Word *)malloc((unsigned) (sizeof(Word) * (NU + 1)));
       if (SPACE == ((Word *)0))
	  FAIL("BEGINSACLIB Step2a","Not enough memory to allocate SPACE.");
       GCASPACE = (GCArray *)malloc((unsigned) (sizeof(GCArray) * (NUp + 1)));
       if (GCASPACE == ((GCArray *)0))
	  FAIL("BEGINSACLIB Step2b","Not enough memory to allocate GCASPACE.");

Step3: /* Set up for fast access to the SPACE and GCASPACE arrays. */
       SPACEB  = SPACE - BETA;
       SPACEB1 = SPACE - BETA1;
       BETAp = BETA + NU + 1;
       BETApp = BETAp + NUp + 1;
       GCASPACEBp = &(GCASPACE[-BETAp]);
      
Step4: /* Create available cell list and available GCA list. */
       AVAIL = NIL;
       for (L = BETA+NU-1; L > BETA; L -= 2) {
	  SFIRST(L,0);
	  SRED(L,AVAIL);
	  AVAIL = L; }
       GCAAVAIL = NIL;
       for (L = BETAp+NUp; L > BETAp; L--) {
	  GCASPACEBp[L].next = GCAAVAIL;
	  GCASPACEBp[L].flag = GC_NO_CHECK;
	  GCASPACEBp[L].len = 0;
	  GCASPACEBp[L].array = (Word *)0;
	  GCAAVAIL = L; }

Step5: /* Store the beginning of stack. */
       BACSTACK = (char *)p;

Step6: /* Declare global variables. */
       GCGLOBAL(&UZ210);
       GCGLOBAL(&SPRIME);
       GCGLOBAL(&MPRIME);
       GCGLOBAL(&LPRIME);
       GCGLOBAL(&GCAPTR1);

Step7: /* Compute ZETA, ETA, THETA, DELTA, EPSIL and TABP2 elements. */
       i = 1;
       t = 1;
       while (t < BETA) {
	  TABP2[i] = t;
	  i = i + 1;
	  t = t + t; }
       ZETA = i - 1;
       ETA = 0;
       t = BETA;
       do {
	  t = t / 10;
	  ETA = ETA + 1; }
       while (!(t < 10));
       THETA = 1;
       for (i = 1; i <= ETA; i++)
	  THETA = 10 * THETA;
       DELTA = TABP2[ZETA / 2 + 1];
       EPSIL = BETA / DELTA;

Step8: /* Initialize the table of inverses modulo BETA = 2^29. */
       CTMI(TMI);

Step9: /* Compute RMULT, RINC and RTERM. */
       L = CONC(LIST10(3,1,4,1,5,9,2,6,5,3),
                LIST10(5,8,9,7,9,3,2,3,8,4));
       m = 0;
       while (m < BETA / 10) {
	  ADV(L,&t,&L);
	  m = 10 * m + t; }
       m = m / 8;
       RMULT = 8 * m + 5;
       L = CONC(LIST10(2,1,1,3,2,4,8,6,5,4),
                LIST10(0,5,1,8,7,1,0,0,0,0));
       m = 0;
       for (i = 1; i <= ETA; i++) {
	  ADV(L,&t,&L);
	  m = 10 * m + t; }
       DQR(m,0,THETA,&RINC,&t);
       if (EVEN(RINC) == 1)
	  RINC = RINC + 1;
       L = CONC(LIST10(5,7,7,2,1,5,6,6,4,9),
                LIST10(0,1,5,3,2,8,6,0,6,0));
       m = 0;
       for (i = 1; i <= ETA; i++) {
	  ADV(L,&t,&L);
	  m = 10 * m + t; }
       RTERM = m;

Step10: /* Compute small prime list. */
       SPRIME = DPGEN(1,NSPRIME);

Step11: /* Compute units of Z sub 210. */
       UZ210 = NIL;
       for (i = 209; i >= 1; i-=2) 
	  if (DGCD(210,i) == 1)
	     UZ210 = COMP(i,UZ210);

Step12: /* Compute medium prime list. */
       if (NMPRIME >= 2 * (EPSIL / ZETA))
	  FAIL("BEGINSACLIB","NMPRIME is too large",NMPRIME);
       n = RNCEIL(RNRED(ZETA,2));
       n = 7 * ((NMPRIME * n) / 10);
       MPRIME = INV(DPGEN(EPSIL - n,n/2));
       /* n is an approximation to ln EPSIL, so that MPRIME will
	  contain approximately NMPRIME primes.
	  MPRIME contains successively smaller primes beginning with
	  the largest prime that is ceiling(ZETA/2) bits long. */

Step13: /* Compute large prime list. */
       if (NLPRIME >= BETA / ZETA)
	  FAIL("BEGINSACLIB","NLPRIME is too big",NLPRIME);
       n = 7 * ((NLPRIME * ZETA) / 10);
       LPRIME = DPGEN(BETA - n,n/2);
       /* n is an approximation to ln BETA, so that LPRIME will
	  contain approximately NLPRIME primes. */

Step14: /* Allocate GCAPTR1. */
       GCAPTR1 = GCAMALLOC(NPTR1,GC_NO_CHECK);

Step15: /* Remember the current time. */
       TAU1 = CLOCK();

Return: /* Prepare for return. */
       return;
}
