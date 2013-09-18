/*======================================================================
                      CONSTRUCT(c,k,f,Ps,As)

Construct a stack.
 
\Input
    \parm{c}  is a candidate cell of~\v{D}.
    \parm{k}  is the level of the cell~\v{c}.
    \parm{f}  is the number of free variables in the input formula.
    \parm{P*} is the list of the $(k+1)$--level projection factors.
    \parm{A*} is the list of all the distinct $(k+1)$--level
              normalized input polynomials.
 
\Output
    A stack is constructed over the cell~\v{c}.
    If \v{A*} $\neq \emptyset$ or $k+1 \leq f$,
         the signature of \v{P*} on each cell in the stack is determined
         and attached to the cell.
======================================================================*/
#include "cad2d.h"

static Word Chrisolate(Word M, BDigit p)
{
  Word n,q1,q2,S,L;
  BDigit *Mp;

Step1: /* Convert the minimal polynomial to a software interval
          polynomial. */
        n = PDEG(M);
        q1 = p + 3;
        q2 = q1 + q1;
        S = (n + 1) * q2 + 1;
        Mp = GETARRAY(S);
        IPSIP(M,p,Mp);

Step2: /* Isolate roots! */
	L = SIPRRID(Mp);
	FREEARRAY(Mp);
	return L;
}

