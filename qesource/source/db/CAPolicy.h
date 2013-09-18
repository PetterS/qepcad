/***************************************************************
 * This file defines the CAPolicy class.  QEPCADB uses this to
 * perform the computations below.
 ***************************************************************/
#ifndef _CA_POLICY_
#define _CA_POLICY_
#include "qepcad.h"
#include "CAServer.h"
#include <map>
#include <iostream>
using namespace std;

class CASComp 
{ 
public: 
   bool operator()(CAServer *p1, CAServer *p2) { return p1->name() < p2->name(); }
};

typedef map<string,CAServer*> ServerBase;

class CAPolicy
{
public:
  virtual ~CAPolicy() { }
  virtual void IPFAC(Word r, Word P, Word *s_, Word *c_, Word *L_) = 0;
  virtual Word IPRES(Word r, Word A, Word B) = 0;
  virtual Word IPDSCR(Word r, Word A) = 0;
  virtual Word IPFACTGB(Word r, Word I, Word N) 
    { FAIL("CAPolicy::IPFACTGB","Not implemented in this policy!"); }

/*
CONSTORDTEST
Input
 r : a level
 A : an r-level saclib polynomial
 L : a list of r-variate saclib polynomials

Returns TRUE if it is determined that the vanishing of A and 
the elements of L implies that the order of A is constant.
Otherwise returns a GB for A,L and all k-order partials s.t.
some of the partials are not 0.
 */
  virtual Word CONSTORDTEST(Word r, Word A, Word L) 
    { FAIL("CAPolicy::CONSTORDTEST","Not implemented in this policy!"); }

  virtual const string name() = 0;
  virtual bool supports(const string &s) = 0;
};

extern CAPolicy *GVCAP;
extern ServerBase GVSB;



#endif
