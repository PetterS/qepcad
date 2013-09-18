/*===========================================================================
<macro>                      s <- ISIGNA(A,n)

Integer sign function, array version.

Input
  A : in Z, in array representation.
  n : a BETA-digt, the word length of A.

Output
  s : the sign of A.

#define ISIGNA(A,n)    ((n) == 0 ? 0 : (((A)[(n)-1] > 0) ? 1 : -1))
===========================================================================*/
