/*======================================================================
                         S <- SYSSOLVECAD(r,L,A,Vp;Q)

System solve by directly applying CAD

Input
 r : the level
 L : a list of r-variate polynomials (the system)
 A : the normalized assumptions formula
 Vp: the variable list to use for any printing 

Output
 Q : is a brand spanking new CAD which this sets to the
     decomposition created while solving the system
 S : 0 if there are infintely many real solutions
     to the system, otherwise a list of all solutions in
     the form of cells from Q.
                   
======================================================================*/
#include "qepcad.h"

Word SYSSOLVECAD(BDigit r, Word L, Word A, Word Vp, QepcadCls &Q)
{
  Word F, Fp, d, t, Lt, Lf, V, S;

  /* Set variable list */
  if (LENGTH(Vp) < r) {
    V = NIL;
    for(int i = r; i > 0; i--)
    {
      char s[2];
      s[0] = 'a' - 1 + i;
      s[1] = '\0';
      V = COMP(LFS(s),V);
    }
  }
  else
    V = Vp;

  /* Create a CAD representing the solutions of the system */
  F = SYSTOUNNORMFORMULA(r,L);
  Q.SETINPUTFORMULA(V,LIST4(r,r,NIL,F));
  Q.SETASSUMPTIONS(A);
  Q.CADautoConst();

  /* List solution points */
  S = NIL;
  for(LISTOFCWTV(Q.GVPC,&Lt,&Lf); Lt != NIL && S != 0; Lt = RED(Lt))
  {  
    Word dc = CELLDIM(FIRST(Lt)) + r - LELTI(FIRST(Lt),LEVEL);
    if (dc == 0)
      S  = COMP(FIRST(Lt),S);
    else
      S = 0;
  }

  /* Prepare to return */
  return S;
}
