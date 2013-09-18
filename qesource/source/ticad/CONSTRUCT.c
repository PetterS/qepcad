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
#include "qepcad.h"

Word IUPSBRRI(Word B, BDigit k);

void QepcadCls::CONSTRUCT(Word c, Word k, Word f, Word Ps_, Word As)
{
        BDigit p,t,Ths;
        Word B,b,E,I,Ip,I1,J,Jp,L,M,Ps,P1,Ps1,S,s,T,Q;
	Word junk,a1,b1,t1,p1,j1;

Step0: /* Root cell. */
	if (k == 0) { CONSTRUCT1(c,k,f,Ps_,As); goto Return; }
	  

Step1: /* Extract the projection factors from their attribute lists. */
       Ps = NIL;
       for(Word Pt = CINV(Ps_); Pt != NIL; Pt = RED(Pt))
       {
         Word Pt1 = FIRST(Pt);
	 if (LELTI(Pt1,PO_TYPE) == PO_POINT)
	   junk = 1;
	 else
	   Ps = COMP(LELTI(Pt1,PO_POLY),Ps);
       }


Step3: /* Non-root cell, Irrational sample point. */
       s = LELTI(c,SAMPLE); FIRST3(s,&M,&J,&b);
       if (PDEG(M) == 1      
                             /*Int*/ && PCRSP == 'y'
          ) goto Step4;

    
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
#ifdef _QEVERBOSE
                 SWRITE("AFUPHIBRI failed, t = ");
                 OWRITE(t);
                 SWRITE(", Ths = ");
                 IWRITE(Ths);
                 SWRITE("\n");
                 SWRITE("Cell index: ");
                 LWRITE(LELTI(c,6));
                 SWRITE("\n");
#endif
                 p = 2;
                 Jp = BRILBRI(J);
                 I = 0;
                 while (I == 0 && p <= 10) {
                    Ths = ACLOCK();
                    AFUPSIBRI(M,Jp,B,p, &Jp,&I);
                    Ths = ACLOCK() - Ths;
                    TMAFUPSIBRI[k+1] = TMAFUPSIBRI[k+1] + Ths;
#ifdef _QEVERBOSE
                    SWRITE("p = ");
                    IWRITE(p);
                    SWRITE(", Ths = ");
                    IWRITE(Ths);
                    SWRITE("\n");
#endif
                    p = p + 1; }
                 if (I == 0) {
                    Ths = ACLOCK();
                    I = AFUPBRI(M,J,B);
                    Ths = ACLOCK() - Ths;
#ifdef _QEVERBOSE
                    SWRITE("AFUPBRI time: ");
                    IWRITE(Ths);
                    SWRITE("\n");
#endif
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
       /* if (B != NIL) I = IUPSBRRI(B,-10); else I = NIL; */
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

/* CONSTRUCT1 comparison of root structure.

   Input:
     A,B: lists of the form (P,I,(o1,o2,...,ok)) where 
          P is uni,sqrfree,prim,irred poly, I is a standard binary rational interval,
          and the oi's are projection objects.

   Note:  These are isolating intervals, so each contains exactly one root
          of the given polynomial.  Moreover, they're standard binary rational intervals
          so if they overlap, it actually means that one is contained in the other.
*/

BDigit C1COMPd(Word A, Word B) /* C1COMPd(A,B) requires that A & B have different pol's*/
{
  Word PA,PB,IA,IB;

  /* Immediate decision */
  FIRST2(A,&PA,&IA);
  FIRST2(B,&PB,&IB);
  if (RNCOMP(SECOND(IA),FIRST(IB)) <= 0) return -1;
  if (RNCOMP(SECOND(IB),FIRST(IA)) <= 0) return 1;

  /* Determine widths of isolating intervals */
  Word wA = LSILW(BRILBRI(IA));
  Word wB = LSILW(BRILBRI(IB));
  
  /* Refine and compare until a decision is made */
  while(true) {
    if (wA > wB) { IA = IUPIIR(PA,IA); wA--; }
    else         { IB = IUPIIR(PB,IB); wB--; }
    if (RNCOMP(SECOND(IA),FIRST(IB)) <= 0) return -1;
    if (RNCOMP(SECOND(IB),FIRST(IA)) <= 0) return 1;    
  }

}

BDigit C1COMP(Word A, Word B)
{
  Word PA,PB,IA,IB;
  FIRST2(A,&PA,&IA);
  FIRST2(B,&PB,&IB);
  if (EQUAL(PA,PB)) {
    if (EQUAL(IA,IB)) return 0;
    if (RNCOMP(SECOND(IA),FIRST(IB)) <= 0) return -1;
    if (RNCOMP(SECOND(IB),FIRST(IA)) <= 0) return 1;
    else return 0;
  }
  else
    return C1COMPd(A,B);
    
}


/* Root cell. */
void QepcadCls::CONSTRUCT1(Word c, Word k, Word f, Word Ps_, Word As)
{
        BDigit p,t,Ths;
        Word B,b,E,I,Ip,I1,J,Jp,L,M,Ps,P1,Ps1,S,s,T,Q,Pp;
	Word junk,a1,b1,t1,p1,j1;

Step1: /* Extract the projection factors from their attribute lists. */
	Ps = NIL; /* Basis for real-root isolation - i.e. the polynomials */
	Pp = NIL; /* Points to be added */
	for(Word Pt = CINV(Ps_); Pt != NIL; Pt = RED(Pt))
	{
	  Word Pt1 = FIRST(Pt);
	  if (LELTI(Pt1,PO_TYPE) == PO_POINT) {
	    Word s = FIRST(LELTI(Pt1,PO_POLY));
	    /* Set p to the minimal polynomial for the root */
	    Word p = LIST3(FIRST(s),SECOND(s),LIST1(Pt1));
	    if (PDEG(FIRST(s)) == 1) {
	      Word R = FIRST(FIRST(THIRD(s)));
	      if (R == 0) p = LIST3(LIST2(1,1),LIST2(0,0),LIST1(Pt1));
	      else {
		Word q = LIST4(1,SECOND(R),0,INEG(FIRST(R)));
		Word I = FIRST(IPRIM(q));
		p = LIST3(q,I,LIST1(Pt1));
	      }
	    }
	      Pp = COMP(p,Pp);
	  }   
	  else
	    Ps = COMP(LELTI(Pt1,PO_POLY),Ps);
	}

 Step2: /* Isolate roots and create stack. */
                             /*Int*/ Ths = ACLOCK();
       SLELTI(c,DEGSUB,PLDEG(Ps));

       /* Compute roots of polynomials */
       if (Ps != NIL) {
 	 I = IUPSBRRI(Ps,-10); /* I = IPLRRI(Ps); */
       }
       else 
	 I = NIL;
       /* Transform I into a list of pairs (P,I,L_O) where P is the minpol,
	  I is the interval, and L_O is a list of projeciton objects */
       { 
	 Word T = NIL;
	 for( ; I != NIL; I = RED2(I))
	 {
	   Word p = SECOND(I);
	   Word Pt = CINV(Ps_);
	   while(LELTI(FIRST(Pt),PO_TYPE) == PO_POINT || !EQUAL(LELTI(FIRST(Pt),PO_POLY),p))
	     Pt = RED(Pt);
	   
	   T = COMP(LIST3(p,FIRST(I),LIST1(FIRST(Pt))),T);
	 }
	 I = CINV(T);
       }
       
       /* Merge point information */
       for(Word Ppp = Pp; Ppp != NIL; Ppp = RED(Ppp))
       {
	 Word p = FIRST(Ppp);
	 
	 Word H = NIL;
	 while(1) {
	   if (I == NIL) { I = CCONC(CINV(H),LIST1(p)); break; }
	   Word t = C1COMP(p,FIRST(I));
	   if (t == -1) { I = CCONC(CINV(H),COMP(p,I)); break; }
	   if (t == 0) { 
	     Word x = THIRD(FIRST(I)); 
	     SLELTI(FIRST(I),3,CCONC(x,THIRD(p))); 
	     I = CCONC(CINV(H),I); 
	     break; }
	   H = COMP(FIRST(I),H);
	   I = RED(I);
	 }
	 
       }
       
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMIPLRRI[k + 1] = TMIPLRRI[k + 1] + Ths;
                          
                             /*Int*/ Ths = ACLOCK();
       EC1(c,I,Ps);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMECR[k + 1] = TMECR[k + 1] + Ths;
                          
                             /*Int*/ Ths = ACLOCK();
       SIGNP1(c,Ps_,I);
                             /*Int*/ Ths = ACLOCK() - Ths;
                             /*Int*/ TMSIGNPR[k + 1] = TMSIGNPR[k + 1] + Ths;
                             /*Int*/ NMSTACK[k + 1] = NMSTACK[k + 1] + 1;
                             /*Int*/ NMSTACKR[k + 1] = NMSTACKR[k + 1] + 1;
                             /*Int*/ NMCELL[k + 1] = NMCELL[k + 1] + LENGTH(LELTI(c,CHILD));
    
       goto Return;

Return: /* Prepare for return. */
       return;
}



/*
Integral univariate polynomial squarefree basis real-root isolation and interval refinement
B : the basis
p : the starting software precision
k : the desired interval width
Output
R : either 0 (indicating failure) or a list of roots 
    (I1,B1,...,Im,Bm), where I1 < I2 < ... < Im 

Note: This would be tremendously improved by recognizing exact binary rational roots of
      all elements of B, not just the linear elements!
*/
Word IUPSBRRIIR(Word t_B, BDigit p, BDigit k)
{

  /* Get software versions of the elements of B, and isolate their roots */
  bool fail = false;
  Word L = NIL, M = NIL, R = NIL;
  BDigit N = LENGTH(t_B);
  BDigit **C = new BDigit*[N + 1]; for(int i = 0; i < N + 1; ++i) C[i] = 0;

  for(Word B = t_B, i = 1; B != NIL; B = RED(B),++i)
  {  
    Word b = FIRST(B);
    Word n = PDEG(b);
    C[i] = new Word[(n+1)*(2*p+6)+1];
    IPSIP(b,p,C[i]);
    Word Li = 0;

    /* If we have a linear polynomial defining a binary rational number, compute root eactly! */
    if (n == 1) {
      Word den = PLDCF(b), num = PCOEFF(b,0), lm, ln;
      if (num == 0)
	Li = LIST1(LIST2(0,0));
      else {
	IFCL2(den,&lm,&ln);
	if (ICOMP(lm,ln) == 0) { 
	  Word x = RNLBRN(RNRED(INEG(num),den));
	  Li = LIST1(LIST2(x,x)); } }
    }

    /* Otherwise, isolate using floating-point routines */
    if (Li == 0)
      Li = SIPRRID(C[i]);

    if (Li == 0) { fail = true; goto Return; }

    for(BDigit t = (n%2==1 ? 1 : -1); Li != NIL; t *= -1, Li = RED(Li)) {
      Word I = FIRST(Li), i1, i2;
      Word J = SIPIR(C[i],I,t,k);
      L = COMP(LIST3(i,J,t),L);
    }
  }

  /* Sort and refine roots */
  M = SIPIIRMS(L,C);
  if (M == 0) { fail = true; /* SWRITE("failed in merge!\n"); */ goto Return; }

  /* Make returned list */
  R = NIL;
  for(Word Mp = CINV(M); Mp != NIL; Mp = RED(Mp))
  {
    Word i, I, t;
    FIRST3(FIRST(Mp),&i,&I,&t);
    R = COMP2(I,LELTI(t_B,i),R);
  }

Return: /* Prepare to return! */
  for(int i = 1; i <= N; ++i) delete [] C[i];
  delete [] C;
  if (fail) R = 0;
  return R;
}

/*
Integral univariate polynomial squarefree basis real-root isolation
same specs as IPLRRI(L), except it target root intervals with
width 2^k.
*/
Word IUPSBRRI(Word B, BDigit k)
{
  Word L = NIL;
  
  /* Get the roots */
  const BDigit P = 64; // The current limit on how far I'll go in software interval computations
  Word R = 0;
  for(BDigit p = 1; R == 0 && p <= P; p *= 2) {
    R = IUPSBRRIIR(B,p,k);
    if (PCVERBOSE && R != 0) { SWRITE("Required precision "); IWRITE(p); SWRITE("!\n"); }
  }
  if (PCVERBOSE && R == 0) { SWRITE("Exceeded precision limit & switched to exact!\n"); }

  /* If successfull, translate from logarithmic to non-logarithmic intervals */
  if (R != 0) {
    for(Word Rp = CINV(R); Rp != NIL; Rp = RED2(Rp))
    {
      Word A, I, a, b;
      FIRST2(Rp,&A,&I);
      FIRST2(I,&a,&b);
      L = COMP2(LIST2(LBRNRN(a),LBRNRN(b)),A,L);
    } }

  /* If unsuccessfull switch to exact! */
  else {
    L = IPLRRI(B);
  }
  
  return L;
}
