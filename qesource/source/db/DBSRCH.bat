                        t:=DBSRCH(D,K)

[Database Search.

\Input
  \parm{D} is the database to be searched.
  \parm{K} is the key.

\Output
  \parm{t} is 1 if exist,  0 otherwise.

\Side
  \parm{DBINFO} is the information found if the search was successful,
                   undefined otherwise.
  \parm{DBTIME} is set to the current time if the search was not successful.
]

include "qepcadGlobals.h"

(1) [Search.]
    D':=D;
    while D' /= () do
      {
      ADV(D';D1,D');
      FIRST4(D1;K1,C1,T1,f1);
      if EQUAL(K1,K) then
        {
        SLELT(D1,4,f1+1);
        t:=1; DBINFO:=C1;
        return
        }
      }.

(2) [Not exist.]
    t:=0; DBINFO:=(); DBTIME:=ACLOCK(); 
    return ||

