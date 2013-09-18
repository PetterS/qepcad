/*======================================================================
                     C <- ICSIGDIFFLNSC(A,a,k,K)

Incompatable cells signiture difference list.

Input:
 A : An array of length a.  Each entry of A is an array of length k.
     Every A[i][j] is an element of {-1,0,1}.  An element A[i][-1] is
     expected, the value of which should be TRUE = 1, FALSE = 0, or
     UNDET = 2.
 a : A non-negative BETA-Digit.
 k : A non-negative BETA-Digit.
 K : List of conflicitng cells.

Output:
 C : A list (c_1, ..., c_l) of subsets of {0, ... , k-1}.  For each
     pair m != n such that A[m][-1] != A[n][-1] there is a subset
     c_i which is defined as all the indices in {0,...,k-1} on which
     A[m] and A[n] differ.

======================================================================*/
#include "qepcad.h"
#define CFLCT 5

Word ICSIGDIFFLNSC(Word **A, Word a, Word k)
{
      Word T,F,U,C,i,kp,D,t,Fp,f,Up,u,Tp,L,l,lp,Lp;

Step1: /* Initialization. */
      T = NIL; F = NIL; U = NIL; L = NIL;
      for(i = 0; i < a; i++) {
        switch(A[i][-1]) {
        case (TRUE) : T = COMP(i,T); break;
        case (FALSE): F = COMP(i,F); break;
        case (UNDET): U = COMP(i,U); break;
	case (CFLCT): L = COMP(i,L); break; } }

Step2: /* Differences between each conflict cell, and each true, false,
	  conflict, or undetermined cell. */
      for(C = NIL; L != NIL; L = RED(L)) {
        l = FIRST(L);
        for(Lp = RED(L); Lp != NIL; Lp = RED(Lp)) {
          lp = FIRST(Lp); kp = k; D = NIL;
          while (kp-- > 0) { if (A[l][kp] != A[lp][kp]) D = COMP(kp,D); }
          C = COMP(D,C); }
        for(Tp = T; Tp != NIL; Tp = RED(Tp)) {
          t = FIRST(Tp); kp = k; D = NIL;
          while (kp-- > 0) { if (A[l][kp] != A[t][kp]) D = COMP(kp,D); }
          C = COMP(D,C); }
        for(Fp = F; Fp != NIL; Fp = RED(Fp)) {
          f = FIRST(Fp); kp = k; D = NIL;
          while (kp-- > 0) { if (A[l][kp] != A[f][kp]) D = COMP(kp,D); }
          C = COMP(D,C); }
        for(Up = U; Up != NIL; Up = RED(Up)) {
          u = FIRST(Up); kp = k; D = NIL;
          while (kp-- > 0) { if (A[l][kp] != A[u][kp]) D = COMP(kp,D); }
          C = COMP(D,C); } }

Step3: /* Differences between each true cell, and each false
          or undetermined cell. */
      for(; T != NIL; T = RED(T)) {
        t = FIRST(T);
        for(Fp = F; Fp != NIL; Fp = RED(Fp)) {
          f = FIRST(Fp); kp = k; D = NIL;
          while (kp-- > 0) { if (A[t][kp] != A[f][kp]) D = COMP(kp,D); }
          C = COMP(D,C); }
        for(Up = U; Up != NIL; Up = RED(Up)) {
          u = FIRST(Up); kp = k; D = NIL;
          while (kp-- > 0) { if (A[t][kp] != A[u][kp]) D = COMP(kp,D); }
          C = COMP(D,C); } }

Step4: /* Differences between each false cell and each 
          undetermined cell. */
      for(; F != NIL; F = RED(F)) {
        f = FIRST(F);
        for(Up = U; Up != NIL; Up = RED(Up)) {
          u = FIRST(Up); kp = k; D = NIL;
          while (kp-- > 0) { if (A[f][kp] != A[u][kp]) D = COMP(kp,D); }
          C = COMP(D,C); } }
      
Return: /* Prepare to return. */
      return (C);

}
