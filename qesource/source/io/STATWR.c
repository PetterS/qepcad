/*======================================================================
                      STATWR()

Statistics Write.
======================================================================*/
#include "qepcad.h"
#include "db/CAPolicy.h"
#define INITSP    12  /* Initial spacing for the table rows. */
#define TABINC    10  /* Tab increment for the table rows. */

void QepcadCls::STATWR()
{
       Word N,T,i,k,n,t,D;
       /* hide N,T,i,k,n,t; */

Step1: /* Heading. */
       for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('='); SWRITE("\n\n");

Step2: /* Overall Statistics. */
       SWRITE("Total time without garbage collection  :");
       T = ACLOCK() - BTMQEPCAD;
       FGWRITE(T,TABINC); SWRITE("\n");
       SWRITE("Total time for garbage collection      :");
       FGWRITE(TAU,TABINC); SWRITE("\n");
       SWRITE("Total time with garbage collection     :");
       FGWRITE(T + TAU,TABINC); SWRITE("\n\n");

Step3: /* Database management. */
       SWRITE("Time taken for database management     :");
       FGWRITE(TMDBMNG,TABINC); SWRITE("\n");
       SWRITE("Time saved by utilizing databases      :");
       FGWRITE(TMDBSAV,TABINC); SWRITE("\n");
       SWRITE("Net time saving                        :");
       FGWRITE(TMDBSAV - TMDBMNG,TABINC); SWRITE("\n\n");

Step4: /* Normalization Phase. */
       SWRITE("Time taken for Normalization Phase     :");
       FGWRITE(TMNORMQFF,TABINC); SWRITE("\n\n");

Step5: /* Time for Projection Phase. */
       SWRITE("Time taken for Projection Phase:\n");
       for (i = 1; i <= INITSP + GVNV * TABINC; i++) CWRITE('-'); SWRITE("\n");
       SWRITE("Level"); TAB(INITSP);
       for (k = 1; k <= GVNV - 1; k++) FGWRITE(k,TABINC);
       SWRITE("     Total\n");
       for (i = 1; i <= INITSP + GVNV * TABINC; i++) CWRITE('-'); SWRITE("\n");
       
       T = 0; SWRITE("PROJECT"); TAB(INITSP);
       for (k = 1; k <= GVNV - 1; k++) { t = TMPROJECT[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("..PROJ"); TAB(INITSP);
       for (k = 1; k <= GVNV - 1; k++) { t = TMPROJ[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....IPFZT"); TAB(INITSP);
       for (k = 1; k <= GVNV - 1; k++) { t = TMIPFZT[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");

       T = 0; SWRITE("..IPLFAC"); TAB(INITSP);
       for (k = 1; k <= GVNV - 1; k++) { t = TMIPLFAC[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");

       T = 0; SWRITE("..APPEND"); TAB(INITSP);
       for (k = 1; k <= GVNV - 1; k++) { t = TMAPPEND[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       for (i = 1; i <= INITSP + GVNV * TABINC; i++) CWRITE('-'); SWRITE("\n\n");

Step6: /* Counts for Projection Phase. */
       SWRITE("Counts for Projection Phase:\n");
       for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('-'); SWRITE("\n");
       SWRITE("Level"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) FGWRITE(k,TABINC);
       SWRITE("     Total\n");
       for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('-'); SWRITE("\n");
       
       N = 0; SWRITE("Proj Poly"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { n = NMPJ[k]; N = N + n; FGWRITE(n,TABINC); }
       FGWRITE(N,TABINC); SWRITE("\n");
    
       N = 0; SWRITE("Proj Fact"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { n = NMPF[k]; N = N + n; FGWRITE(n,TABINC); }
       FGWRITE(N,TABINC); SWRITE("\n");
     
       for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('-'); SWRITE("\n\n");

Step7: /* Truth invariant CAD construction Phase. */
       SWRITE("Time taken for Truth Invariant CAD Construction Phase:\n");
       for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('-'); SWRITE("\n");
       SWRITE("Level"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) FGWRITE(k,TABINC);
       SWRITE("     Total\n");
       for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('-'); SWRITE("\n");
    
       T = 0; SWRITE("TICAD"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMTICAD[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("..CHOOSE"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMCHOOSE[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("..CONVERT"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMCONVERT[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....TCN"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMTCN[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....NORMAL"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMNORMAL[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....SIMPLE"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMSIMPLE[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("..CONSTRUCT"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMCONSTRUCT[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....SUBST"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMSUBST[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....AFUPLM"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMAFUPLM[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....AFCSBM"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMAFCSBM[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....AFUPBRI"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMAFUPBRI[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");

       T = 0; SWRITE("...AFUPHIBRI"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMAFUPHIBRI[k];T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....EC"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMEC[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....SIGNP"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMSIGNP[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....RCFAFC"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMRCFAFC[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....SUBSTR"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMSUBSTR[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....IPLSRP"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMIPLSRP[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....IPFSBM"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMIPFSBM[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....IPLRRI"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMIPLRRI[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....ECR"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMECR[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("....SIGNPR"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMSIGNPR[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("..EVALUATE"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMEVALUATE[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");
    
       T = 0; SWRITE("..PROPAGATE"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMPROPAGATE[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T,TABINC); SWRITE("\n");

       T = 0; SWRITE("..APEQC"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { t = TMAPEQC[k]; T = T + t; FGWRITE(t,TABINC); }
       FGWRITE(T, TABINC); SWRITE("\n");
    
       for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('-'); SWRITE("\n\n");

Step8: /* Counts for Truth--Invariant CAD Construction Phase. */
       SWRITE("Counts for Truth--Invariant CAD Construction Phase:\n");
       for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('-'); SWRITE("\n");
       SWRITE("Level"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) FGWRITE(k,TABINC);
       SWRITE("     Total\n");
       for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('-'); SWRITE("\n");
    
       N = 0; SWRITE("Stacks"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { n = NMSTACK[k]; N = N + n; FGWRITE(n,TABINC); }
       FGWRITE(N,TABINC); SWRITE("\n");
   
       N = 0; SWRITE("..Rational"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { n = NMSTACKR[k]; N = N + n; FGWRITE(n,TABINC); }
       FGWRITE(N,TABINC); SWRITE("\n");
   
       N = 0; SWRITE("Cells"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { n = NMCELL[k]; N = N + n; FGWRITE(n,TABINC); }
       FGWRITE(N,TABINC); SWRITE("\n");
  
       N = 0; SWRITE("Conversion"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { n = NMCONVERT[k]; N = N + n; FGWRITE(n,TABINC); }
       FGWRITE(N,TABINC); SWRITE("\n");
    
       N = 0; SWRITE("..Trivial"); TAB(INITSP);
       for (k = 1; k <= GVNV; k++) { n = NMTCONVERT[k]; N = N + n; FGWRITE(n,TABINC); }
       FGWRITE(N,TABINC); SWRITE("\n");
    
       for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('-'); SWRITE("\n\n");

Step10: /* Solution formula construction stats */
       SWRITE("Timings for solution formula construction:\n");
       D = CINV(TMSFCONST);
       for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('-'); SWRITE("\n\n");
       for(k = 1; D != NIL; D = RED(D), k++)
       {
	 SWRITE("Solution Formula Construction call #"); IWRITE(k);
	 SWRITE(": "); IWRITE(FIRST(D)); SWRITE("ms\n");
	 for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('-'); SWRITE("\n\n");
       }

Step11: /* CA Server stats */
       for(ServerBase::iterator p = GVSB.begin(); p != GVSB.end(); ++p)    
       { p->second->reportStats(cout); cout << endl; }
       
Step12: /* Tail. */
       for (i = 1; i <= INITSP + (GVNV + 1) * TABINC; i++) CWRITE('='); SWRITE("\n");
       goto Return;

Return: /* Prepare for return. */
       return;
}
