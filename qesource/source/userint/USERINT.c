/*======================================================================
                      USERINT(P,W)

User Interface.

\Input
  \parm{P} is a list of characters for prompting.
  \parm{W} is a character indicating where this interface
           has been called.
======================================================================*/
#include "qepcad.h"
#include "../../extensions/adj2d/adj2D.h"
#include "../../extensions/newadj/newadj2D.h"

/* PROTOTYPES FOR SOME EXPERIMENTAL FUNCTIONS! */
void PRINTBORDERPOLS(Word D);
void VERTFILL2D(Word D);
void PASSLINE(Word D, Word F, Word P);
void CADTVNEG(Word D);
void CADTVSUPINF(Word D, Word k, Word dir);

void QepcadCls::USERINT(Word P, Word W)
{
       Word I,t,i,j,k,op;
       Word F,s;
       /* hide I,t; */

Step1: /* Get a command ID. */
       I = GETCID(P,W);

Step2: /* Process the command. */
       switch (I) {
       case 1: PRHELP(W); break;
       case 2: PRWHATIS(); break;
       case 3: PRQUIT(); break;
       case 4: { PRSTEP(&t); if (t == 1) goto Return; } break;
       case 5: PRUDB(); break;
       case 6: PRLDB(); break;
       case 7: PRPROJOP(); break;
       case 8: PRCCS(); break;
       case 9: PRIGS(); break;
       case 10: PRDF(); break;
       case 11: PRDVL(); break;
       case 12: PRDQ(); break;
       case 13: PRDQFF(); break;
       case 14: PRDNQFF(); break;
       case 15: PRDIP(); break;
       case 16: PRDPC(); break;
       case 17: PRDCC(); break;
       case 18: PRDLV(); break;
       case 19: PRDC(); break;
       case 20: PRDSET(); break;
       case 21: { PRFINISH(); goto Return; } break;
       case 22: PRDPF(); break;
       case 23: PRDPJ(); break;
       case 24: { PRMCC(&t); if (t == 1) goto Return; } break;
       case 25: PRDTRACEA(); break;
       case 26: PRTRACEA(); break;
       case 27: PRTRACED(); break;
       case 28: STATWR(); break;
       case 30: PRTCN(); break;
       case 31: PRRSP(); break;
       case 32: PRRMPF(); break;
       case 33: PRRMPJ(); break;
       case 34: PRDTRACED(); break;
       case 35: PRDFPCSTAT(); break;
       case 38: DSTATWR(); break;
       case 39: /* full-cad command! */
	 if (PCMZERROR)
	   SWRITE("Command incompatible with \"measure-zero-erro\"! No change made!\n");
	 else
	   PCFULL = 'y'; 
	 break;
       case 40: { PRGO(); goto Return; } break;
       case 41: PRDESIRED(); break;
       case 42: PRUSEDESIRED(); break;
       case 43: PRDDESIRED(); break;
       case 44: PRCCSF(); break;
       case 45: PRIPFZT(); break;
       case 46: PRAPPROX(); break;
       case 47: PRSIMPLIFIER(); break;
       case 48: PRDCS(); break; 
       case 49: PRDPCS(); break; 
       case 51: PREQNCONST(); break;
       case 52: PRRESALG(); break;
       case 53: PRPROPEC(); break;
       case 54: PREQNCONSTL(); break;
       case 55: PRDEQNCONST(); break;
       case 56: PRCHPIVOT(); break;
       case 57: PRDSEARCH(); break;
       case 58: PRSEARCH(); break;
       case 59: SOLEXTINT(); break;
       case 60: PRDLPI(); break;
       case 61: PRDLFI(); break;
       case 63: TRUECELLWRITE(GVPC); break;
       case 64: FALSECELLWRITE(GVPC); break;
       case 69: PRDSTACK(); break;
       case 71: DISP2DCAD(GVPC,GVPF,GVPJ); break;
       case 72: /*ADJ_2D_TEST(GVPC,GVPF,GVPJ); */ /* HATEST(GVPC,GVPF,GVPJ); */ break;
       case 73: PCCHFLAG = 1; break;
       case 74: PCVERBOSE = (CREADB() == 'y') ? 1 : 0; break;
       case 75: t = IREAD(); SIMPLE_CAD_INFO(GVPC,GVPF,GVNFV,t); break;
       case 76: TVCLOSURE1D(GVPC,GVPF,GVPJ,GVNFV,IREAD()); break;
       case 77: TVCLOSURE1DS(GVPC,GVPF,GVPJ,GVNFV,IREAD()); break;
       case 78: t = ACLOCK();
	 TV2D(GVPC,GVPF,GVPJ); /* "Special" closure */
	 t = ACLOCK() - t;
	 SWRITE("That took "); IWRITE(t); SWRITE(" milliseconds.\n\n");
	 break;
       case 79: t = ACLOCK();
	 CLOSURE2D(GVPC,GVPF,GVPJ); /* True closure */
	 t = ACLOCK() - t;
	 SWRITE("That took "); IWRITE(t); SWRITE(" milliseconds.\n\n");
	 break;
       case 80:
	 SWRITE("CELL INDEX: ");
	 I = LREAD();
	 SWRITE("TRUE ("); IWRITE(TRUE);
	 SWRITE("), FALSE ("); IWRITE(FALSE);
	 SWRITE("), or UNDET ("); IWRITE(UNDET);
	 SWRITE("u): ");
	 t = IREAD();
	 SETTRUTHVALUE(t,I,GVPC);
	 break;
       case 81:
	 i = IREAD();
	 if (i == 0) i = GVNFV;
	 j = IREAD();
	 k = IREAD();
	 op = IREAD();
	 KTHSECTIONTRUE(GVPC,j,k,op,i);
	 break;
	     
       case 82:
	 SWRITE("The solution set has dimension ");
	 IWRITE(SOLSETDIM(GVPC,GVNFV));
	 SWRITE("\n");
	 break;

       case 83:
	 PRAFUPBRI(); break;

       case 84:
	 {
	   SWRITE("There are ");
	   BDigit n = NUMSOLPOINTS(GVPC,GVNFV);
	   if (n == -1)
	     SWRITE("infinitely many solution points.\n");
	   else {
	     IWRITE(n);
	     SWRITE(" solution points.\n"); }
	 }
	 break;

       case 85:
	 /* CONVEXPROP(IREAD(),GVPC);*/
	 EXPROP(IREAD(),GVPC);
	 break;
       case 86: 
	 SWRITE("Give me a formula:\n");
	 FMAREAD(GVPF,GVVL,&j,&t);
	 if (t)
	   SETTV2FMA(GVPC,GVPF,j,GVNFV);
	 else
	   SWRITE("Format's wrong!\n");
	 break;
       case 88:
	 t = LREAD(); 
	 REPLACE_WITH_SIMPLE(GVPC,GVPF,
			     t == NIL ? 0 : FIRST(t) + 2*SECOND(t));
	 break;
       case 90:
	 j = DOPFSUFF(GVPF,LIST1(GVPC));
	 switch(j) {
	 case 0: SWRITE("CAD is identically false.\n"); break;
	 case 1: SWRITE("CAD is identically true.\n"); break;
	 case 2: SWRITE("CAD is projection definable.\n"); break;
	 default: SWRITE("CAD is not projection definable.\n"); break; }
	 break;
	     
       case 91:
	 SFC4(GVPC,GVPF,GVPJ,IREAD(),NIL);
	 /* IPLDWR(GVVL,BYPOLLIST2D(GVPC,GVPF,GVPJ)); */

	 /* UNIVPROP(IREAD(),GVPC); */
	 break;
     
       case 92: /*Vertical Fill */
	 VERTFILL2D(GVPC);
	 break;

       case 93: /* PASSLINE */
	 SWRITE("Give me a formula:\n");
	 FMAREAD(GVPF,GVVL,&j,&t);
	 if (t) {
	   t = SCADDSCON(GVPC,NIL,2);
	   t = PCAD2ESPCAD(GVPF,GVPF,t,NIL);
	   PASSLINE(t,j,GVPF);
	 }
	 else
	   SWRITE("Format's wrong!\n");
	 break;

       case 94: /* Boundary */
	 BOUNDARY2D(GVPC,GVPF,GVPJ);
	 break;


       case 95: /*Experimental  exp1*/
	 PRINTBORDERPOLS(GVPC);
	 break;

       case 96: /* p-2d-cad : "print 2d cad as eps-file" */
	 PLOT2DCAD2FILE(GVPC,GVPF,GVPJ);
	 break;

       case 97: /* measure-zero-error */
	 if (PCFULL == 'y')
	   SWRITE("Command incompatible with the  \"full-cad\" option! No change made!\n");
	 else
	   PCMZERROR = 1;
	 break;
	 
       case 98: /* "assume" command */
	 QFFRDR(CINV(REDI(CINV(GVVL),GVNV - GVNFV)),&F,&s);
	 if (s) {
	   if (GVUA == NIL)
	     GVUA = F;
	   else if (FIRST(GVUA) != ANDOP)
	     GVUA = LIST3(ANDOP,GVUA,F);
	   else
	     GVUA = CCONC(GVUA,LIST1(F));
	 }
	 else
	   SWRITE("Incorrect format:  No assumptions added!\n");
	 break;

       case 99: /* "d-assumptions" command */
	 if (GVUA == NIL)
	   SWRITE("There are no assumptions!\n");
	 else {
	   QFFWR(GVVL,GVUA); SWRITE("\n"); 
	 }
	 break;
	 
       case 100: /* "negate-truth-values" command */
	 CADTVNEG(GVPC);
	 break;
	 
       case 101: /* "lim-inf" command */
	 CADTVSUPINF(GVPC,GVNFV,-1);
	 break;

       case 102: /* "lim-sup" command */
	 CADTVSUPINF(GVPC,GVNFV,+1);
	 break;

       case 103: /* Print witnesses command */
	 if (GVWL == 0)
	   SWRITE("Command only valid for SAT problems!\n");
	 else if (GVWL != -1)
	 {
	   /* Prepare S, the list of buckets for bucket sort. */
	   Word S;
	   for(S = NIL,i = 0; i < GVNV+1; i++)
	     S = COMP(NIL,S);

	   /* Put each cell in the proper dimension bucket. */
	   Word L = GVWL,c;
	   while(L != NIL) {
	     ADV(L,&c,&L);
	     i = CELLDIM(c) + 1;
	     SLELTI(S,i,COMP(c,LELTI(S,i))); }

	   /* Print buckets in reverse order. */
	   for(S = CINV(S); S != NIL; S = RED(S))
	     for(Word Li = FIRST(S); Li != NIL; Li = RED(Li))
	       CELLWR(FIRST(Li));
	 }
	 break;
	 
       case 104:
	 PREQNCONSTPOLY();
	 break;

       case 105:
	 PCCONTINUE = TRUE;
	 goto Return;
	 break;

       }
       goto Step1;

Return: /* Prepare for return. */
       return;
}


