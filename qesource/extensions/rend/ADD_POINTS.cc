/*===========================================================================
                       
===========================================================================*/
#include "rend.h"

void ADD_POINTS( Rend_Cell &C, Word p_index, Word x, Word L_)
{
  Word i,L,y;


  i = 0;

  //-- Loop over each point. --//
  for( L = L_; L != NIL; L = RED(L) ) {
    i += 2;

    //-- Find the next section of pol p_index. --//
    while( ((Rend_Sample_2DC*) C[i].sample )->P_index != p_index)
      i += 2;

    y = FIRST(L);

    /****** This version is for lists of RATIONAL numbers. ********
    ((Rend_Sample_2DC*) C[i].sample ) -> 
      add_point(LIST2(RNLBRN(x),RNLBRN(y))); */

    /****** This is for lists of LOGARITHMIC BINARY RATIONAL numbers. **/
    ((Rend_Sample_2DC*) C[i].sample ) -> add_point(LIST2(x,y));

  }
}

    
