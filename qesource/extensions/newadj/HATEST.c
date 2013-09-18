#include "newadj2D.h"
Word ISSECTOR(Word C) { return LAST(LELTI(C,INDX)) % 2; }
void SAMPLECWR(Word c);
void strippedAFLWR(Word M,Word I,Word N,Word a,Word A);
void ANDWRITExx(Word M,Word I,Word n);
void RNDWRITExx(Word R,Word n);
void AFDWRITE(Word M, Word I, Word b, Word n);

/*
  D = GVPC;
  P = GVPF;
  J = GVPJ;
*/
void HATEST(Word D, Word P, Word J)
{
  Word k,Q,c1,c2,A,L,Q2;

  L = NIL;
  Q2 = NIL;

  SWRITE("Are base cells 1-level or 2-level? ");
  if (IREAD() == 2)
    k = 1;
  else
    k = 0;

  for(Q = LIST1(D); Q != NIL; Q = RED(Q)) {

    c1 = FIRST(Q);
    if (c1 == NIL) continue;

    if (LELTI(c1,LEVEL) <= k)
      Q = CCONC(Q,LELTI(c1,CHILD));

    if (LELTI(c1,LEVEL) == k)
      Q = CCONC(Q,LIST1(NIL));
      
    if (LELTI(c1,LEVEL) > k) {
      Q2 = CCONC(LELTI(c1,CHILD),Q2);
      c2 = SECOND(Q);
      A = AD2D_FAIL;
      if (ISSECTOR(c1) && c2 != NIL)
	A = HA(c2,c1,P,J,D);
      if (!ISSECTOR(c1))
	A = HA(c1,c2,P,J,D);
      SWRITE("Cell");OWRITE(LELTI(c1,INDX));SWRITE(" Adj's: ");
      if (A == AD2D_FAIL || LENGTH(A) > 1)
	SWRITE("FAIL");
      else {
	OWRITE(FIRST(A));
	L = CCONC(FIRST(A),L);
      }
      SWRITE("\n"); } }

  SWRITE("\n\n");
  while(Q2 != NIL) {
    OWRITE(LELTI(FIRST(Q2),INDX)); SWRITE(" "); SAMPLECWR(FIRST(Q2));
    Q2 = RED(Q2); }
  SWRITE("\n\n");
  while(L != NIL) {
    OWRITE(FIRST(L));
    SWRITE("\n");
    L = RED(L); }

  

  return;
}

/*===========================================================================
                         AFDWRITExx(M,I,b,n)

Algebraic number field, decimal write.  

Inputs
  M : integral minimal polynomial for a real algebraic number alpha.
  I : an acceptable isolating interval for alpha.
  b : an element of Q(alpha).
  n : non-negative integer.

Side effects
    A decimal approximation to b is written to the output stream.
    |b - R| < 1/2 10^{-n}.  
===========================================================================*/
#include "saclib.h"

void AFDWRITExx(Word M, Word I, Word b, Word n)
{
       Word J,N;

Step1: /* Convert to algebraic number and write. */
       ANFAF(M,I,b,&N,&J);
       ANDWRITExx(N,J,n);

Return: /* Prepare for return. */
       return;
}


/*======================================================================
                      SAMPLECWR(c)

Sample point coordinate write.

\Input
  \parm{c} is a cell whose sample point is to be written out
           to the output stream.
======================================================================*/
#include "saclib.h"
#include "qepcad.h"

void SAMPLECWR(Word c)
{
       Word I,Ip,M,Mp,b,bp,k,s,F,j,Ms,Is;
       Word M1;
       /* hide k; */

Step1: /* Setup. */
       s = LELTI(c,SAMPLE);
       k = LELTI(c,LEVEL);

Step2: /* Extended representation. */
       if (ISPRIMIT(s)) goto Step3;
       FIRST5(s,&M,&I,&Mp,&Ip,&bp);

       strippedAFLWR(Mp,Ip,LFS("Coordinate "),LFS("alpha"),bp);

       F = AFPNIP(Mp,M);  
       M = AFPICR(1,M);
       IPSRP(2,M,&M1,&M);
       AMUPMPR(Mp,Ip,M,I,F,&Is,&j);
       Ms = LELTI(F,j); 
       Is = IPSIFI(Ms,Is);  
       ANDWRITExx(Ms,Is,10);
       SWRITE("\n");
       goto Return;

Step3: /* Primitive representation. */
       FIRST3(s,&M,&I,&b);
       strippedAFLWR(M,I,LFS("Coordinate "),LFS("alpha"),b);  SWRITE("\n");

Return: /* Prepare for return. */
       return;
}

/*======================================================================
                      strippedAFLWR(M,I,N,a,A)

Algebraic number field elements list write.

\Input
  \parm{M} is a minimal polynomial for alpha.
  \parm{I} is the isolating interval for alpha.
  \parm{N} is the base name for the coordinates.
  \parm{a} is the variable name for the algebraic number alpha.
  \parm{A} is the list of elements of Q(alpha).
======================================================================*/
#include "saclib.h"
#include "qepcad.h"

