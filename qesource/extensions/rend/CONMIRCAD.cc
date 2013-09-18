/*===========================================================================
                        CONMIRCAD(D,P,J,M)

Construct "mirror" CAD

===========================================================================*/
#include "rend.h"

void CONMIRCAD(Word D,Word P,Word J,Rend_Cell& M, QepcadCls &Q)
{
  Word S,L,C,R;
  Word Sol,T,t,t1,t2,x1,y1,x2,y2; Word time;

Step1: /* Set up mirror CAD M. */
  M.initialize(NULL,AD2D_ErrI,0,D,P);

  time = ACLOCK();

Step2: /* Get the section-section adjacencies. */
  for(S = LELTI(D,CHILD),ADV(S,&L,&S); S != NIL; L = R) {
    ADV(S,&C,&S);
    ADV(S,&R,&S);
    Sol = Q.ADJ_2D_PART(C,L,R,P,J);
    // Sol = ADJ_2D1_COMPLETE(C,L,R,P,J);

    if (Sol == AD2D_FAIL) {
      SWRITE("Adjacency failed over cell ");
      OWRITE(LELTI(C,INDX));
      SWRITE("\n"); }
    else if (Sol == NIL)
    {
      ; //I think I can just ignore things!
    }
    else if (LENGTH(Sol) > 1) {
      SWRITE("Couldn't find unique adjacencies over ");
      OWRITE(LELTI(C,INDX));
      SWRITE("\n"); }
    else {
      //-- Loop over each adjacency and add it to mirror CAD M. --//
      T = FIRST(Sol);
      while(T != NIL)
      {
        ADV(T,&t,&T);
        FIRST2(t,&t1,&t2);
        FIRST2(t1,&x1,&y1);
        FIRST2(t2,&x2,&y2);

        if (x1 & 1)
          M[x1][y1].set_right(y2);
        else
          M[x2][y2].set_left(y1);
      }
    }
  }

  if (PCVERBOSE) {
    SWRITE("ADJ comp's took: ");
    IWRITE(ACLOCK() - time);
    SWRITE("ms\n"); }

Return: /* */
  return;
}
  
