#include "lift2d.h"

void modHIPRRID(BDigit n,interval *A, Word *L_,BDigit *t_);

Word sacMain()
{
  interval *A;
  Word P,t,L,n;

  SWRITE("Enter pol. in x: ");
  IPEXPREAD(1,LIST1(LFS("x")),&P,&t);
  CREAD();

  
  IUPHIP(P,&A,&t);
  if (t)
    modHIPRRID(PDEG(P),A,&L,&t);
  if (t)
    SWRITE("failure!\n");
  else {
    OWRITE(L);
    SWRITE("\n"); }

  return 0;
}
