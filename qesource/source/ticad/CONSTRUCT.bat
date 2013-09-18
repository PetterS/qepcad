                   CONSTRUCT(D,c,k,f,P*,A*)
 
[Construct a stack.
 
\Input
    \parm{D}  is a partial CAD.
    \parm{c}  is a candidate cell of~\v{D}.
    \parm{k}  is the level of the cell~\v{c}.
    \parm{f}  is the number of free variables in the input formula.
    \parm{P*} is the list of the $(k+1)$--level projection factors.
    \parm{A*} is the list of all the distinct $(k+1)$--level
              normalized input polynomials.
 
\Output
    A stack is constructed over the cell~\v{c}.
    If \v{A*} $\neq \emptyset$ or $k+1 \leq f$,
         the signature of \v{P*} on each cell in the stack is determined
         and attached to the cell.
]

include "qepcadGlobals.h"

(1) [Root cell.]
    if k > 0 then goto 2;
    if P* /= () then I := IPLRRI(P*) else I := ();
    EC1(c,I);
    if A* /= () \/ 1 <= f then SIGNP1(c,P*,I);
    return.
 
(2) [Non-root cell, Irrational sample point.]
    s := LELT(c,SAMPLE); FIRST3(s;M,I,b);
    if PDEG(M) = 1 then go to 3;
    S := SUBST(k,M,b,P*);
    AFUPLM(M,S;L,T);
    AFCSBMDB(M,T;B,E);
    if B /= () then I := AUPBRI(M,I,B) else I := ();
    EC(c,I);
    if A* /= () \/ k+1 <= f then SIGNP(c,k,B,I,E,L);
    return.

(3) [Non-root cell, Rational sample point.]
    b:=RCFAFC(b);
    S := SUBSTR(k,b,P*);
    IPLSRP(S;s,T);  
    IPFSBM(1,T;B,E);
    if B /= () then I:=IPLRRI(B) else I:=();
    ECR(c,I);
    if A* /= () \/ k+1 <= f then SIGNPR(c,k,B,I,E,s);
    return ||
