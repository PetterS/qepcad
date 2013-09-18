/* 
gcc -o go mainIBPRRIOAP.c IBPRRIOAP.c -I$saclib/include $saclib/lib/saclibo.a
*/
#include "lift2d.h"

int sacMain()
{
  Word V,B,t,Vx,M,I,L,Lp,i,k;
  
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

  /* Read minimal polynomial M */
  Vx = LIST1(LFS("x"));
  SWRITE("Enter M, a polynomial in x (the minimal polynomial): ");
  IPEXPREADR(1,Vx,&M,&t);
  if (!t) {
    SWRITE("Polynomial read unsuccessfull!\n");
    return 1; }
  else {
    SWRITE("Polynomial read in is: ");
    IPDWRITE(1,M,Vx);
    SWRITE("\n"); }

  /* Read isolating interval for root alpha of minimal polynomial */
  SWRITE("Enter logarithmic binary rational standard interval isolating a root of M: ");
  I = LBRIREAD();
  SWRITE("Interval read is: ");
  LBRIWRITE(I);
  SWRITE("\n");

  /* Get target precision */
  SWRITE("Enter target precision: ");
  k = IREAD();
  SWRITE("Target precision read is: ");
  IWRITE(k);
  SWRITE("\n");

  /* Isolate roots of B(alpha,y) */
  IBPRRIOAP(M,I,B,k,&L,&t);
  for(Lp = L; Lp != NIL; Lp = RED(Lp)) {
    LBRIWRITE(FIRST(Lp));
    SWRITE("\n"); }
    
  SWRITE("\n");

  return 0;
}
