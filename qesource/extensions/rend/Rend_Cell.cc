/*************************************************************
 **
 **  Rend_Cell.cc
 ** 
 **
 *************************************************************/
#include "Rend_Cell.h"
#include "Mapper.h"

/*************************************************************
 **  class Rend_Cell Constructor
 *************************************************************/
Rend_Cell::Rend_Cell()
{
  index = level = left = right = AD2D_ErrI;
  parent = NULL; sample = NULL; truth = UNDET;
  section = 0;
}

/*************************************************************
 **  class Rend_Cell Destructor
 *************************************************************/
Rend_Cell::~Rend_Cell()
{
  delete sample;
  sample = NULL;
}

/*************************************************************
 **  initialize -- Initialize actually constructs the CAD
 **  image.
 *************************************************************/
void Rend_Cell::initialize(Rend_Cell* dad, int I, int l, Word C, Word P)
{
  Word S;

  //-- Set the easy information. --------------------------//
  QEPCAD_Cell = C;
  parent = dad;
  index = I;
  level = l;
  section = (index % 2 == 0 || index == AD2D_N_In || index == AD2D_Infy);
  if (level == 2 && index == AD2D_N_In && ! parent -> section) {
    left = AD2D_N_In; right = AD2D_N_In; }
  if (level == 2 && index == AD2D_Infy && ! parent -> section) {
    left = AD2D_Infy; right = AD2D_Infy; }

  //-- Set the child & truth fields appropriately. -----------------// 
  if (C != NIL) {
    truth = LELTI(C,TRUTH);
    S = LELTI(C,CHILD);
    if (level == 1 && section ) { //-- 1D Section
      sample = new Rend_Sample_1DS(C,P); }
    if (level == 1 && !section ) { //-- 1D Sector
      sample = new Rend_Sample_1DO(this); }
    if (level == 2 && section && dad -> section) { //section over section
      sample = new Rend_Sample_2DS(C); }
    if (level == 2 && section && ! (dad -> section)) { //section over sector
      sample = new Rend_Sample_2DC(C,P); } }
  else
    S = NIL;
  if (level < 2) { 
    //-- Set up stack above cell. --//
    child.allocate( LENGTH(S) + 2 );
    child[0].initialize(this, AD2D_N_In, l+1, NIL,NIL);
    child[ child.size() - 1 ].initialize(this, AD2D_Infy, l+1, NIL,NIL);
    for(int i = 1; S != NIL; i++,S = RED(S))
      child[i].initialize(this, i, l+1, FIRST(S), P); }

}

/*************************************************************
 **  set_extents
 **  
 *************************************************************/
void Rend_Cell::set_extents(Word J)
{
  Word n,j1,j2;
  if (level >= 2) {
    cerr << "set_extents called on a 2+D cell." << endl;
    child[0]; }
  n = child.size() - 1;
  FIRST2(J,&j1,&j2);
  if (child[0].sample != NULL)
    delete child[0].sample;
  child[0].sample = new Rend_Sample_BR(j1);
  if (child[n].sample != NULL)
    delete child[n].sample;
  child[n].sample = new Rend_Sample_BR(j2);
}

static char Tmap(Word t)
{
  switch(t) {
  case TRUE : return 'T'; 
  case FALSE : return 'F';
  default : return 'U';
  }
}

/*************************************************************
 **  description
 **  
 *************************************************************/
