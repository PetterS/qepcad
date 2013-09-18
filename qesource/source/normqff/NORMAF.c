/*======================================================================
                      F <- NORMAF(A)

Normalize Atomic Formula.

\Input
  \parm{A} is an atomic formula.

\Output
  \parm{F} is a quantifier--free formula equivalent to \v{A}
           such that all the atomic formulas in \v{F} are 
           normalized.
======================================================================*/
#include "qepcad.h"
Word NORMAETF(Word A);

Word NORMAF(Word A)
{
       Word F,I,L,L_i,Lh,Lh_i,P,P_i,Ph_i,T,c,e_i,r,rh_i,s;
       /* hide rh_i,s; */

Step1: /* Get the components. */
       if (FIRST(A) == IROOT)
       {
	 F = NORMAETF(A);
	 goto Return;
       }
       FIRST4(A,&T,&P,&r,&I);

Step2: /* \v{P} = 0. */
       if (P != 0) goto Step3;
       switch (T)
         {
         case EQOP: F = LIST4(EQOP,0,0,NIL); break;
         case GEOP: F = LIST4(EQOP,0,0,NIL); break;
         case LEOP: F = LIST4(EQOP,0,0,NIL); break;
         case GTOP: F = LIST4(NEOP,0,0,NIL); break;
         case LTOP: F = LIST4(NEOP,0,0,NIL); break;
         case NEOP: F = LIST4(NEOP,0,0,NIL);
         break; }
       goto Return;

Step3: /* Factor \v{P}. */
       IPFACDB(r,P,&s,&c,&L);

Step4: /* Adjust \v{T}. */
       if (s < 0) T = NEGRLOP(T);

Step5: /* \v{P} is an integer. */
       if (L != NIL) goto Step6;
       switch (T)
         {
         case NEOP: F = LIST4(EQOP,0,0,NIL); break;
         case GTOP: F = LIST4(EQOP,0,0,NIL); break;
         case GEOP: F = LIST4(EQOP,0,0,NIL); break;
         case EQOP: F = LIST4(NEOP,0,0,NIL); break;
         case LTOP: F = LIST4(NEOP,0,0,NIL); break;
         case LEOP: F = LIST4(NEOP,0,0,NIL);
         break; }
       goto Return;

Step6: /* Simplify the representation of the polys in \v{L}. */
       Lh = NIL;
       while (L != NIL)
         {
         ADV(L,&L_i,&L);
         FIRST2(L_i,&e_i,&P_i);
         PSIMREP(r,P_i,&rh_i,&Ph_i);
         Lh_i = LIST3(e_i,rh_i,Ph_i);
         Lh = COMP(Lh_i,Lh);
         }
       Lh = INV(Lh);

Step7: /* Expand. */
       switch (T)
         {
         case EQOP: F = EXPAFEQ(Lh); break;
         case GTOP: F = EXPAFGT(Lh); break;
         case LTOP: F = EXPAFLT(Lh); break;
         case NEOP: F = LIST2(NOTOP,EXPAFEQ(Lh)); break;
         case LEOP: F = LIST2(NOTOP,EXPAFGT(Lh)); break;
         case GEOP: F = LIST2(NOTOP,EXPAFLT(Lh)); break;
         }
       goto Return;

Return: /* Prepare for return. */
       return(F);
}

/*======================================================================
                      F <- NORMAETF(A)

Normalize Atomic Extended Tarski Formula.

\Input
  \parm{A} is an atomic Extended Tarski formula.

\Output
  \parm{F} is a quantifier--free formula equivalent to \v{A}
           such that all the atomic formulas in \v{F} are 
           normalized.
Note: We need to allow this to be called on normalized atomic
formulas without crashing, so this should work when "P" from below
is a single poly or a non-empty list of polys.  The way this is 
handled is a hack: a poly's first element should always be a BETA-digit.
The first element of a non-empty list of polys is itself a list.
We will, however, assume that if a list appears, it is in fact a list
of irreducible, primitive, positive polynomials.
======================================================================*/

Word NORMAETF(Word A)
{
  Word X,T,j,P,r,I,s,c,L,Lr,Fs,Fa,L_i,e_i,P_i,rk_i,Pk_i,F;

Step1: /* Get the components. */
       FIRST6(A,&X,&T,&j,&P,&r,&I);

Step2: /* Factor \v{P}. */
       if (!ISLIST(FIRST(P)))
	 IPFACDB(r,P,&s,&c,&L);
       else {
	 Word Lp = NIL;
	 for(; P != NIL; P = RED(P))
	   Lp = COMP(LIST2(1,FIRST(P)),Lp);
	 L = CINV(Lp);
       }

Step3: /* Sign of content is irrelevant in _root_ expressions! */

Step4: /* Simplify the representation of the polys in \v{L}. */
       Lr = NIL; /* r-level factors */
       Fs = NIL; /* factors of level less than r can't be zero! */
       while (L != NIL)
       {
         ADV(L,&L_i,&L);
         FIRST2(L_i,&e_i,&P_i);
         PSIMREP(r,P_i,&rk_i,&Pk_i);
	 if (rk_i < r)
	   Fs = COMP(LIST4(NEOP,Pk_i,rk_i,NIL),Fs);
	 else
	   Lr = COMP(Pk_i,Lr);
       }
       Lr = INV(Lr);

Step5: /* Create formula */
       Fa = LIST6(IROOT,T,j,Lr,r,NIL);
       F = COMP(Fa,Fs);
       F = COMP(ANDOP,CINV(F));

Return: /* Prepare for return. */
       return(F);
}
