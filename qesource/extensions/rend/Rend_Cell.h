/*************************************************************
 **
 **  Rend_Cell.h
 **
 **
 *************************************************************/
#ifndef _REND_CELL_
#define _REND_CELL_

/*************************************************************
 **  Includes
 *************************************************************/

using namespace std;

#include "rend.h"
class Mapper;

/*************************************************************
 **  Class Rend_Cell
 *************************************************************/
class Rend_Cell
{
  /** Data Members *******************************************/
public:
  int index;/* the index of the cell in its stack           */
  int level;/* the level of the cell                        */
  int left; /* the index of the cell's left neighbor        */
  int right;/* the index of the cell's right neighbor       */
  int section;/* 1 if the cell's a section  and 0 otherwise */
  Word truth; /* the truth value of the cell                */
  Safe_Array<Rend_Cell> child; /* the children of the cell  */
  Rend_Cell* parent; /* the parent cell                     */
  Rend_Sample* sample; /* the cell's sample point.          */
  Word QEPCAD_Cell; 

  /** Function Members **************************************/
public:
  Rend_Cell();
  ~Rend_Cell();
  void initialize(Rend_Cell* parent, 
		  int I, 
		  int l, 
		  Word C, 
		  Word P);
  void set_left(int i); /* sets index of left neighbor      */
  void set_right(int i);/* sets index of right neighbor     */

  Rend_Cell& operator[](int i); /* gives child from index   */
  Rend_Cell* neighbor_l(); /* returns left neighbor cell    */
  Rend_Cell* neighbor_r(); /* returns right neighbor cell   */
  int array_index();       /* returns i such that 
			      parent->child[i] is the cell  */
  void set_extents(Word J);
  void out_descrip(Rend_Win &W, ostream &out, Mapper &M);
  void out_descrip_ps(Rend_Win &W, ostream &out, Mapper &M);
  void out_descrip_ps_color(Rend_Win &W, ostream &out, Mapper &M);
  void out_descrip_ps_standard(Rend_Win &W, ostream &out, Mapper &M);
  void out_descrip_ps_raji(Rend_Win &W, ostream &out, Mapper &M);
  Word description(Rend_Win &W);
};


#endif /* _REND_CELL_ */