Word Rend_Cell::description(Rend_Win &W)
{
  Word V,l,r;

  //////*  Get those easy level 1 cells.
  if (level < 2)
    return sample -> coordinate(W.precis.x);

  //////*  Level 2 cells over sectors 
  if (! parent -> section ) {
    
    if (section) {

      ///////**** Section over Sector
      if (index == AD2D_Infy || index == AD2D_N_In)
	V = NIL;
      else
	V = sample -> coordinate(W.precis.y);

      // Add right neighbor
      Rend_Cell* nb = neighbor_l();
      if (nb != NULL)
	l = nb -> description(W);
      else {
	Word x = parent->parent->child[parent->index-1].sample->coordinate(W.precis.x);
	Word y = SECOND(FIRST(V));
	l = LIST2(x,y);
      }
      V = COMP( l , V );

      // Add left neighbor
      nb = neighbor_r();
      if (nb != NULL)
	r = nb -> description(W);
      else {
	Word x = parent->parent->child[parent->index+1].sample->coordinate(W.precis.x);
	Word y = SECOND(LAST(V));
	r = LIST2(x,y);
      }
      V = CONC(V,LIST1(r));
    }
    else {

      ///////**** Sector over Sector
      V = (*parent)[ index + 1 ].description(W);
      V = CINV(V);
      V = CCONC( (*parent)[ index - 1 ].description(W) , V); 
    }
  }
  else {

  //////*  Level 2 cells over sections.
    if (section) {

      ///////**** Section over Section
      if (index == AD2D_Infy)
	V = LIST2( parent -> description(W) ,  W.Y.W);
      else if (index == AD2D_N_In)
	V = LIST2( parent -> description(W) ,  W.y.W);
      else
	V = LIST2( parent -> description(W) , 
		   sample -> coordinate(W.precis.y) ); }
    else {
      
      ///////**** Sector over Section
      V = LIST2(
		parent -> child[index+1].description(W) ,
		parent -> child[index-1].description(W) ); }
  }
    
  return V;
      
}


/*************************************************************
 **  out_descrip
 **  
 *************************************************************/
void Rend_Cell::out_descrip(Rend_Win &W,ostream &out,Mapper &M)
{
  Word p,x,y,L,Lp,l,l1,l2,l3,x1,x2,y1,y2;

  int px = 8;
  int py = 8;

  switch (level) {
  case 0 :
    /****** Root Cell *************/
    return;
  case 1 :
    /****** 1D Section Cell *******/
    if (section) { 
      out << "V" << "\t" << Tmap(truth)  << "\t";
      M.Xwrite(description(W),out,px); out << endl; }
    else {
      FIRST2(description(W),&x1,&x2);
      out << "C" << "\t" << Tmap(truth) << "\t";
      M.Xwrite(x1,out,px); out << '\t'; M.Xwrite(x2,out,px); out << endl; }
    break;
  case 2:
    /****** 2D Cells  **************/
    if (parent -> section) {
      /*** in stack over section. ***/

      if (section) {
	out << "S" << "\t" << Tmap(truth)  << "\t";
	FIRST2( description(W) ,&x,&y); 
	M.Xwrite(x,out,px); out << '\t';M.Ywrite(y,out,py); out << endl; }
      else {

	out << "R" << "\t" << Tmap(truth)  << "\t";
	FIRST2( description(W) , &x, &y );
	FIRST2( x , &x1,&y1);
	FIRST2( y , &x2,&y2);

	M.Xwrite(x1,out,px); out << '\t'; 
	M.Ywrite(y1,out,py); out << '\t';
	M.Ywrite(y2,out,py); out << endl;
      }
    }
    else {
      /*** in stack over sector. ***/
      if (section) {
	out << "L" << "\t" << Tmap(truth)  << "\t"; }
      else {
	out << "P" << "\t" << Tmap(truth)  << "\t"; }

      L = description(W);

      out << LENGTH(L) << endl;
      while(L != NIL) {
	ADV(L,&l,&L);	
	out << '\t';
	M.Xwrite(FIRST(l),out,px); out << '\t'; 
	M.Ywrite(SECOND(l),out,py); out << '\n';
      }
    }

    break;
  }

}


