/***************************************************************
 * This file defines the class CAServer (Computer Algebra Server).
 * The fundamental idea is that some standard calculations, like
 * resultants, discriminants, factorization and groebner basis
 * calculation could be provided by different systems.  The
 * CAServer provides an interface to a system.
 ***************************************************************/
#ifndef _CA_SERVER_
#define _CA_SERVER_
#include "qepcad.h"
#include <iostream>
using namespace std;

class CAServer
{
public:
  virtual void IPFAC(Word r, Word P, Word *s_, Word *c_, Word *L_)
  {
    cerr << "IPFAC not implemented by this CAServer!" << endl;
    exit(1);
  }
  virtual Word IPRES(Word r, Word A, Word B)
  {
    cerr << "IPRES not implemented by this CAServer!" << endl;
    exit(1);
  }
  virtual Word IPDSCR(Word r, Word A)
  {
    cerr << "IPDSCR not implemented by this CAServer!" << endl;
    exit(1);
  }

  /*
    Integer Polynomial Factorized Groebner Basis: 
    Inputs:
     r = number of variables
     I = a list of r-variate polynomials that generate the ideal
     N = a list of negated equations, i.e. non-zero constraints
    Output:
     F = a factorized Groebner Basis given as a list of GB's, each
         GB being a list of r-variate integral polynomials.  The intersection
	 of these ideals has the same zero set as the original ideal,
	 assuming the given non-zero constraints.  Each polynomial
	 will be integral.	 
   */
  virtual Word IPFACTGB(Word r, Word I, Word N)
  {
    cerr << "IPFACTGB not implemented by this CAServer!" << endl;
    exit(1);
  }
  virtual Word CONSTORDTEST(Word r, Word A, Word L)
  {
    cerr << "CONSTORDTEST not implemented by this CAServer!" << endl;
    exit(1);
  }


  virtual int serverTime() { return -1; }
  virtual void reportStats(ostream &out) 
  { 
    out << "Stats for CAServer " << name() << " not available." << endl; 
  }
  virtual const string name() { return "Empty"; }
  virtual ~CAServer() { }
  virtual void kill() { } // response to a kill signal, emergency cleanup!
};


#endif
