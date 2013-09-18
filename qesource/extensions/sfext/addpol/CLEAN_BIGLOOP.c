/*======================================================================
                     CLEAN_BIGLOOP(Jb,Pb,P0,D0,N;P,D)

Clean big loop for SF construction.  Prunes projection factor set as
derivatives are added.

Inputs
  Jb : Projection polynomial set.
  Pb : Projection factor set.
  P0 : The projection factor set for P0.
  D0 : The partial cad with truth values
  N  : The number of free variables.
======================================================================*/
#include "qepcad.h"

void QepcadCls::CLEAN_BIGLOOP(Word Jb, Word Pb, Word P0, Word D0, Word N, Word *P_, Word *D_)
{
      Word P,D,G,C,T,N_T,Tb,Gb,Gbp,S_N_T,Tp,Gp,K,KT,p,i,S;
      Word Q,Q_i,Ps,Ds,Qb,Qb_i,Dsp,t,Ph;
      Word inum,tm,temp;

Step1: /* Initialize. */
      P = LCOPY(P0); D = D0; 
      G = NIL; for(i = 0; i < N; i++) { G = COMP(NIL,G); }
      Ph = P;
     
       /* Stats. */ inum = 0;


Step2: /* Construct the conflicting pair set. */
  
       /* Stats. */ SWRITE("\n\nIteration #: "); IWRITE(++inum);
                    SWRITE("################################################\n");
                    CADSTATS(D,P);
                    tm = ACLOCK();

      C = CFLCELLLIST(LIST1(D));
      for(t = C; t != NIL && FIRST(t) == NIL;t = RED(t));
  
                    SWRITE("Step2: ");IWRITE(ACLOCK()-tm);

      if (t == NIL) goto Return; /* If no conflicting pairs, return. */
		    SWRITE("\nThere are "); IWRITE(LENGTH(FIRST(t)));
		    SWRITE(" conflicting pairs at the highest level.\n");

Step3: /* Construct T. */
  
       /* Stats. */ tm = ACLOCK();

      BPOLSETS(C,D,P,&T,&N_T);
  
                    SWRITE("\nStep3: ");IWRITE(ACLOCK()-tm);


Step4: /* Construct G. */
  
       /* Stats. */ tm = ACLOCK();

      Gb = PMINHITSETWPTS(T,P,LELTI(G,N_T));
      G = NIL; for(i = 0; i < N; i++) { G = COMP(NIL,G); }
                    temp = LCOPY(G);
      SLELTI(G,N_T,Gb);
  
                    SWRITE("\nStep4: ");IWRITE(ACLOCK()-tm);
		    SWRITE("\n|Gb| = ");IWRITE(LENGTH(Gb));
		    IPLLDWRMOD(GVVL,G);


Step5: /* Construct S, a set for best possible nec & suff conditions. */
       /* Stats. */ tm = ACLOCK();

       /***
	*  Best possible is too much.  We play the coarse CAD game for effic.
	***/
       CCADCON(N,P,D,&Ps,&Ds); Ds = 0; Ps = PFSSUNION(Ps,G);

       /* S = MINPFSETNSC(P,Ps,D,C); */ S = P;
  
                    SWRITE("\nStep5: ");IWRITE(ACLOCK()-tm);


Step6: /* Construct K. */
  
       /* Stats. */ tm = ACLOCK();

       KCONST(Jb,Pb,Gb,&K,&KT);
  
                    SWRITE("\nStep6: ");IWRITE(ACLOCK()-tm);


Step7: /* Construct the CAD defined by the PROJ-closure of S u G. */
  
       /* Stats. */ tm = ACLOCK();

       Q = PFSSUNION(S,G);
       CCADCONFPFS(N,P,D,Q,&Ps,&Ds);
       Dsp = CADFPCAD(Ds,Ps,NIL,NIL,P);
  
                    SWRITE("\nStep7: ");IWRITE(ACLOCK()-tm);


Step8: /* Introduce new derivative, p. */
  
       /* Stats. */ tm = ACLOCK();

       p = NEWDERIV(KT,P,Pb,Jb,Ph);
  
                    SWRITE("\nStep8: ");IWRITE(ACLOCK()-tm);
		    SWRITE("\nGonna introduce ... ");
		    SLELTI(temp,N_T,LIST1(p));
		    IPLLDWRMOD(GVVL,temp);


Step9: /* Construct new P, the PROJ-closure of S u G u {p}. */
  
       /* Stats. */ tm = ACLOCK();

       SLELTI(Q,N_T,PFSUNION(LELTI(Q,N_T),LIST1(p)));
       PROJMCECCLOSURE(Pb,Jb,Q);
  
                    SWRITE("\nStep9: ");IWRITE(ACLOCK()-tm);


Step10:/* Construct D, the RCAD defined by P. */
  
       /* Stats. */ tm = ACLOCK();

       P = PFSREORDER(Q,Ps);
       D = RNCADRTV(Dsp,Ps,P,N);
       Ph = PFSSUNION(Ph,P);
  
                    SWRITE("\nStep10: ");IWRITE(ACLOCK()-tm);


Step11:/* Repeat the Loop. */
       goto Step2;

Return:/* Return. */
       *P_ = P;
       *D_ = D;
       return;

}