/*************************************************************
 **  Some tiny helper functions
 *************************************************************/
     int Rend_Cell::array_index()
     {
       if (index > 0 && index < parent -> child.size() - 1)
	 return index;
       if (index == AD2D_N_In)
	 return 0;
       if (index == AD2D_Infy)
	 return parent -> child.size() - 1;
       return AD2D_ErrI;
     }

     Rend_Cell* Rend_Cell::neighbor_l()
     { //  This function assumes level == 2.
       int i_1;
       Rend_Cell* nb = NULL;
       if (left != AD2D_ErrI) {
	 i_1 = parent -> array_index();
	 Rend_Cell* nbdad = &(parent -> parent -> child[i_1 - 1]);
	 nb = &( (*nbdad)[ left ] );
       }
       return nb;
     }

     Rend_Cell* Rend_Cell::neighbor_r()
     { //  This function assumes level == 2.
       int i_1;
       Rend_Cell* nb = NULL;
       if (right != AD2D_ErrI) {
	 i_1 = parent -> array_index();
	 Rend_Cell* nbdad = &(parent -> parent -> child[i_1 + 1]);
	 nb = &( (*nbdad)[ right ] );
       }
       return nb;
     }

     Rend_Cell& Rend_Cell::operator[](int i)
     {
       if (i == AD2D_N_In)
	 i = 0;
       else if (i == AD2D_Infy)
	 i = child.size() - 1;
       return child[i];
     }

     void Rend_Cell::set_left(int i)
     {
       left = i;
     }

     void Rend_Cell::set_right(int i)
     {
       right = i;
     }

/*************************************************************
 **  out_descrip_ps  The postscript version
 **  
 *************************************************************/
void Rend_Cell::out_descrip_ps(Rend_Win &W,ostream &out, Mapper &M)
{
  Word p,x,y,L,l,x1,x2,y1,y2;
  p = 12;
  switch (level) {
  case 0 :
    /****** Root Cell *************/
    return;
  case 1 :
    /****** 1D Section Cell *******/
    out << "%%Cell(" << index << ")\n";
    if (section) { 
      L = LIST2(child[0].description(W),child[child.size() - 1].description(W));
      M.LPwrite(L,out,p);
    }
    else { 
      if (truth == TRUE) {
	  out << "gsave\n0.8 setgray\n";
	  
	  L = LIST4(
		    parent->child[ index - 1 ].child[0].description(W),
		    parent->child[ index - 1 ].child[parent->child[ 
							index - 1 ].child.size() - 1
		                                    ].description(W),
		    parent->child[ index + 1 ].child[parent->child[ 
							index + 1 ].child.size() - 1
		                                    ].description(W),
		    parent->child[ index + 1 ].child[0].description(W)
		    );
	  
	  M.LPwrite(L,out,p,1); 
	  out << "grestore\n"; }
	
    }
    break;
  case 2:     
    /****** 2D Cells  **************/  
    out << "%%Cell(" << parent->index << "," << index << ")\n";
    if (parent -> section) {
      /*** in stack over section. ***/
      
      if (section) {
	//-- section over section to add
      }
      else {
	//-- sector over section to add
      }
    }
    else {
      /*** in stack over sector. ***/
      if (section) {
	L = description(W);
	M.LPwrite(L,out,p);
      }
      else {
	//-- sector over sector
	if (truth == TRUE) {
	  out << "gsave\n0.8 setgray\n";
	  L = description(W);
	  M.LPwrite(L,out,p,1); 
	  out << "grestore\n"; }
      } }
    break;
  }
    
}


/*************************************************************
 **  out_descrip_pscolor  The postscript version
 **  
 *************************************************************/
