/*======================================================================
                      c <- CHSECTSAMP(a,b)

Choose sector sample point.

Inputs:
 a : a binary rational number or the Word -1.
 b : a binary rational number or the Word 1.
 Note: If a doesn't have Word value -1 and b doesn't have Word 
       value 1 then a <= b.
Outputs
 c : a binary rational number.
     if a = Word -1 and b = Word 1 then c is zero.
     if a = Word -1 and b is binary rational, then c = floor(b) - 1.
     if a is binary rational and c is Word 1, then c = ceil(a) + 1.
     if both a and b are binary rational then let [x,y] be the 
        interval of width (b - a)/2 centered at the midpoint of (a,b);
        c is set to the binary rational in [x,y] with smallest 
        numerator.
======================================================================*/

Word CHSECTSAMP(Word a, Word b)
{
  Word cp,c,A,B,C,X,Y,t,x,y,i,j,k,F,G,H,p,T;

Step1: /* No Sections: a = -1 and b = 1. */
  if (a == -1 && b == 1) {
    c = 0;
    goto Return; }

Step2: /* First Sector: a = -1 and b a binary rational. */
  if (a == -1) {
    c = RNINT(IDIF(RNFLOR(b),1));
    goto Return; }

Step3: /* Last Sector: a binary rational and b = 1. */
  if (b == 1) {
    c = RNINT(ISUM(RNCEIL(a),1));
    goto Return; }

Step4: /* Interesting case:  both binary rational. */
  A = RNLBRN(a); 
  B = RNLBRN(b);
  C = LBRIMID(LIST2(A,B));

Step5: /* Construct (X,Y), the interval centered at |C| with
half the width of interval (A,B). */
  X = LBRIMID(LIST2(A,C));
  Y = LBRIMID(LIST2(C,B));
  t = LBRNSIGN(X);
  if (t*LBRNSIGN(Y) <= 0) {
    c = 0;
    goto Return; }
  if (t == -1) {
    T = X;
    X = LBRNNEG(Y);
    Y = LBRNNEG(T); }

Step6: /*  Construct c. */
  FIRST2(X,&x,&i);
  FIRST2(Y,&y,&j);
  if (i > j) {
    k = i;
    F = x;
    G = IMP2(y,i - j); }
  else {
    k = j;
    F = IMP2(x,j - i);
    G = y; }
  p = IFDBIT(F,G);
  C = LBRNFIE(ITRUNC(G,p-1),-(k - (p-1)));
  if (t == -1)
    C = LBRNNEG(C);
  c = LBRNRN(C);

Return: /* Return c. */
  c = CSSP((a == -1 ? NIL : a), (b == 1 ? NIL : b) );

  return c;

}