void strippedAFLWR(Word M,Word I,Word N,Word a,Word A)
{
       Word A1,Ap,i,l,L,j;
       /* hide i; */

Step1: /* Write. */
       Ap = A;
       i = 0;
       while (Ap != NIL)
         {
         ADV(Ap,&A1,&Ap);
         i = i + 1;
         AFDWRITExx(M,I,A1,10); SWRITE(" ");
         }

Return: /* Prepare for return. */
       return;
}

/*===========================================================================
                         ANDWRITExx(M,I,n)

Algebraic number decimal write.  

Inputs
  M : an integral minimal polynomial for a real algebraic number alpha.
  I : an acceptable isolating interval for alpha.  
  n : a nonnegative integer.  

Side effects
     A decimal approximation R to alpha is written to the output stream.
     |alpha -  R| <=  1/2 10^{-n}.  The decimal approximation is followed
     by "+" if |R| < |alpha| and "-" if |R| > |alpha|.
===========================================================================*/
#include "saclib.h"

void ANDWRITExx(Word M, Word I, Word n)
{
       Word J,R,Mp,K;
       Word a,a1,a2,b,b1,b2,d,d1,d2,e,f,m;
       Word N;

Step1: /* Rational number. */
       if (PDEG(M) == 1) {
	  R = IUPRLP(M);  RNDWRITExx(R,n);  return; };

Step2: /* Interval approximation. */
       J = ISFPIR(M,I,n + 1);

Step3: /* 0 in J? */
       while (RISIGN(J) == NIL) J = IUPIIR(M,J);

Step4: /* Decimal approximation of interval endpoint. */
       FIRST2(J,&a,&b);
       N = IEXP(10,n);  
       if (RISIGN(J) > 0) {
	  FIRST2(a,&a1,&a2);
	  IQR(IPROD(a1,N),a2,&d1,&d2);
	  d = RNRED(d1,N);
	  e = RNSUM(d,LIST2(1,N));
	  f = RNSUM(e,LIST2(1,N)); }
       else {
	  FIRST2(b,&b1,&b2);
	  IQR(IPROD(b1,N),b2,&d1,&d2);  
	  f = RNRED(d1,N);
	  e = RNDIF(f,LIST2(1,N));  
	  d = RNDIF(e,LIST2(1,N)); }

Step5: /* Refine interval until e not in J */
       while ( RNCOMP(e,a) >= 0 && RNCOMP(e,b) <= 0) {
	  J = IUPIIR(M,J);
	  FIRST2(J,&a,&b); }
       if (RNCOMP(b,e) < 0)
	  K = LIST2(d,e);
       else
	  K = LIST2(e,f);

Step6: /* determine which half alpha belongs to. */
       FIRST2(K,&d,&e);
       m = RNQ(RNSUM(d,e),RNINT(2));
       while (RNCOMP(m,a) >= 0 && RNCOMP(m,b) <= 0) {
	  J = IUPIIR(M,J);
	  FIRST2(J,&a,&b); }
       if (RNCOMP(b,m) < 0) {
	  RNDWRITExx(d,n);
       }
       else {
	  RNDWRITExx(e,n);
       }

Return: /* Prepare for return. */
       return;
}

/*======================================================================
                      RNDWRITExx(R,n)

Rational number decimal write. 

Inputs
  R : a rational number.  
  n : a non-negative BETA-digit.  

Side effects
  R is approximated by a decimal fraction d with n decimal digits 
  following the decimal point and d is written in the output stream.  
  The inaccuracy of the approximation is at most (1/2)*10^-n.  
  If abs(d) is greater than abs(R) then the last digit is followed by a minus sign, 
  if abs(d) is less than abs(R) then by a plus sign.
======================================================================*/
#include "saclib.h"

void RNDWRITExx(Word R, Word n)
{
       Word A,B,D,F,M,d,i,s,t;
       /* hide B,d,i,s,t; */

Step1: /* Compute approximation. */
       if (R == 0)
         {
         A = 0;
         B = 1;
         }
       else
         FIRST2(R,&A,&B);
       s = ISIGNF(A);
       if (s < 0)
         A = INEG(A);
       M = IEXP(10,n);
       A = IPROD(A,M);
       IQR(A,B,&D,&F);
       F = IDPR(F,2);
       if (F == 0)
         t = 0;
       else
         {
         t = ICOMP(B,F);
         if (t == 0)
           t = 1;
         else
           if (t < 0)
             D = ISUM(D,1);
         }

Step2: /* Convert and write. */
       if (s < 0)
         CWRITE('-');
       IQR(D,M,&D,&F);
       IWRITE(D);
       CWRITE('.');
       for (i = 1; i <= n; i++)
         {
         F = IDPR(F,10);
         IQR(F,M,&d,&F);
         CWRITE(d + '0');
         }

Return: /* Prepare for return. */
       return;
}
