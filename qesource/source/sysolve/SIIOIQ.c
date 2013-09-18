/***************************************************************
Sign-invariance implies order-invariance query.

Inputs:
r  : a level
P  : a polynomial
ZL : a list of (a1, ..., am) of polynomials that are to be zero 
     (all of level  r)
NZ : a list of (b1, ...,bn) of polynomials that are to be non-zero 
     (all of level  r)
A  : the normalized assumptions formula

Output:
F  : a formula of level less than r that is a sufficient condition
     for P to have constant order = 1 in any region in which
     A /\ P = a1 = ... = am = 0 /\ b1 = 0 /\ ... /\ bn /= 0
***************************************************************/
#include "db/CAPolicy.h"

void GBTest(Word r, Word L, Word N, Word Vp)
{
  if (LENGTH(Vp) < r) { SWRITE("Not enough variables in GBTest!\n"); }
  Word F = GVCAP->IPFACTGB(r,L,N);
  SWRITE("\nSYSTEM:\n"); PRINTCOEFFSYS(r,LIST1(L),Vp); SWRITE("\n");
  SWRITE("\nGB's:\n");
  PRINTCOEFFSYS(r,F,Vp);
  SWRITE("\n");
    
}

void testSIimplOI(BDigit r, Word P, Word ZL, Word NZ, Word A)
{
  /* Compute generators A and all its 1st order partials */
  Word L = LIST1(A);
  for(int i = 1; i <= r; ++i)
  {
    Word D = IPDER(r,A,i);
    if (D != 0)
      L = COMP(D,L);
  } 
  L = CCONC(L,ZL);

  /* Compute a variable list for output purposes. */
  Word V = NIL;
  for(int i = r; i > 0; i--)
  {
    char s[2];
      s[0] = 'a' - 1 + i;
      s[1] = '\0';
      V = COMP(LFS(s),V);
  }

  /* Go through assumptions and find non-vanishing conditions. */
  Word M = NZ;
  SWRITE("Test si ==> oi: ");
  IPDWRITE(r,A,V);
  SWRITE("\n");
  GBTest(r,L,V);
}
