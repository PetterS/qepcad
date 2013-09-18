/*======================================================================
                      EC1(c,L,Bs)

Establish Children of the root.

\Input
  \parm{c} is  the root cell.
  \parm{L} is  a list of real roots. (See CONSTRUCT for detail.)
  \parm{Bs} is  the basis.

\Output
  The children of the cell \v{c} are established.
======================================================================*/
#include "qepcad.h"

void EC1(Word c, Word L, Word Bs)
{
       Word B,I,J,Lp,M,N,S,Sp,P,a,b,kp,l,r,rp,s,xb,xp,Lp1,OL;
       /* hide kp,xp; */
       Word T;

Step1: /* Initialize. */
        S = NIL; Lp = L; kp = 1; xp = 0;
        M = PMON(1,1); J = LIST2(0,0); 

Step2: /* No real root. */
        if (Lp != NIL) goto Step3;
	a = CSSP(NIL,NIL);
        b = LIST1(a); s = LIST3(M,J,b);
        xp = xp + 1; xb = LIST1(xp);
        P = LIST1(0);
        Sp = MCELL(kp,NIL,FALSE,LELTI(c,TRUTH),s,xb,P,LELTI(c,HOWTV),NIL,NIL); S = COMP(Sp,S);
        SLELTI(c,CHILD,S);
        goto Return;

Step3: /* First sector. */
	ADV(Lp,&Lp1,&Lp);
        FIRST3(Lp1,&B,&I,&OL); FIRST2(I,&l,&r);
	a = AFFRN(CSSP(NIL,l)); 
	T = r;
        b = LIST1(a); s = LIST3(M,J,b);
        xp = xp + 1; xb = LIST1(xp);
        P = LIST1(0);
        Sp = MCELL(kp,NIL,FALSE,LELTI(c,TRUTH),s,xb,P,LELTI(c,HOWTV),NIL,NIL); S = COMP(Sp,S);

Step4: /* First section. */
        if (PDEG(B) == 1)
          { a = IUPRLP(B); a = AFFRN(a); b = LIST1(a); s = LIST3(M,J,b); }
        else
          { a = AFGEN(); b = LIST1(a); s = LIST3(B,I,b); }
        xp = xp + 1; xb = LIST1(xp);
        P = LIST1(0);

        N = NIL;
	for(Word X = OL; X != NIL; X = RED(X)) { N = COMP(LIST2(THIRD(LELTI(FIRST(X),PO_LABEL)),1),N); }

        Sp = MCELL(kp,NIL,FALSE,LELTI(c,TRUTH),s,xb,P,LELTI(c,HOWTV),NIL,N); S = COMP(Sp,S);

Step5: /* Check if there are more roots. */
        if (Lp == NIL) goto Step9;
        rp = r;

Step6: /* Next sector. */
	ADV(Lp,&Lp1,&Lp);
        FIRST3(Lp1,&B,&I,&OL); FIRST2(I,&l,&r);
	a = AFFRN(CSSP(T,l)); 
	T = r;
        b = LIST1(a); s = LIST3(M,J,b);
        xp = xp + 1; xb = LIST1(xp);
        P = LIST1(0);
        Sp = MCELL(kp,NIL,FALSE,LELTI(c,TRUTH),s,xb,P,LELTI(c,HOWTV),NIL,NIL); S = COMP(Sp,S);

Step7: /* Next section. */
        if (PDEG(B) == 1)
          { a = IUPRLP(B); a = AFFRN(a); b = LIST1(a); s = LIST3(M,J,b); }
        else
          { a = AFGEN(); b = LIST1(a); s = LIST3(B,I,b); }
        xp = xp + 1; xb = LIST1(xp);
        P = LIST1(0);
        N = NIL;
	for(Word X = OL; X != NIL; X = RED(X)) { N = COMP(LIST2(THIRD(LELTI(FIRST(X),PO_LABEL)),1),N); }
        Sp = MCELL(kp,NIL,FALSE,LELTI(c,TRUTH),s,xb,P,LELTI(c,HOWTV),NIL,N); S = COMP(Sp,S);

Step8: /* Loop. */
        goto Step5;

Step9: /* Last sector. */
	a = AFFRN(CSSP(T,NIL));
        b = LIST1(a); s = LIST3(M,J,b);
        xp = xp + 1; xb = LIST1(xp);
        P = LIST1(0);
        Sp = MCELL(kp,NIL,FALSE,LELTI(c,TRUTH),s,xb,P,LELTI(c,HOWTV),NIL,NIL); S = COMP(Sp,S);

Step10: /* Finalize. */
        S = INV(S); SLELTI(c,CHILD,S); goto Return;

Return: /* Prepare for return. */
       return;
}
