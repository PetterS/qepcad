/*==========================================================================
                          B <- IPSQRT(r,A)

Integral polynomial square root.

Inputs
  r : a BETA-digit, r >= 0, the number of variables;
  A : in Z[X1,...,Xr].

Output
  B : in Z[X1,...,Xr].  If A has a square root then B is the positive
       or zero square root of A.  Otherwise, B = NIL.
==========================================================================*/
#include "saclib.h"

Word IPSQRT(r,A)
       Word r,A;
{
       Word B,B1,B1s,B1b,s,t,m,n,a,rp,b,Ap,bb,mp,np,ap,bp,C;

Step1: /* A <= 0? */
       if (A == 0) { 
	 B = 0; 
	 goto Return; }
       s = IPSIGN(r,A);
       if (s < 0) { 
	 B = NIL; 
	 goto Return; }

Step2: /* r == 0? */
       if (r == 0) { 
	 ISQRT(A,&B,&t); 
	 if (t != 0) 
	   B = NIL; 
	 goto Return; }

Step3: /* Compute leading term of B, if it exists. */
       m = PDEG(A);
       QREM(m,2,&n,&t); 
       if (t != 0) { 
	 B = NIL; 
	 goto Return; }
       a = PLDCF(A); 
       rp = r - 1; 
       b = IPSQRT(rp,a); 
       if (b == NIL) { 
	 B = NIL; 
	 goto Return; }
       B = PMON(b,n); 
       Ap = PRED(A);
  
Step4: /* Compute successive terms of B. */
       bb = IPIP(rp,2,b); 
       while (Ap != 0) {  
	 mp = PDEG(Ap);  
	 np = mp - n;
	 if (np < 0) { 
	   B = NIL; 
 	   goto Return; }
	 ap = PLDCF(Ap); 
	 if (rp > 0) 
	   IPQR(rp,ap,bb,&bp,&t);
	 else 
	   IQR(ap,bb,&bp,&t);
	 if (t != 0) { 
	   B = NIL; 
	   goto Return; }
	 B1 = PMON(bp,np);
	 B1b = IPIP(r,2,B1); 
	 C = IPPROD(r,B,B1b); 
	 B = IPSUM(r,B,B1);
	 B1s = IPPROD(r,B1,B1); 
	 C = IPSUM(r,C,B1s);
	 Ap = IPDIF(r,Ap,C); }
       
Return: /* Prepare for return. */
       return(B);
}
