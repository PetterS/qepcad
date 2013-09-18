/*======================================================================
                      PRODWR(v)

Product Write.

\Input
  \parm{v} is a product.
======================================================================*/
#include "qepcad.h"

void PRODWR(Word v)
{
       Word I,I1,P1,P11,Pp,R1,W,W1,i,j,n1,v1,vp;
       /* hide i,j,n1; */

       SWRITE("In \"PRODWR\"! This is dead code!\n"); exit(1);

Step1: /* Setup. */
/*        I = NIL; Pp = GVPF; */
/*        for (i = 1; i <= GVNFV; i++) */
/*          { */
/*          ADV(Pp,&P1,&Pp); */
/*          n1 = LENGTH(P1); */
/*          for (j = 1; j <= n1; j++) */
/*            { */
/*            ADV(P1,&P11,&P1); */
/*            I = COMP(LIST2(i,j),I); */
/*            } */
/*          } */
/*        I = INV(I); */

Step2: /* Preprocess. */
       W = NIL; vp = v;
       while (vp != NIL)
         {
         ADV(vp,&v1,&vp); ADV(I,&I1,&I);
         switch (v1)
           {
           case GEOP: { W1 = LIST2(I1,LFS(">=")); W = COMP(W1,W); } break;
           case LEOP: { W1 = LIST2(I1,LFS("<=")); W = COMP(W1,W); } break;
           case NEOP: { W1 = LIST2(I1,LFS("/=")); W = COMP(W1,W); } break;
           case GTOP: { W1 = LIST2(I1,LFS(">")); W = COMP(W1,W); } break;
           case LTOP: { W1 = LIST2(I1,LFS("<")); W = COMP(W1,W); } break;
           case EQOP: { W1 = LIST2(I1,LFS("=")); W = COMP(W1,W); } break;
           }
         }
       W = INV(W);

Step3: /* Write. */
       while (W != NIL)
         {
         ADV(W,&W1,&W);
         FIRST2(W1,&I1,&R1);
         LABELWR(LFS("P"),I1); SWRITE(" "); CLOUT(R1); SWRITE(" 0");
         if (W != NIL) SWRITE(" /\\ ");
         }
       goto Return;

Return: /* Prepare for return. */
       return;
}
