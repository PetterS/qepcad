/*======================================================================
                      MODCR(b,G,Ms,Ns; bs)

Modify Coordintes.

\Input
  \parm{b} is a list of coordinates in $Q(\alpha)$.
  \parm{G} is the minimal polynomial of $\gamma$.
  \parm{M*} is $\alpha$ as an element of $Q(\gamma)$.
  \parm{N*} is $\beta$ as an element of $Q(\gamma)$.

\Output
  \parm{b*} is the list of cooridates in $Q(\gamma)$.
======================================================================*/
#include "qepcad.h"

void MODCR(Word b, Word G, Word Ms, Word Ns, Word *bs_)
{
       Word bp,bp1,bs,bs1;

Step1: /* Modify. */
       bs = NIL; bp = b;
       do
         {
         ADV(bp,&bp1,&bp);
         bp1 = AFICR(bp1);
         bs1 = RPAFME(1,G,bp1,LIST1(Ms));
         bs = COMP(bs1,bs);
         }
       while (!(bp == NIL));
       bs = COMP(Ns,bs);
       bs = INV(bs);
       goto Return;

Return: /* Prepare for return. */
       *bs_ = bs;
       return;
}
