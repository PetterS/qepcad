/*======================================================================
                      DSTATWR()

Dissertation Statistics Write.
======================================================================*/
#include "qepcad.h"

void QepcadCls::DSTATWR()
{
       Word N_c,N_f,N_j,N_s,T,T_c,T_p,i,r;
       /* hide N_c,N_f,N_j,N_s,T,T_c,T_p,i,r; */

Step1: /* Prepare. */
       r = GVNV;
       T_p = 0; for (i = 1; i <= r - 1; i++) T_p = T_p + TMPROJECT[i];
       N_f = 0; for (i = 1; i <= r; i++) N_f = N_f + NMPF[i];
       N_j = 0; for (i = 1; i <= r - 1; i++) N_j = N_j + NMPJ[i];
       T_c = 0; for (i = 1; i <= r; i++) T_c = T_c + TMTICAD[i];
       N_s = 0; for (i = 1; i <= r; i++) N_s = N_s + NMSTACK[i];
       N_c = 0; for (i = 1; i <= r; i++) N_c = N_c + NMCELL[i];
       T = TMNORMQFF + T_p + T_c + TMSOLUTION + TAU;

Step2: /* Write. */
       SWRITE("--------------Dissertation Statistics -----------------\n");
       SWRITE("@\n");

       GWRITE(NMATOM); SWRITE("\n");

       GWRITE(T); SWRITE("\n");

       GWRITE(TMNORMQFF); SWRITE("\n");

       GWRITE(N_j); SWRITE("\n");
    
       GWRITE(N_f); SWRITE("\n");

       GWRITE(T_p); SWRITE("\n");

       GWRITE(NMPF[r]); SWRITE("\n");
    
       for (i = r - 1; i >= 1; i--)
         {
         GWRITE(NMPJ[i]); SWRITE("\n");
      
         GWRITE(NMPF[i]); SWRITE("\n");
      
         GWRITE(TMPROJECT[i]); SWRITE("\n");
         }
         
       GWRITE(N_s); SWRITE("\n");

       GWRITE(N_c); SWRITE("\n");
 
       GWRITE(T_c); SWRITE("\n");

       for (i = 1; i <= r; i++)
         {
         GWRITE(NMSTACK[i]); SWRITE("\n");

         GWRITE(NMCELL[i]); SWRITE("\n");
      
         GWRITE(TMTICAD[i]); SWRITE("\n");
         }

       GWRITE(TMSOLUTION); SWRITE("\n");

       GWRITE(TAU); SWRITE("\n");

Step3: /* Finish. */
       SWRITE("@\n");
       SWRITE("--------------------------------\n"); goto Return;

Return: /* Prepare for return. */
       return;
}
