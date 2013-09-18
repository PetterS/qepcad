#include "lift2d.h"

void modHIPRRID(BDigit n,interval *A, Word *L_,BDigit *t_);

Word sacMain()
{
  interval *A;
  Word P,t,L,n;

  SWRITE("Enter pol. in x: ");
  IPEXPREAD(1,LIST1(LFS("x")),&P,&t);
  CREAD();
  
  I = LBRIREAD();

 Step1: /* Convert the isolating interval for \alpha to a
	   hardware interval. */
  L = NIL;
  LBRNIEEEE(FIRST(I), &t,&F1,&n1);
  if (t != 0)
    goto Return;
  w1 = F1.num;
  LBRNIEEEE(SECOND(I), &t,&F2,&n2);
  if (t != 0)
    goto Return;
  w2 = F2.num;
  np = MIN(n1,n2);


 Step2: /* Convert the minimal polynomial to a hardware interval
	   polynomial and refine the hardware interval. */
  FPCATCH();
  IUPHIP(P,&A,&t);
  if (t == 0) {
    t = 1;
    goto Return; }
  n = PDEG(M);
  t = HIPFES(n,A,w2);
  if (FPCHECK() == 1) {
    t = 1;
    goto Return; }
  if (t == NIL) {
    t = 2;
	   goto Return; }
	u = 0;
	while (u == 0 && np > 0) {
	   p = (w1 + w2) / 2.0;
	   s = HIPFES(n,A,p);
	   if ((FPCHECK() == 1) || (s == NIL))
	      u = 1;
	   else if (s == t)
	      w2 = p;
	   else if (s == -t)
	      w1 = p;
	   else {
	      w1 = p;
	      w2 = p; }
	   np = np - 1; }
	K.left = w1;
	K.right = w2;



  HIPFES(PDEG(P),A,x);

  return 0;
}
