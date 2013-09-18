/*===========================================================================
                         SEPLAB(k,C; Cb,Ch)
Separate labels.

Inputs
   k :  a beta-digit, k >=2.
   C :  the list of labels of the irreducible factors of a k-level
        constraint.

Outputs
   Cb : a list of the labels in C of factors of level less than k.
   Ch : a list of the labels in C of factors of level k.
===========================================================================*/
#include "qepcad.h"

void SEPLAB(Word k, Word C, Word *Cb_, Word *Ch_)
{
       Word C1,Cb,Ch,Cp,h;

Step1: /*  */
       Cp = C;
       Cb = NIL;
       Ch = NIL;
       while (Cp != NIL) {
	  ADV(Cp,&C1,&Cp);
	  h = SECOND(C1);
	  if (h < k) Cb = COMP(C1,Cb);
	  else Ch = COMP(C1,Ch); }

Return: /* Prepare for return. */
       *Cb_ = Cb;
       *Ch_ = Ch;
       return;
}