/********************************************************
 * Inputs:
 * D   : a CAD
 * k   : the highest level (i.e. no k+1st free variable)
 * dir : +1 for sup and -1 for inf
 * Side effects:
 * Sets the truth values in D to the lim-sup/inf of the
 * initial truth value set.  This works stack-wise on the
 * highest-level variable.
 ********************************************************/
void CADTVSUPINF(Word D, Word k, Word dir)
{
  if (LELTI(D,LEVEL) < k-1)
  {
    for(Word L = LELTI(D,CHILD); L != NIL; L = RED(L))
      CADTVSUPINF(FIRST(L),k,dir);
  }
  else
  {
    Word L = LELTI(D,CHILD);
    if (dir == -1) 
      L = CINV(L);

    Word m = 0, i = 0;
    while(L != NIL)
    {
      /* c is the ith cell in L, its truth value is t. */
      Word c = FIRST(L);
      L = RED(L);
      ++i;
      Word t = LELTI(c,TRUTH);

      /* adjust m and c's truth value appropriately */
      if (t == TRUE)
	SLELTI(c,TRUTH,FALSE);
      if (t == TRUE)
      {
	if (i % 2 == 0)
	  m = c;
	else if (L != NIL)
	  m = FIRST(L);
	else
	  m = 0;
      }
    }
    if (m != 0)
      SLELTI(m,TRUTH,TRUE);
  }
}

