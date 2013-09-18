/*
Solution formula construction version 2
*/
#include "qepcad.h"

void QepcadCls::SFC2(Word D, Word P, Word J, Word n, Word sfm)
{
      Word t,SF,D0,P0,J0,D1,P1,Pp,Dp,Q,L,Lt,Lf;

Step1: /* Space is either empty or R^n. */
      t = DOPFSUFF(P,LIST1(D));
      if (t == TRUE) {       
	SF = LIST1(TRUE);  /* CAD is identically TRUE. */
	goto Step5; }
      else if (t == FALSE) {
	SF = LIST1(FALSE); /* CAD is identically FALSE. */
	goto Step5; }
      else if (t == NIL) {
	/* The CAD is not projection definable. */
	SWRITE("\n\nThis CAD is not projection definable.\n\n");
	CCADCON(n,P,D,&Pp,&Dp);
	Dp = PCAD2ESPCAD(P,Pp,Dp,NIL);
	LTFOCWTV(Dp,&Lt,&Lf);
	t = ACLOCK();
	Lt = SPCADCBDD(Lt,n);
	Q = NAIVESF(Lt,Lf,LISTOETA(Pp,n),Pp);
	t = ACLOCK() - t;
	SWRITE("\nNew NAIVESF took: "); IWRITE(t); SWRITE(" ms.\n");
	FMAWRITE(Q,Pp,GVVL);
	SWRITE("\n\n");	
	FMAWRITEp(Q,Pp,GVVL,0);
	SWRITE("\n\n");	
	t = ACLOCK();
	Lt = SPCADCBDD(Lt,n);
	Q = NECCONDS(Lt,Lf,LISTOETA(Pp,n),Pp);
	t = ACLOCK() - t;
	SWRITE("\nNew NECCONDS took: "); IWRITE(t); SWRITE(" ms.\n");
	FMAWRITE(Q,Pp,GVVL);
	SWRITE("\n\n");	
	FMAWRITEp(Q,Pp,GVVL,0);
	SWRITE("\n\n");	
	goto Return;
      }
      else {
	/* The CAD is projection definable. */
	P1 = P; D1 = D; }
      
Step2: /* Construct a simple ESPCAD for D, and 
          check projection definability. */
      CCADCON(n,P1,D1,&Pp,&Dp);
      Dp = PCAD2ESPCAD(P1,Pp,Dp,NIL);
      t = ESPCADDOPFSUFF(Pp,LIST1(Dp));

Step3: /* Put back some projection factors if needed. */
        if (t == NIL) {
          Q = MINPFSET(P1,Pp,D1,n);
          CCADCONFPFS(n,P1,D1,Q,&Pp,&Dp);
          Dp = PCAD2ESPCAD(P1,Pp,Dp,NIL); }
	
Step4: /* Construct formula. */
	LTFOCWTV(Dp,&Lt,&Lf);
	Lt = SPCADCBDD(Lt,n);
	L = LISTOTA(Pp,n);
	if (sfm == 1) {
	  SF = NECCONDS(Lt,Lf,L,Pp); }
	else {
	  SF = NAIVESF(Lt,Lf,L,Pp); }

Step5: /* Print Formula */
	SWRITE(" An equivalent formula is:\n");
	FMAWRITE(SF,Pp,GVVL);
        SWRITE("\n\n");
	SWRITE("In other words:\n");
        FMAWRITEp(SF,Pp,GVVL,0);
        SWRITE("\n\n");

 Return: /* Prepare to return. */
	return;
}
