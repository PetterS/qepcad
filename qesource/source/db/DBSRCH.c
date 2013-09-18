/*======================================================================
                      t <- DBSRCH(D,K)

Database Search.

\Input
  \parm{D} is the database to be searched.
  \parm{K} is the key.

\Output
  \parm{t} is 1 if exist,  0 otherwise.

\Side
  \parm{DBINFO} is the information found if the search was successful,
                   undefined otherwise.
  \parm{DBTIME} is set to the current time if the search was not successful.
======================================================================*/
#include "qepcad.h"

Word DBSRCH(Word D, Word K)
{
       Word C1,D1,Dp,K1,T1,f1,t;
       /* hide t; */

Step1: /* Search. */
                            /*Int*/ TMDBMNG = TMDBMNG - ACLOCK();
       Dp = D;
       while (Dp != NIL)
         {
         ADV(Dp,&D1,&Dp);
         FIRST4(D1,&K1,&C1,&T1,&f1);
         if (EQUAL(K1,K))
           {
           SLELTI(D1,4,f1 + 1);
           t = 1; DBINFO = C1;
                             /*Int*/ TMDBSAV = TMDBSAV + T1;
                             /*Int*/ TMDBMNG = TMDBMNG + ACLOCK();
           goto Return;
           }
         }

Step2: /* Not exist. */
       t = 0; DBINFO = NIL; DBTIME = ACLOCK();
                             /*Int*/ TMDBMNG = TMDBMNG + ACLOCK();
       goto Return;

Return: /* Prepare for return. */
       return(t);
}
