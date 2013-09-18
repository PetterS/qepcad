/*======================================================================
                      CHSCN(M,I,N,J,t,S; S1,K1)

Choose the right Conjugate.

\Input
  \parm{M} 
  \parm{I} 
  \parm{N}  
  \parm{J}  
  \parm{t}   
  \parm{S}  

\Output
  \parm{S1}
  \parm{K1}
======================================================================*/
#include "qepcad.h"

void CHSCN(Word M, Word I, Word N, Word J, Word t, Word S, Word *S1_, Word *K1_)
{
       Word K1,S1,kp;
       /* hide kp; */

Step1: /* Choose. */
        ANIIPE(M,I,N,J,t,S,&S1,&kp,&K1);
        K1 = IPSIFI(S1,K1);
        goto Return;

Return: /* Prepare for return. */
       *S1_ = S1;
       *K1_ = K1;
       return;
}