void CADTVNEG(Word D)
{
  Word t = LELTI(D,TRUTH);
  if (t == FALSE) SLELTI(D,TRUTH,TRUE);
  if (t == TRUE) SLELTI(D,TRUTH,FALSE);
  for(Word L = LELTI(D,CHILD); L != NIL; L = RED(L))
    CADTVNEG(FIRST(L));
}

/**********
 * b is a sector cell in the 1D CAD
 * This function is called by PRINTBORDERPOLS to give the index (in the
 * signature) of the upper and lower border polynomial in the stack over
 * b.  This assumes at present that all cells in the stack have had a
 * truth-value assigned to them.
 **********/
void BORDERPOLINDICES(Word b, Word *L_, Word *U_)
{
  Word i,j,T,S;

  for(T = LELTI(b,CHILD); LELTI(FIRST(T),TRUTH) != TRUE; T = RED(T));
  for(S = FIRST(LELTI(FIRST(T),SIGNPF)), i = 1; FIRST(S) != 0; S = RED(S),i++);

  for(T = CINV(LELTI(b,CHILD)), j = 1; LELTI(FIRST(T),TRUTH) != TRUE; T = RED(T), j++);
  for(S = FIRST(LELTI(FIRST(T),SIGNPF)), j = 1; FIRST(S) != 0; S = RED(S),j++);

  *L_ = i;
  *U_ = j;
}


