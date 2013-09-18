/*===========================================================================
				  CTMI(A)

Create table of modular inverses.

Input:
   A:  Array of length 128.

Effect:  A[i] is set to the inverse of 2*i + 1 modulo 2^8.
===========================================================================*/
#include "saclib.h"

void CTMI(A)
       Word *A;
{
       Word i;

Step1: /* Use MDINV. */
       for (i = 0; i < 128; i++)
	  A[i] = MDINV(256,2*i + 1);

Return: /* Return. */
       return;
}
