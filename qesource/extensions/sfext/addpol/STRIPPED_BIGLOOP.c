/*======================================================================
                     CLEAN_BIGLOOP(Jb,Pb,P0,D0,N;P,D)

Clean big loop for SF construction.  Doesn't prune projection factor set 
as derivatives are added.

Inputs
  Jb : Projection polynomial set.
  Pb : Projection factor set.
  P0 : The projection factor set for P0.
  D0 : The partial cad with truth values
  N  : The number of free variables.
======================================================================*/
#include "qepcad.h"

void QepcadCls::STRIPPED_BIGLOOP(Word Jb, Word Pb, Word P0, Word D0, Word N, Word *P_, Word *D_)
{
      Word P,D,G,C,T,N_T,Tb,Gb,Gbp,S_N_T,Tp,Gp,K,KT,p,i,S;
      Word Q,Q_i,Ps,Ds,Qb,Qb_i,Dsp,t,Ph;
      Word inum,tm,tt;

Step1: /* Initialize. */
                    tt = ACLOCK();
      P = NIL; for(i = N; i > 0; i--) { P = COMP(LELTI(P0,i),P); }
      D = D0; 
      G = NIL; for(i = 0; i < N; i++) { G = COMP(NIL,G); }
       /* Stats. */ inum = 0;

Step2: /* Construct the conflicting pair set. */
       /* Stats. */ if (PCVERBOSE) {
	            SWRITE("\n\nIteration #: "); IWRITE(++inum);SWRITE("\n");
                    CADSTATS(D,P);
                    tm = ACLOCK(); }

      C = CFLCELLLIST(LIST1(D));
      for(t = C; t != NIL && FIRST(t) == NIL;t = RED(t));

                    if (PCVERBOSE) {
		      SWRITE("\nStep2: ");IWRITE(ACLOCK()-tm);SWRITE("\n"); }

      if (t == NIL) goto Return; /* If no conflicting pairs, return. */

Step3: /* Construct T. */
       /* Stats. */ tm = ACLOCK();
      BPOLSETS(C,D,P,&T,&N_T);

                    if (PCVERBOSE) {
		    SWRITE("\nStep3: ");IWRITE(ACLOCK()-tm);SWRITE("\n"); }

Step4: /* Construct G. */
       /* Stats. */ tm = ACLOCK();
      Gb = PMINHITSETWPTS(T,P,LELTI(G,N_T));
      G = NIL; for(i = 0; i < N; i++) { G = COMP(NIL,G); }
      SLELTI(G,N_T,Gb);
                    if (PCVERBOSE) {
                    SWRITE("\nStep4: ");IWRITE(ACLOCK()-tm);SWRITE("\n");
		    SWRITE("\n|Gb| = ");IWRITE(LENGTH(Gb));SWRITE("\n");
		    IPLLDWRMOD(GVVL,G);SWRITE("\n"); }

Step6:/* Construct K. */
       /* Stats. */ tm = ACLOCK();
      KCONST(Jb,Pb,Gb,&K,&KT);

                    if (PCVERBOSE) {
		    SWRITE("\nStep6: ");IWRITE(ACLOCK()-tm);SWRITE("\n"); }

Step8: /* Introduce new derivative, p. */
       /* Stats. */ tm = ACLOCK();
      p = NEWDERIV(KT,P,Pb,Jb,P);

                    if (PCVERBOSE) {
                    SWRITE("\nStep8: ");IWRITE(ACLOCK()-tm);
		    SWRITE("\nGonna introduce ... ");
		    IPLDWR(GVVL,LIST1(p));SWRITE("\n"); }

Step9: /* Construct new P, the PROJ-closure of S u G u {p}. */
       /* Stats. */ tm = ACLOCK();
      Ps = LCOPY(P);
      SLELTI(P,N_T,PFSUNION(LELTI(P,N_T),LIST1(p)));
      PROJMCECCLOSURE(Pb,Jb,P);

                    if (PCVERBOSE) {
		    SWRITE("\nStep9: ");IWRITE(ACLOCK()-tm);SWRITE("\n"); }

Step10:/* Construct D, the RCAD defined by P. */
       /* Stats. */ tm = ACLOCK();
      P = PFSREORDER(P,Ps);
      D = RNCADRTV(D,Ps,P,N);

                    if (PCVERBOSE) {
		    SWRITE("\nStep10: ");IWRITE(ACLOCK()-tm);SWRITE("\n"); }

Step11:/* Repeat the Loop. */
      goto Step2;

Return:/* Return. */
      tt = ACLOCK() - tt;

                    if (PCVERBOSE) {
		    SWRITE("The whole thing took: "); IWRITE(tt); SWRITE(" miliseconds!\n\n"); }

      *P_ = P;
      *D_ = D;
      return;

}
