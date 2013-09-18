/*======================================================================
                      QEPCAD(Fs; t,F_e,F_n,F_s)

Quantifier Elimination by Partial Cylindrical Algebraic Decomposition.
 
\Input
  \parm{F*} $=(Q_{f+1} x_{f+1})\cdots(Q_r x_r)\hat{F}(x_1,\ldots,x_r)$,
            $0\leq f < r$, is a quantified formula.
 
\Output
  \parm{t}  is either \c{EQU} or \c{INEQU}.
  \parm{Fe} is a quantifier-free formula equivalent to~\v{F*}
            if \v{t} is \c{EQU}, otherwise \v{Fe} is undefined.
  \parm{Fn} is a quantifier-free formula necssary for~\v{F*}
            if \v{t} is \c{INEQU}, otherwise \v{Fn} is undefined.
  \parm{Fs} is a quantifier-free formula sufficient for~\v{F*}
            if \v{t} is \c{INEQU}, otherwise \v{Fs} is undefined.
======================================================================*/
#include "qepcad.h"

void QepcadCls::QEPCADauto(Word Fs, Word *t_, Word *F_e_, Word *F_n_, Word *F_s_)
{
       Word A,D,F,F_e,F_n,F_s,Fh,J,P,Q,Ths,f,i,r,t, T;
       /* hide Ths,i,t; */
       Word cL,**cC,cr,ce,ci,*cT,cj,cs,cl,ct; /* Chris variables. */
       Word Cs,Ps,Qs,Pps,Cps,Qps,SF; /* Chris variables. */
       char c1,c2; /* Chris variables. */

Step1: /* Normalize. */
       FIRST4(Fs,&r,&f,&Q,&Fh);
       F = NORMQFF(Fh);
       if (GVUA != NIL) GVNA = NORMQFF(GVUA);
       GVNQFF = F;
       if (TYPEQFF(F) != UNDET) { t = EQU; F_e = F; goto Return; }

Step2: /* Projection. */
       if (GVUA != NIL) F = LIST3(ANDOP,GVNA,F);
       A = EXTRACT(r,F);
       if (GVUA != NIL) {
	 GVNA = SECOND(F);
	 F = THIRD(F); }
       GVNIP = A;
       GVPF = LLCOPY(A);
       GVLV = r;
       PROJECTauto(r,A,&P,&J);

Step3: /* Truth-invariant CAD. */
       D = TICADauto(Q,F,f,P,A);

Step4: /* Solution. */
       GVPC = D;
       if (!PCMZERROR)
	 SFC3(GVPC,GVPF,GVPJ,GVNFV,LIST10(0,0,0,1,0,3,2,4,1,-1));
       else
	 SFCFULLD(GVPC,GVPF,GVPJ,GVNFV);

Return: /* Prepare for return. */
       *t_ = t;
       *F_e_ = F_e;
       *F_n_ = F_n;
       *F_s_ = F_s;
       return;
}
