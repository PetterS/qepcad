                         P:=PROJECT(r,A)

[Projection Phase.
 
\Input
  \item{A} is a list~$(A_1,\ldots,A_r)$, where $A_i$ is a list of
           all the distinct $i$--level normalized input polynomials. 
         
\Output
  \item{P} is a list~$(P_1,\ldots,P_r)$, where $P_i$ is a list of
           $i$--level projection factors.
]
 
(1) [Initialize.]  
    P:=LLCOPY(A); k:=r.
 
(2) [Done?]         
    if k = 1 then return.

(3) [Project.] 
    Pk := LELT(P,k); J:=PROJ(k,Pk).
      
(4) [Factor.]      
    R:=IPLFAC(k-1,J).
 
(5) [Append.] 
    P:=APPEND(P,k-1,R).
   
(6) [Loop.] 
    k := k - 1;  goto 2 ||



