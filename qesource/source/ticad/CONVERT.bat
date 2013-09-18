                        CONVERT(c,k)

[Convert to a primitive sample point.  
 
\Input 
   \parm{c} is a cell.
   \parm{k} is the level of the cell~\v{c}, \v{k} $\geq 1$.
 
\Output
   If the sample point of the cell~\v{c} is not primitive, 
   it is converted to a primitive one.
]

include "qepcadGlobals.h"

(1)[Already primitive.]
   s:=LELT(c,SAMPLE); if ISPRIMIT(s) then return.   
 
(2)[Trivial case.]
   g:=FIRST(s); if PDEG(g) > 1 then goto 3;
   c' := LELT(c,PARENT); s':=LELT(c',SAMPLE); FIRST3(s';M,I,b);
   a0:= AFUPRL(M,g);
   b := CCONC(b,LIST1(a0));
   s := LIST3(M,I,b);
   SLELT(c,SAMPLE,s);
   return.
 
(3)[Nontrivial case.]
   NORMAL(c); SIMPLE(c); return ||
