/***************************************************************
***
*** gcword.h
***
*** This file defines the class GCWord, or "garbage collected
*** word".  It is designed to be used in conjunction with 
*** saclib to provide an easy way to incoporate garbage 
*** collected saclib lists into class definitions and arrays.
*** It even makes global variables easier to define.
***
*** An object of type GCWord behaves just like a "Word", except
*** that it is visible to the garbage collector even if it is
*** a member of some stucture or class or array or is, for any
*** other reason, not a local variable.  Note:  garbage 
*** collection may be slowed by the presence of GCWord's!
***
*** CWB 5/15/00
***************************************************************/

#ifndef _GCW_
#define _GCW_


extern "C" {
#include "saclib.h"
}
extern void gcw_register(Word *);


class GCWord
{
public:
  Word W;
  
  //-- Constructors -------------------------------------------//
  GCWord() { W = 0; gcw_register(&W); }
  GCWord(const GCWord &X) { W = X.W; gcw_register(&W); }
  GCWord(const Word &X) { W = X; gcw_register(&W); }

  //-- Destructor ---------------------------------------------//
  ~GCWord() { gcw_register(&W); }
  
  //-- Assignment ---------------------------------------------//
  GCWord& operator=(const GCWord& X) { W = X.W; return *this; }
  GCWord& operator=(const Word& X) { W = X; return *this;}
  
  //-- Cast to Word -------------------------------------------//
  operator Word() const { return W; }
};

#endif
