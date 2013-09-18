/*************************************************************
 **
 **  Rend_Sample.h
 **
 **
 *************************************************************/
#ifndef _REND_SAMPLE_
#define _REND_SAMPLE_

/*************************************************************
 **  Includes
 *************************************************************/
#include "rend.h"

/*************************************************************
 **  Class Rend_Sample
 **  The two common functions of all sub-types of Rend_Sample
 **  are:
 **
 **  coordinate(k) - returns a logarithmic binary rational
 **    number approximating the coordinate of the sample point.
 **
 **  round(k,roundup) - returns a logarithmic binary rational
 **    number approximating the sample point coordinate, with
 **    a directed rounding, so that [round(k,0),round(k,1) is
 **    guaranteed to contain the coordinate.
 **
 *************************************************************/
class Rend_Sample
{
 public:
  virtual Word coordinate(int k) = 0; 
  virtual Word round(int k,int roundup)
    { return this -> coordinate(k); }
  //  virtual ~Rend_Sample() = 0;
};

class Rend_Sample_1DS : public Rend_Sample
{
  /*********************************************************
   ** 1-level section cells
   **
   ** P_index is the index of the sample point's minpol, A is
   ** the minpol itself, I is an isolating interval for the
   ** root of A that is the sample point, and t is the trend.
   *********************************************************/
private:
  int P_index,t;
  gcmemloc A,I;
public:
  Rend_Sample_1DS(Word C, Word P);
  virtual ~Rend_Sample_1DS();
  virtual Word coordinate(int k);
  virtual Word round(int k, int roundup);
  Word weakcompare(Word R);
    
};

class Rend_Sample_1DO : public Rend_Sample
{
  /*********************************************************
   ** 1-level sector cells
   *********************************************************/
public:
  Rend_Cell *l,*r;
  gcmemloc L;
public:
  Rend_Sample_1DO(Rend_Cell *dad);
  virtual ~Rend_Sample_1DO();
  virtual Word coordinate(int k);
    
};

class Rend_Sample_2DS : public Rend_Sample
{
  /*********************************************************
   ** 2-level sections over 1-level sections
   **
   ** I'm going to simply store the current best isolating
   ** interval in I.  If the sample point is in primitive
   ** representation, A stores the minimal polynomial. 
   ** Otherwise, A stores the whole sample point structure.
   *********************************************************/
private:
  int t;
  gcmemloc A,I;
public:
  Rend_Sample_2DS(Word C);
  virtual ~Rend_Sample_2DS();
  virtual Word coordinate(int k);
    
};

class Rend_Sample_2DC : public Rend_Sample
{
  /*********************************************************
   ** 2-level sections over 1-level sectors
   *********************************************************/
public:
  int P_index; // gives index of defining pol
  gcmemloc L;
public:
  Rend_Sample_2DC(Word C,Word P);
  virtual ~Rend_Sample_2DC();
  virtual Word coordinate(int k);
  void add_point(Word p);
  void clear_points();
};

class Rend_Sample_BR : public Rend_Sample
{
  /*********************************************************
   ** This is for virtual cells at +/- infinity
   *********************************************************/
private:
  gcmemloc N;
public:
  Rend_Sample_BR(Word a);
  virtual ~Rend_Sample_BR();
  virtual Word coordinate(int k);    
};

#endif /* _REND_SAMPLE_ */

