/*************************************************************
 ** NOTE: This got superceeded by GCWord.
 **
 **  gcmemloc.h
 **
 **  This provides a not very efficient, but sound way to
 **  declare a global, static local, or variable within a
 **  an array or structure as being saclib garbage collected.
 **  If there's not a whole bunch of deallocation, it should
 **  be reasonable though.
 **
 *************************************************************/
#ifndef _GCMEMLOC_
#define _GCMEMLOC_

#include "../../source/saclib/gcword.h"

typedef GCWord gcmemloc;

#endif /* _GCMEMLOC_ */
