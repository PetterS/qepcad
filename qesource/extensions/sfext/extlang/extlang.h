/*********************************************************************

As part of extending the language of solution formulae to include
statements like R_k( P_i,j ) to mean "the sign of the kth root
function", I need to extend the cell data structure to include a
field for the signs of the extended functions in cells.

If cell C is an i-level cell of an ESCAD (Extended sub-CAD), then
field SC_SIGN is a list (s_1,s_2, ... ,s_m), such that there are
m i-level projection factors for the ESCAD, and s_j is the sign of
the jth i-level projection factor in C.

The field SC_TMPM is a "temporary mark" which can be set to anything.

FNOTDEF is a constant intended to appear in the extended sign
vector, indicating that the expression is not defined.  It's used
over cells where a kth-root expression is not defined because the
polynomial in question doesn't have k roots.
**********************************************************************/
#ifndef _EXTLANG_
#define _EXTLANG_

#include "qepcad.h"
#include "coarsecad.h"

#define SC_SIGN 5
#define SC_EXTS 6
#define SC_TMPM 7
#define FNOTDEF -2

#ifndef BDCOMP
#define BDCOMP(a,b)       ((a) > (b) ? 1 : ((a) < (b) ? -1 : 0))
#endif

#endif
