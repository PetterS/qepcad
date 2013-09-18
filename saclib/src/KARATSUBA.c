/*===========================================================================
			  KARATSUBA(A,n1,B,n2,C,W)

Integer product - array representation. Karatsuba's and Maeder's method.

Inputs
  n1,n2: positive beta-integers, n1 >= n2.
  A, B : non-negative integers of lengths n1 and n2 in array representation.
  C    : an array of length >= n1 + n2 + 1.
  W    : a work array of length >= 2(n1 - a + 3 floor(log_2(n1 - 3))),
         where a = 2^(k - 1) + 3 * k,
         with k = ceiling(log_2(MAXCLASSICAL - 3)).

Effect : A * B is added to C.
===========================================================================*/
#include "saclib.h"

void KARATSUBA(A,n1,B,n2,C,W)
        Word *A,n1,*B,n2,*C,*W;
{
        Word h,l,l1,l2,m;

Step1: /* Use classical algorithm if A,B are small. */
       if (n1 <= MAXCLASSICAL)
         {
         PRODUCT(A,n1,B,n2,C);
	 goto Return;
         }

Step2: /* A at least twice as long as B. */
       m = (n1 + 1) / 2;
       if (m >= n2)
         {
         KARATSUBA(A + 0, m, B, n2, C, W);
         if (n1 - m >= n2)
           KARATSUBA(A + m, n1 - m, B, n2, C + m, W);
         else
           KARATSUBA(B, n2, A + m, n1 - m, C + m, W);
         goto Return;
         }

Step3: /* Sum high and low order part of each number. */
       COPYTO(W + 0, A + 0, m);
       W[m] = 0;
       ADDTO(W + 0, A + m, n1 - m);
       if (W[m] == 0)
         l1 = m;
       else
         l1 = m + 1;
       COPYTO(W + (m+1), B + 0, m);
       W[m+1+m] = 0;
       ADDTO(W + (m+1), B + m, n2 - m);
       if (W[m+1+m] == 0)
         l2 = m;
       else
         l2 = m + 1;

Step4: /* Multiply the sums. Put product into result. */
       if ( l1 >= l2)
         KARATSUBA(W + 0, l1, W + (m+1), l2, C + m, W + 2*(m+1));
       else
         KARATSUBA(W + (m+1), l2, W + 0, l1, C + m, W + 2*(m+1));

Step5: /* Multiply high order parts. */
       h = (n1 - m) + (n2 - m) + 1;
       CLEAR(W + 0, h);
       KARATSUBA(A + m, n1 - m, B + m, n2 - m, W + 0, W + h);

Step6: /* Put high order product into result. */
       ADDTO(C + 2*m, W, (n1 - m) + (n2 - m));
       SUBFROM(C + m, W, (n1 - m) + (n2 - m));

Step7: /* Multiply low order parts. */
       l = m + m + 1;
       CLEAR(W + 0, l);
       KARATSUBA(A, m, B, m, W + 0, W + l);

Step8: /* Put low order product into result. */
       ADDTO(C + 0, W, m + m);
       SUBFROM(C + m, W, m + m);

Return: /* Prepare for return. */
	return;
}