void Rend_Cell::out_descrip_ps_color(Rend_Win &W,ostream &out, Mapper &M)
{
  Word p,x,y,L,l,x1,x2,y1,y2;
  p = 12;
  switch (level) {
  case 0 :
    /****** Root Cell *************/
    return;
  case 1 :
    /****** 1D Section Cell *******/
    if (truth == TRUE || truth == FALSE) {
      out << "%%Cell(" << index << ")\n";
      if (section) { 
	if (truth == TRUE)
	  out << "TSN\n";
	else
	  out << "FSN\n";
	L = LIST2(child[0].description(W),child[child.size() - 1].description(W));
	M.LPwrite(L,out,p);
      }
      else { 
	if (truth == TRUE)
	  out << "TSR\n";
	else
	  out << "FSR\n";
	  
	  L = LIST4(
		    parent->child[ index - 1 ].child[0].description(W),
		    parent->child[ index - 1 ].child[parent->child[ 
								   index - 1 ].child.size() - 1
		    ].description(W),
		    parent->child[ index + 1 ].child[parent->child[ 
								   index + 1 ].child.size() - 1
		    ].description(W),
		    parent->child[ index + 1 ].child[0].description(W)
		    );
	  
	  M.LPwrite(L,out,p,1); 
	  out << "grestore\n"; } }
    break;
  case 2:     
    /****** 2D Cells  **************/  
    out << "%%Cell(" << parent->index << "," << index << ")\n";
    if (parent -> section) {
      /*** in stack over section. ***/
      if (section) {
	//-- section over section to add
	/*
	if (truth == TRUE)
	  out << "TSN\n";
	else
	  out << "FSN\n";
	  */
      }
      else {
	//-- sector over section to add
	if (truth == TRUE)
	  out << "TSN\n";
	else
	  out << "FSN\n";
	L = description(W);
	M.LPwrite(L,out,p);
      }
    }
    else {
      /*** in stack over sector. ***/
      if (section) {
	if (truth == TRUE)
	  out << "TSN\n";
	else
	  out << "FSN\n";
	L = description(W);
	M.LPwrite(L,out,p);
      }
      else {
	//-- sector over sector
	if (truth == TRUE)
	  out << "TSR\n";
	else
	  out << "FSR\n";
	  L = description(W);
	  M.LPwrite(L,out,p,1); 
      } }
    break;
  }
    
}


/*************************************************************
 **  out_descrip_ps_raji
 **  
 *************************************************************/
void Rend_Cell::out_descrip_ps_raji(Rend_Win &W,ostream &out, Mapper &M)
{
  Word p,x,y,L,l,x1,x2,y1,y2;
  p = 12;
  switch (level) {
  case 0 :
    /****** Root Cell *************/
    return;
  case 1 :
    /****** 1D Section Cell *******/
    break;
  case 2:     
    /****** 2D Cells  **************/  
    out << "%%Cell(" << parent->index << "," << index << ")\n";
    if (parent -> section) {
      // Nothing for now
    }
    else {
      /*** in stack over sector. ***/
      if (section) {
	L = description(W);
	M.LPwrite(L,out,p);
      }
      else {
	//-- Shouldn't happen for Raji
      } }
    break;
  }
    
}


/*************************************************************
 **  out_descrip_pscolor  The postscript version
 **  
 *************************************************************/
void Rend_Cell::out_descrip_ps_standard(Rend_Win &W,ostream &out, Mapper &M)
{
  Word p,x,y,L,l,x1,x2,y1,y2;
  p = 12;
  switch (level) {
  case 0 :
    /****** Root Cell *************/
    return;
  case 1 :

    /****** 1D Section Cell *******/
    out << "%%Cell(" << index << ")\n";
    
    if (truth == TRUE)
      out << "TC\n";
    else if (truth == FALSE)
      out << "FC\n";
    else
      out << "UC\n";
    
    if (section) {
      L = LIST2(child[0].description(W),child[child.size() - 1].description(W));
      M.LPwrite(L,out,p); }
    else {
      
      L = LIST4(
		parent->child[ index - 1 ].child[0].description(W),
		parent->child[ index - 1 ].child[parent->child[index - 1 ].child.size() - 1].description(W),
		parent->child[ index + 1 ].child[parent->child[index + 1 ].child.size() - 1].description(W),
		parent->child[ index + 1 ].child[0].description(W)
		);
      M.LPwrite(L,out,p,1); }
    break;

  case 2:     
    /****** 2D Cells  **************/  
    out << "%%Cell(" << parent->index << "," << index << ")\n";
    
    if (truth == TRUE)
      out << "TC\n";
    else if (truth == FALSE)
      out << "FC\n";
    else
      out << "UC\n";

    if (parent -> section) {
      /*** in stack over section. ***/
      if (section) {
	//-- section over section to add
	M.Pwrite(description(W),out,p);
	out << " DOT\n";
      }
      else {
	//-- sector over section to add
	L = description(W);
	M.LPwrite(L,out,p);
      }
    }
    else {
      /*** in stack over sector. ***/
      if (section) {
	L = description(W);
	M.LPwrite(L,out,p);
      }
      else {
	//-- sector over sector
	L = description(W);
	M.LPwrite(L,out,p,1); 
      } }
    break;
  }
    
}

