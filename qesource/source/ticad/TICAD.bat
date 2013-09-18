                        D:=TICAD(Q,F,f,P,A)

[Truth Invariant CAD Construction Phase.
     
\Input
  \parm{Q} is the list of quantifiers
           in the input formula.
  \parm{F} $=F(x_1,\ldots,x_r)$
           is the normalized input quantifier-free formula.
  \parm{f} is the number of free variables in the input formula.
  \parm{P} is the list~$(P_1,\ldots,P_r)$, 
           where $P_i$ is the list of
           $i$--level projection factors.
  \parm{A} is the list~$(A_1,\ldots,A_r)$,
           where $A_i$ is the list of all
           the distinct $i$--level normalized input polynomials.
 
Output:
  \parm{D} is a truth--invariant partial CAD of $f$--space
           in which every leaf cell has a determined truth value.]

include "qepcadGlobals.h"
 
(1) [Initialize.]
    D:=INITPCAD().   
    
(2) [Choose.]
    CHOOSE(D;t,c);   if t = 0 then return;
    k:=LELT(c,LEVEL); if k = 0 then goto 4.
 
(3) [Convert.]
    CONVERT(c,k).

(4) [Construct stack.]
    P*:=LELT(P,k+1); A*:=LELT(A,k+1); CONSTRUCT(c,k,f,P*,A*).
 
(5) [Evaluate.]
    EVALUATE(c,k,F,A).
 
(6) [Propagate.]
    PROPAGATE(D,c,k,f,Q);  goto 2 ||
