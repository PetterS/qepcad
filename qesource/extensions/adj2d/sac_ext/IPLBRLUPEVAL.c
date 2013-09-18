/*
Integral polynomial logarithmic binary rational linear
univariate polynomial evaluation.
*/

Word IPLBRLUPEVAL(Word r, Word A, Word a)
{

Step1: /* Special Cases. */
       if (A == 0) {
	 b = 0;
	 goto Return; }
       if (a == 0) {
	 b = PCFE(A,0);
	 goto Return; }

Step2: /* */
       a1 = PCFE(a,1);
       a0 = PCFE(a,0);
       FIRST2(a1,&f1,&s1);
       FIRST2(a0,&f0,&s0);
       if (s1 > s0) {
	 p = s1;
	 f0 = IMP2(f0,s1-s0); }
       else {
	 p = s0;
	 f1 = IMP2(f1,s0-s1); }
       
Step3: /* General Case. */
       Ap = A;
       rp = r - 1;
       ADV2(Ap,&d,&b,&Ap);
       n = d;
       while(Ap != NIL) {
	 ADV2(Ap,&i,&c,&Ap);
	 b1 = IPIP(rp,IEXP(f1,d - i),b);
	 b1 = PMPMV(b1,1);
	 b0 = IPIP(rp,IEXP(f0,d - i),b);
	 b = IPSUM(b1,b0);
	 if (p > 0)
	   b = IPSUM(rp,b,IPMP2(rp,c,p*(n-i))); /* b = b + c * 2^(p*(n-i)). */
	 else if (p < 0)
	   b = IPSUM(rp,IPMP2(rp,b,-p*(d-i)),c);
	 else
	   b = IPSUM(rp,b,c);
	 d = i;
       }
       
Step3: /* */
       
       b = IPIP(rp,IEXP(?,d),b);
       
Return: /* Prepare to return. */
       return b;
}