/**********
 * This function takes a CAD of 2-space and simply prints out all the cells
 * that could represent a line that needs to be added to form the convex hull.
 **********/
void PRINTBORDERPOLS(Word D)
{
  Word L,lL,uL,lR,uR,cL,cU,T,M;

  /* Process leftmost cell */
  L = LELTI(D,CHILD);
  BORDERPOLINDICES(FIRST(L),&lL,&uL);
  L = RED(L);

  while(L != NIL)
  {
    /* Get Section Cell info */
    ADV(L,&M,&L);
    for(T = LELTI(M,CHILD); LELTI(FIRST(T),TRUTH) != TRUE; T = RED(T));
    cL = FIRST(T);
    for(T = CINV(LELTI(M,CHILD)); LELTI(FIRST(T),TRUTH) != TRUE; T = RED(T));
    cU = FIRST(T);

    /* Get Right Sector Cell Info */
    BORDERPOLINDICES(FIRST(L),&lR,&uR);
    L = RED(L);
    
    /* L O W E R   B O U N D A R Y */
    if (lL != lR)
    {
      SWRITE("Cell "); OWRITE(LELTI(cL,INDX)); SWRITE(" has a boundary swap!\n");
    }
    else
    {
      for(T = LELTI(cL,MULSUB); FIRST(FIRST(T)) != lL; T = RED(T));
      if (SECOND(FIRST(T)) > 1)
      {
	SWRITE("Cell "); OWRITE(LELTI(cL,INDX)); SWRITE(" has multiple root!\n");
      }
    }

    /* U P P E R   B O U N D A R Y */
    if (uL != uR)
    {
      SWRITE("Cell "); OWRITE(LELTI(cU,INDX)); SWRITE(" has a boundary swap!\n");
    }
    else
    {
      for(T = LELTI(cU,MULSUB); FIRST(FIRST(T)) != uL; T = RED(T));
      if (SECOND(FIRST(T)) > 1)
      {
	SWRITE("Cell "); OWRITE(LELTI(cU,INDX)); SWRITE(" has multiple root!\n");
      }
    }

    /* Prepare for next loop! */
    lL = lR;
    uL = uR;
  }
}


