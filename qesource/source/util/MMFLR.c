/*======================================================================
                      P <- MMFLR(L)

Make Matrix From a List of Rows.

\Input
  \parm{L} is a list of rows of $\beta$--integers: 
       $((L_{1,1},\ldots,L_{1,m_1}),\ldots,(L_{n,1},\ldots,L_{n,m_n}))$,
       where $n \geq 0$ and $m_i \geq 0$ for $1 \leq i \leq n$.
       
\Output
  \parm{P} is the  $n $by $t_{n+1}$ matrix $(P_{i,j})$ such that 
           $P_{i,j} = 0$              if $j > t_{i+1}$ or $j \leq t_i$,
                      $L_{i,j-t_i}$   otherwise
           where $t_i$ is $m_1 + m_2 + \cdots + m_{i-1}$.
======================================================================*/
#include "qepcad.h"

Word MMFLR(Word L)
{
       Word L1,L11,Lp,P,P1,i,k,n;
       /* hide i,k,n; */

Step1: /* Make. */
       n = LENGTH(L); P = NIL;
       for (i = 1; i <= n; i++)
         {
         P1 = NIL; Lp = L;
         for (k = 1; k <= n; k++)
           {
           ADV(Lp,&L1,&Lp);
           while (L1 != NIL)
             {
             ADV(L1,&L11,&L1);
             if (k == i) P1 = COMP(L11,P1); else P1 = COMP(0,P1);
             }
           }
         P1 = INV(P1); P = COMP(P1,P);
         }
       P = INV(P);
       goto Return;

Return: /* Prepare for return. */
       return(P);
}
