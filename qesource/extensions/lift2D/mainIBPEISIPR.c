/* 
gcc -o go mainIBPEISIPR.c IBPELBRISIPR.c -I$saclib/include $saclib/lib/saclibo.a
*/
#include "lift2d.h"

void SIPWRITE(Word *P, BDigit p, BDigit k)
{
  BDigit wii, i;
  wii = 2*(p + 3); // words in interval
  for(i = P[0]; i >= 0; i--)
  {
    SIDWRITE(P + 1 + i*wii,k);
    SWRITE(" x^");
    IWRITE(i);
    if (i > 0)
      SWRITE(" + ");
  }
}

int sacMain()
{
  Word V,B,t,Vx,M,L,Lp,i,k = 20;
  Word wii, p, J, *I , *Bp;
  
  /* Read bivariate polynomial */
  V = LIST2(LFS("x"),LFS("y"));
  SWRITE("Enter B, a polynomial in x and y : ");
  IPEXPREADR(2,V,&B,&t);
  if (!t) {
    SWRITE("Polynomial read unsuccessfull!\n");
    return 1; }
  else {
    SWRITE("Polynomial read in is: ");
    IPDWRITE(2,B,V);
    SWRITE("\n"); }

  /* Get precision */
  SWRITE("Enter precision: ");
  p = IREAD();
  SWRITE("Precision read is: ");
  IWRITE(p);
  SWRITE("\n");

  /* Read Interval */
  SWRITE("Enter binary rational interval: ");
  J = LBRIREAD();

  /* Sub! */
  Bp = GETARRAY(1 + (PDEG(B) + 1)*2*(p + 3));
  IBPELBRISIPR(B,J,p,Bp);
  SWRITE("Evaluation result is : ");
  SIPWRITE(Bp,p,k);
  SWRITE("\n");

  return 0;
}
