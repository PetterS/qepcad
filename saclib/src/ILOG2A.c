/*===========================================================================
<macro>                      b <- ILOG2A(A,n)

Integer logarithm, base 2, array version.

Inputs
  A : in Z, in array representation.
  n : a BETA-digit, the word length of A.

Outputs
  b : a BETA-integer.
      If A = 0 then b = 0.
      Otherwise, b = floor(log_2(|A|)) + 1.

#define ILOG2A(A,n)    (((n)==0) ? 0 : ((n)-1)*ZETA + DLOG2((A)[(n)-1]))
===========================================================================*/
