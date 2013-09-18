/*======================================================================
                      EC(c,L,E,Bs)

Establish Children.

\Input
  \parm{c} is  the non-root cell.
  \parm{L} is  a list of real roots. (See CONSTRUCT for detail.)
  \parm{E} is  the multiplicity matrix.
  \parm{Bs} is  the basis.

\Output
  The children of the cell \v{c} are established.
======================================================================*/
#include "qepcad.h"

void EC(Word c, Word L, Word E, Word Bs)
{
       Word B,I,J,Lp,M,N,S,Sp,Pp,P,a,b,bp,kp,l,r,rp,s,sp,x,xb,xp;
       /* hide kp,xp; */
       Word T;

Step1: /* Initialize. */
        S = NIL; Lp = L; kp = LELTI(c,LEVEL) + 1; x = LELTI(c,INDX); xp = 0;
        sp = LELTI(c,SAMPLE); FIRST3(sp,&M,&J,&b); Pp = LELTI(c,SIGNPF);

Step2: /* No real root. */
        if (Lp != NIL) goto Step3;
	a = CSSP(NIL,NIL);
        bp = CCONC(b,LIST1(a)); s = LIST3(M,J,bp);
        xp = xp + 1; xb = CCONC(x,LIST1(xp));
        P = COMP(0,Pp);
        Sp = MCELL(kp,NIL,FALSE,LELTI(c,TRUTH),s,xb,P,LELTI(c,HOWTV),NIL,NIL); S = COMP(Sp,S);
        SLELTI(c,CHILD,S);
        goto Return;

Step3: /* First sector. */
        ADV2(Lp,&I,&B,&Lp); FIRST2(I,&l,&r);
	a = AFFRN(CSSP(NIL,l));
	T = r;
        bp = CCONC(b,LIST1(a)); s = LIST3(M,J,bp);
        xp = xp + 1; xb = CCONC(x,LIST1(xp));
        P = COMP(0,Pp);
        Sp = MCELL(kp,NIL,FALSE,LELTI(c,TRUTH),s,xb,P,LELTI(c,HOWTV),NIL,NIL); S = COMP(Sp,S);

Step4: /* First section. */
        s = LIST5(B,I,M,J,b);
        xp = xp + 1; xb = CCONC(x,LIST1(xp));
        P = COMP(0,Pp);
        N = MKMUL(E,LSRCH(B,Bs));
        Sp = MCELL(kp,NIL,FALSE,LELTI(c,TRUTH),s,xb,P,LELTI(c,HOWTV),NIL,N); S = COMP(Sp,S);

Step5: /* Check if there are more roots. */
        if (Lp == NIL) goto Step9;
        rp = r;

Step6: /* Next sector. */
        ADV2(Lp,&I,&B,&Lp); FIRST2(I,&l,&r);
	a = AFFRN(CSSP(T,l)); 
	T = r;
        bp = CCONC(b,LIST1(a)); s = LIST3(M,J,bp);
        xp = xp + 1; xb = CCONC(x,LIST1(xp));
        P = COMP(0,Pp);
        Sp = MCELL(kp,NIL,FALSE,LELTI(c,TRUTH),s,xb,P,LELTI(c,HOWTV),NIL,NIL); S = COMP(Sp,S);

Step7: /* Next section. */
        s = LIST5(B,I,M,J,b);
        xp = xp + 1; xb = CCONC(x,LIST1(xp));
        P = COMP(0,Pp);
        N = MKMUL(E,LSRCH(B,Bs));
        Sp = MCELL(kp,NIL,FALSE,LELTI(c,TRUTH),s,xb,P,LELTI(c,HOWTV),NIL,N); S = COMP(Sp,S);

Step8: /* Loop. */
        goto Step5;

Step9: /* Last sector. */
	a = AFFRN(CSSP(T,NIL));
        bp = CCONC(b,LIST1(a)); s = LIST3(M,J,bp);
        xp = xp + 1; xb = CCONC(x,LIST1(xp));
        P = COMP(0,Pp);
        Sp = MCELL(kp,NIL,FALSE,LELTI(c,TRUTH),s,xb,P,LELTI(c,HOWTV),NIL,NIL); S = COMP(Sp,S);

Step10: /* Finalize. */
        S = INV(S); SLELTI(c,CHILD,S); goto Return;

Return: /* Prepare for return. */
       return;
}

