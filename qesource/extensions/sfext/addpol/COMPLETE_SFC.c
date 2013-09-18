/*======================================================================
                      COMPLETE_SFC() 

Complete solution formula construction.

Side effects
  This is the sub-program called by qepcad for guaruanteed solution
  formula construction.  If the CAD does not suffice for solution
  formula construction, derivatives of projection factors are added
  to the projection factor set to make the CAD self-defining.
======================================================================*/
#include "qepcad.h"

void COMPLETE_SFC()
{
      Word t,Ps,Ds,Q,SF,C,i,D0,P0,D1,P1,J0;

D0 = GVPC; P0 = LCOPY(GVPF); J0 = LCOPY(GVPJ);
for(i = GVNFV - LENGTH(J0); i > 0; i--)
  J0 = INV(COMP(NIL,INV(J0)));

/* TIME */ t = ACLOCK();
SWRITE("\n");
Step0: /* Check for the trivial cases. */
      switch( DOPFSUFF(P0,LIST1(D0)) ) {
      case (TRUE) : SWRITE("\n\nInput is identically TRUE.\n\n");
	            goto Return;
      case (FALSE): SWRITE("\n\nInput is identically FALSE.\n\n");
	            goto Return; 
      case (NIL)  :
	            t = ACLOCK() - t;
	            SWRITE("Projection set does not suffice, adding polynomials ...\n");
		    t = ACLOCK() - t;
	            /* SWRITE("\nThe projection set does not suffice. Should projection");
	            SWRITE("\nfactors be removed from the projection factor set as\n");
		    SWRITE("derivatives are added? (y/n) ");
		    if (getchar() == 'y') { */
		      CLEAN_BIGLOOP(J0,P0,P0,D0,GVNFV,&P1,&D1); break; /*  }
		    else { 
		      STRIPPED_BIGLOOP(J0,P0,P0,D0,GVNFV,&P1,&D1); break; } */
      default     : P1 = P0; D1 = D0; break; }

Step1: /* Find some polynomials which we know will pop up in Q. */
       /* Q = PWUDSCWCP(D1,P1,GVNFV); */
      CCADCON(GVNFV,P1,D1,&Ps,&Ds); Ds = NIL;

Step2: /* Find a minimal set of polynomials which suffice for SF const,
	  making use of the set Q computed in Step 1. */
      Q = MINPFSET(P1,Ps,D1); Ps = NIL;

Step3: /* Construct a CAD from the proj-closure of Qs from step2. */
      CCADCONFPFS(GVNFV,P1,D1,Q,&Ps,&Ds);

/* TIME */ t = ACLOCK() - t;

/* STAT */ SWRITE("Solution formula construction preprocessing time: ");
           IWRITE(t); SWRITE(" milliseconds\n");

Step5: /* Construct that solution formula. */
/* TIME */ t = ACLOCK();
      SF = NSFCONST(Ds,P1,Q);
/* TIME */ t = ACLOCK() - t;

      SWRITE("\n=======================================================\n");
      SWRITE("\nAn equivalent quantifier-free formula:\n\n");
      FWPWRITE(SF);
      SWRITE("\n\nIn other words,\n\n");
      FWPIWRITE(SF);
      SWRITE("\n\n");
      SWRITE("Formula constructed in "); IWRITE(t); SWRITE(" milliseconds\n");
      SWRITE("=======================================================\n");
      /*NSFCONST_STATS();
        SWRITE("\nStatistics for the CAD used for this construction:\n");
        PCADSTATS(Ds,Ps); */ 

Return:/* Prepare to return. */      
      return;
}



void modCOMPLETE_SFC()
{
      Word t,Ps,Ds,Q,SF,C,i,D0,P0,D1,P1,J0,Lt,Lf;

D0 = GVPC; P0 = LCOPY(GVPF); J0 = LCOPY(GVPJ);
for(i = GVNFV - LENGTH(J0); i > 0; i--)
  J0 = INV(COMP(NIL,INV(J0)));

/* TIME */ t = ACLOCK();
SWRITE("\n");
Step0: /* Check for the trivial cases. */
      switch( DOPFSUFF(P0,LIST1(D0)) ) {
      case (TRUE) : SWRITE("\n\nInput is identically TRUE.\n\n");
	            goto Return;
      case (FALSE): SWRITE("\n\nInput is identically FALSE.\n\n");
	            goto Return; 
      case (NIL)  :
	            t = ACLOCK() - t;
	            SWRITE("Projection set does not suffice, adding polynomials ...\n");
		    t = ACLOCK() - t;
	            /* SWRITE("\nThe projection set does not suffice. Should projection");
	            SWRITE("\nfactors be removed from the projection factor set as\n");
		    SWRITE("derivatives are added? (y/n) ");
		    if (getchar() == 'y') { */
		      CLEAN_BIGLOOP(J0,P0,P0,D0,GVNFV,&P1,&D1); break; /*  }
		    else { 
		      STRIPPED_BIGLOOP(J0,P0,P0,D0,GVNFV,&P1,&D1); break; } */
      default     : P1 = P0; D1 = D0; break; }

#ifdef hjldhjkf
Step1: /* Find some polynomials which we know will pop up in Q. */
       /* Q = PWUDSCWCP(D1,P1,GVNFV); */
      CCADCON(GVNFV,P1,D1,&Ps,&Ds); Ds = NIL;

Step2: /* Find a minimal set of polynomials which suffice for SF const,
	  making use of the set Q computed in Step 1. */
      Q = MINPFSET(P1,Ps,D1); Ps = NIL;

Step3: /* Construct a CAD from the proj-closure of Qs from step2. */
      CCADCONFPFS(GVNFV,P1,D1,Q,&Ps,&Ds);

/* TIME */ t = ACLOCK() - t;

/* STAT */ SWRITE("Solution formula construction preprocessing time: ");
           IWRITE(t); SWRITE(" milliseconds\n");
#endif

Step5: /* Construct that solution formula. */
	   SWRITE("\n");
	   Ds = SCADDSCON(D1,NIL,GVNFV);
	   Ps = P1;
	   Ds = PCAD2ESPCAD(Ps,Ps,Ds,NIL);
	   LTFOCWTV(Ds,&Lt,&Lf);
/* TIME */ t = ACLOCK();
	   STRAIGHTFORWARDSF(Lt,Lf,Ps,GVNFV);
/* TIME */ t = ACLOCK() - t;

Return:/* Prepare to return. */      
      return;
}