void QepcadCls2D::CONSTRUCT(Word c,Word k,Word f,Word Ps_,Word As)
{
        BDigit p,t,Ths;
        Word A1,As1,At,B,b,E,I,Ip,I1,J,Jp,L,M,P1,Ps1,Pt,Pt1,S,s,T,Q;
	Word junk,a1,b1,t1,p1,j1;

Step1: /* Extract the projection factors from their attribute lists. */
	Word Ps = Ps_;
       Pt = NIL;
       while (Ps != NIL)
         {
         ADV(Ps,&Ps1,&Ps);
         P1 = LELTI(Ps1,PO_POLY);
         Pt = COMP(P1,Pt);
         }
       Pt = INV(Pt);
       Ps = Pt;
       At = NIL;
       while (As != NIL)
         {
         ADV(As,&As1,&As);
         A1 = LELTI(As1,PO_POLY);
         At = COMP(A1,At);
         }
       At = INV(At);
       As = At;

Step2: /* Root cell. */
       if (k > 0) goto Step3;
    
                             /*Int*/ Ths = ACLOCK();
       SLELTI(c,DEGSUB,PLDEG(Ps));
       CONSTRUCT1(c,k,f,Ps_,As);
       goto Return;

Step3: /* Non-root cell, Irrational sample point. */
       s = LELTI(c,SAMPLE); FIRST3(s,&M,&J,&b);
       if (PDEG(M) == 1      
                             /*Int*/ && PCRSP == 'y'
          ) goto Step4;




       /******************************************/
       if (PCVERBOSE) {
	 SWRITE("\n\n");
	 SWRITE("Cell ");
	 OWRITE(LELTI(c,INDX)); }
       if (CELLSRRQ2D(c,GVPF) == TRUE) {
	 if (PCVERBOSE) {
	   SWRITE(" CELLSRRQ2D says ");
	   SWRITE("TRUE!\n"); }
	 if (LIFTSRR2D(c,GVPC,GVPF))
	   goto Return;
	 else
	   if (PCVERBOSE) SWRITE(" ... and CELLSRRQ2D FAILED!\n");
       }
       else if (CELLSRDQ2D(c,GVPF,&Q) == TRUE) {
	 if (PCVERBOSE) SWRITE(" CELLSRDQ2D says TRUE!\n");
	 if (LIFTSRD2D(c,GVPC,GVPF,Q))
	   goto Return;
	 else
	   if (PCVERBOSE) SWRITE(" ... and CELLSRDQ2D FAILED!\n");
       }
       else {
	 if (PCVERBOSE) SWRITE("Must have some multiple roots!\n");
       }	
       /******************************************/


    
                             /*Int*/ Ths = ACLOCK();
       S = SUBSTDB(c,k,M,b,Ps,*this);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMSUBST[k + 1] = TMSUBST[k + 1] + Ths;
                             /*Int*/ if (LSRCH('l',PCPROJOP) != 0 && LSRCH(0,S) != 0)
			       /*Int*/   FAIL("CONSTRUCT","Substitution failed",k,M,b,Ps,S);
       
       SLELTI(c,DEGSUB,PLDEG(S));
                             /*Int*/ Ths = ACLOCK();
       AFUPLM(M,S,&L,&T);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMAFUPLM[k + 1] = TMAFUPLM[k + 1]+Ths;

                          
                             /*Int*/ Ths = ACLOCK();
       AFCSBMDB(M,T,&B,&E);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMAFCSBM[k + 1] = TMAFCSBM[k + 1] + Ths;

        if (B != NIL) {
           if (PCAFUPBRI == 1) {
              Jp = BRILBRI(J);
              Ths = ACLOCK();
              AFUPHIBRI(M,Jp,B, &I,&t);
              Ths = ACLOCK() - Ths;
              TMAFUPHIBRI[k+1] = TMAFUPHIBRI[k+1] + Ths; 
              if (t == 0) {
                 Ip = I;
                 while (Ip != NIL) {
                    I1 = FIRST(Ip);
                    I1 = LBRIBRI(I1);
                    SFIRST(Ip,I1);
                    Ip = RED2(Ip); } }
              if (t != 0) {
		if (PCVERBOSE) {
		  SWRITE("AFUPHIBRI failed, t = ");
		  OWRITE(t);
		  SWRITE(", Ths = ");
		  IWRITE(Ths);
		  SWRITE("\n");
		  SWRITE("Cell index: ");
		  LWRITE(LELTI(c,6));
		  SWRITE("\n"); }
                 p = 2;
                 Jp = BRILBRI(J);
                 I = 0;
                 while (I == 0 && p <= 10) {
                    Ths = ACLOCK();
                    AFUPSIBRI(M,Jp,B,p, &Jp,&I);
                    Ths = ACLOCK() - Ths;
                    TMAFUPSIBRI[k+1] = TMAFUPSIBRI[k+1] + Ths;
		    if (PCVERBOSE) {
		      SWRITE("p = ");
		      IWRITE(p);
		      SWRITE(", Ths = ");
		      IWRITE(Ths);
		      SWRITE("\n"); }
                    p = p + 1; }
                 if (I == 0) {
                    Ths = ACLOCK();
                    I = AFUPBRI(M,J,B);
                    Ths = ACLOCK() - Ths;
		    if (PCVERBOSE) {
		      SWRITE("AFUPBRI time: ");
		      IWRITE(Ths);
		      SWRITE("\n"); }
                    TMAFUPBRI[k+1] = TMAFUPBRI[k+1] + Ths; } } }
              else {
                 Ths = ACLOCK();
                 I = AFUPBRI(M,J,B);
                 Ths = ACLOCK() - Ths;
                 TMAFUPBRI[k+1] = TMAFUPBRI[k+1] + Ths; } }
        else
           I = NIL;
                             /*Int*/ Ths = ACLOCK();
       EC(c,I,E,B);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMEC[k + 1] = TMEC[k + 1] + Ths;
                             /*Int*/ Ths = ACLOCK();
       SIGNP(c,k,B,I,E,L);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMSIGNP[k + 1] = TMSIGNP[k + 1] + Ths;
                             /*Int*/ NMSTACK[k + 1] = NMSTACK[k + 1] + 1;
                             /*Int*/ NMCELL[k + 1] = NMCELL[k + 1] + LENGTH(LELTI(c,CHILD)); 
       goto Return;

Step4: /* Non-root cell, Rational sample point. */
                             /*Int*/ Ths = ACLOCK();
       b = RCFAFC(b);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMRCFAFC[k + 1] = TMRCFAFC[k + 1] + Ths;
                          
                             /*Int*/ Ths = ACLOCK();
       S = SUBSTR(c,k,b,Ps);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMSUBSTR[k + 1] = TMSUBSTR[k + 1] + Ths;
                             /*Int*/ if (LSRCH('l',PCPROJOP) != 0 && LSRCH(0,S) != 0)
                             /*Int*/   FAIL("CONSTRUCT","Substitution failed",k,M,b,Ps,S);
       SLELTI(c,DEGSUB,PLDEG(S));
                          
                             /*Int*/ Ths = ACLOCK();
       IPLSRP(S,&s,&T);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMIPLSRP[k + 1] = TMIPLSRP[k + 1] + Ths;
                          
                             /*Int*/ Ths = ACLOCK();
       IPFSBM(1,T,&B,&E);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMIPFSBM[k + 1] = TMIPFSBM[k + 1] + Ths;
                          
                             /*Int*/ Ths = ACLOCK();
       if (B != NIL) I = IPLRRI(B); else I = NIL;
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMIPLRRI[k + 1] = TMIPLRRI[k + 1] + Ths;
                          
                             /*Int*/ Ths = ACLOCK();
       ECR(c,I,E,B);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMECR[k + 1] = TMECR[k + 1] + Ths;
                          
                             /*Int*/ Ths = ACLOCK();
       SIGNPR(c,k,B,I,E,s);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMSIGNPR[k + 1] = TMSIGNPR[k + 1] + Ths;
                             /*Int*/ NMSTACK[k + 1] = NMSTACK[k + 1] + 1;
                             /*Int*/ NMSTACKR[k + 1] = NMSTACKR[k + 1] + 1;
                             /*Int*/ NMCELL[k + 1] = NMCELL[k + 1] +  LENGTH(LELTI(c,CHILD));

Return: /* Prepare for return. */
       return;
}




