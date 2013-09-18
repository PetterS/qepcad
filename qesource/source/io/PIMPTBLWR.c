/*======================================================================
                      PIMPTBLWR(C,R,V)

Prime Implicant Table Write.

\Input
 \parm{C} is the marks for columns.
 \parm{R} is the marks for rows.
 \parm{V} is the table.
======================================================================*/
#include "qepcad.h"
#define ALIVE      1
#define DEAD       0

void PIMPTBLWR(Word C, Word R, Word V)
{
       Word R1,Rp,T,V1,Vp,d,i,j,l,m,n,v;
       /* hide d,i,j,m,n; */

Step1: /* Draw the column heading. */
       m = LENGTH(C); n = LENGTH(R);
       if (m >= 1000 || n >= 1000)
         { SWRITE("PIMPTBLWR: Sorry the table is too big.\n"); goto Return; }
       SWRITE("=======");
       for (i = 1; i <= m; i++)
         { if (LELTI(C,i) == ALIVE) CWRITE('='); }
       SWRITE("\n       ");
       for (i = 1; i <= m; i++)
         { if (LELTI(C,i) == ALIVE) { d = i / 100; CWRITE(d + '0'); } }
       SWRITE("\n       ");
       for (i = 1; i <= m; i++)
         { if (LELTI(C,i) == ALIVE) { d = REM(i,100) / 10; CWRITE(d + '0'); } }
       SWRITE("\n       ");
       for (i = 1; i <= m; i++)
         { if (LELTI(C,i) == ALIVE) { d = REM(i,10); CWRITE(d + '0'); } }
       SWRITE("\n       ");
       for (i = 1; i <= m; i++)
         { if (LELTI(C,i) == ALIVE) CWRITE('-'); }
       SWRITE("\n");

Step2: /* Draw each rows. */
       Vp = V; Rp = R;
       for (j = 1; j <= n; j++)
         {
         ADV(Rp,&R1,&Rp); ADV(Vp,&V1,&Vp);
         if (R1 == ALIVE)
           {
           FIRST3(V1,&v,&l,&T);
           GWRITE(l); TAB(3);
           GWRITE(j); TAB(6); CWRITE('|');
           for (i = 1; i <= m; i++)
             {
             if (LELTI(C,i) == ALIVE)
               {
               if (INSET(T,i))
                 CWRITE('X');
               else
                 CWRITE('.');
               }
             }
           SWRITE("\n");
           }
         }

Step3: /* Draw the final line. */
       SWRITE("=======");
       for (i = 1; i <= m; i++)
         { if (LELTI(C,i) == ALIVE) CWRITE('='); }
       SWRITE("\n");

Return: /* Prepare for return. */
       return;
}