/**********************
 ** Vertical fill in 2D
 **********************/
void VERTFILL2D(Word D)
{
  Word L, S, T, CB;

  /* GET 1D CAD STACK */
  L = L = LELTI(D,CHILD);
  if (L == NIL)
  {
    SWRITE("Must by a 2D CAD!\n");
    return;
  }

  /* LOOP OVER CELLS IN 1D CAD */
  for(; L != NIL; L = RED(L))
  {
    S = LELTI(FIRST(L),CHILD);

    /* Skip empty stacks */
    if (S == NIL)
      continue;
    
    /* Search for first TRUE cell in stack */
    for(T = S; T != NIL && LELTI(FIRST(T),TRUTH) != TRUE; T = RED(T));

    /* Bail if there are no TRUE cells, else CB is the first TRUE cell */
    if (T == NIL)
      continue;
    CB = FIRST(T);

    for(T = CINV(S); LELTI(FIRST(T),TRUTH) != TRUE; T = RED(T));
    while(FIRST(T) != CB) {
      SLELTI(FIRST(T),TRUTH,TRUE);
      T = RED(T); }
  }
}

/*
  D an ESPCAD
  F an FMA formula
  P the projection factor set to which C's signiture refers.
 */
#include "../extensions/sfext/espcad.h"
void PASSLINE(Word D, Word F, Word P)
{
  Word L, Lp, T, S;
  /* GET 1D CAD STACK */
  L = LELTI(D,SC_CDTV);
  if (!ISLIST(L))
  {
    SWRITE("Must by a 2D CAD!\n");
    return;
  }

  /* LOOP OVER CELLS IN 1D CAD UNTIL A TRUE CELL SATISFYING FORMULA IS FOUND*/
  for(Lp = L, T = NIL; Lp != NIL && T == NIL; Lp = RED(Lp))
  {
    S = LELTI(FIRST(Lp),SC_CDTV);

    /* Skip empty stacks */
    if (!ISLIST(S))
      continue;

    for(T = S; 
	T != NIL && (FMACELLEVAL(F,FIRST(T),P) != TRUE ||
		     LELTI(FIRST(T),SC_CDTV) != TRUE); T = RED(T));
  }

  if (Lp == NIL)
    return;

  /* LOOP LEFTOVER OVER CELLS IN IN REVERSE UNTIL A TRUE CELL SATISFYING FORMULA IS FOUND*/
  for(Lp = CINV(Lp), T = NIL; Lp != NIL && T == NIL; Lp = RED(Lp))
  {
    S = LELTI(FIRST(Lp),SC_CDTV);

    /* Skip empty stacks */
    if (!ISLIST(S))
      continue;


    for(T = S; 
	T != NIL && (FMACELLEVAL(F,FIRST(T),P) != TRUE ||
		     LELTI(FIRST(T),SC_CDTV) != TRUE); T = RED(T));
  }

  /* SET CELLS SATISFYING FORMULA IN BETWEEN TO TRUE */
  while(Lp != NIL)
  {
    S = LELTI(FIRST(Lp),SC_CDTV);

    /* Skip empty stacks */
    if (!ISLIST(S))
      continue;

    for(T = S; T != NIL; T = RED(T))
      if (FMACELLEVAL(F,FIRST(T),P) == TRUE)
	SLELTI(LELTI(FIRST(T),SC_REP),TRUTH,TRUE);       

    Lp = RED(Lp);
  }
}
