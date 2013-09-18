/*======================================================================
                      CAD2D(Fs; t,F_e,F_n,F_s)

2D Cylindrical Algebraic Decomposition.
 
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
#include "cad2d.h"

void QepcadCls2D::CAD2D(Word Fs, Word *t_, Word *F_e_, Word *F_n_, Word *F_s_)
{
       Word A,D,F,F_e,F_n,F_s,Fh,J,P,Q,Ths,f,i,r,t;
       Word L;
Step1: /* Normalize. */
       FIRST4(Fs,&r,&f,&Q,&Fh);
       F = NORMQFF(Fh);
       GVNQFF = F;

Step2: /* Projection. */
       A = EXTRACT(r,F);
       GVNIP = A;
       for (i = 1; i <= r; i++) 
	 NMNIP[i] = LENGTH(LELTI(A,i));
       GVPF = LLCOPY(A);
       GVLV = r;
       PROJECT(r,A,&P,&J);

Step3: /* Truth-invariant CAD. */
       NMFPF = 0;
       for (i=1; i<=f; i++) NMFPF=NMFPF+LENGTH(LELTI(P,i));
       D = TICAD(Q,F,f,P,A);


Step4: /* Solution. */
               /*Int*/ GVPC = D;
               /*Int*/ PCNSTEP = 1;
               /*Int*/ if (INTERACT()) USERINT(LFS("Before Solution"),'e');
         
Return: /* Prepare for return. */
       *t_ = t;
       *F_e_ = F_e;
       *F_n_ = F_n;
       *F_s_ = F_s;
       return;
}

Word AllAdjs(QepcadCls2D &Q, Word D,Word P,Word J)
{
  Word A,L,a,b,X;
  A = NIL;
  for(L = CINV(LELTI(D,CHILD)); RED(L) != NIL; L = RED2(L))
  {
    FIRST2(L,&a,&b);
    X = Q.ADJ_2D_PART(b,THIRD(L),a,P,J);
    A = CONC(FIRST(X),A);
  }
  return A;
}

Word printgraph(Word D, Word L)
{
  Word A,R,c,Q,a,b;
  FILE* fp;
  fp = fopen("temp","w");
  
  SWRITE("graph: {\n");

  /* Write nodes */
  for(Q = LELTI(D,CHILD); Q != NIL; Q = RED(Q))
    for(R = LELTI(FIRST(Q),CHILD); RED(R) != NIL; R = RED2(R))
    {
      c = SECOND(R);
      SWRITE("node: { title: \"");
      OWRITE(LELTI(c,INDX));
      SWRITE("\" }\n");
    }

  /* Write edges */
  while(L != NIL)
  {
    FIRST2(FIRST(L),&a,&b);
    L = RED(L);
    SWRITE("edge: { source: \"");
    OWRITE(a);
    SWRITE("\" target: \"");
    OWRITE(b);
    SWRITE("\" }\n");
  }

  SWRITE("}\n");
  return 0;
}
