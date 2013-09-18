/*======================================================================
                      sh <- CONVERT(s,k)

Convert to a primitive sample point.  
 
\Input 
   \parm{s} is a sample point of a cell c.
   \parm{k} is the level of the cell~\v{c}, \v{k} $\geq 1$.
 
\Output
   \parm{sh} is a primitive sample point for the cell c.
======================================================================*/
#include "qepcad.h"

Word QepcadCls::CONVERT(Word s, Word k)
{
       Word a,A,b,B,c,C,I,J,K,sh,t,T1,T2,u;

Step1: /* Already primitive. */
       if (ISPRIMIT(s)) {sh = s; goto Return;}

Step2: /* Get primitive element. */
       FIRST5(s,&B,&J,&A,&I,&c);
       SIMPLEQE(A,I,B,J,&C,&t,&u,&K,&a,&b,&T1,&T2);

Step3: /* Update statistics */
      TMNORMAL[k + 1] = TMNORMAL[k + 1] + T1;
      TMSIMPLE[k + 1] = TMSIMPLE[k + 1] + T2;
      NMCONVERT[k + 1] = NMCONVERT[k + 1] + 1;
      if (PDEG(A) == 1 || PDEG(B) == 1)
         {
         TMTCN[k + 1] = TMTCN[k + 1] + T2;
         NMTCONVERT[k + 1] = NMTCONVERT[k + 1] + 1;
         }

Step4: /* Convert coordinates. */
       if (u != 0) {MODCRDB(c,C,a,b,&c);}
       else c = CCONC(c,LIST1(b));
       sh = LIST4(C,K,c,s);

Return: /* Prepare for return. */
       return(sh);
}
