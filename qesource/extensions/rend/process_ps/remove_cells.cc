/*************************************************************
 ** This program is meant to be used on the eps files produced
 ** by my 2D CAD plotting program.
 ************************************************************/

#include <iostream.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int get_int(char* &p)
{
  int n;
  for(n = 0; isdigit(*p); p++)
    n = 10*n + ((*p) - '0');
  return n;
}

main(int argc, char** argv)
{
  const int n = 200, true = 1, false = 0;
  char A[n], B[5];
  int cell_flag = 0;

  /************************************************************
   ** What should get kept and what killed?
   ************************************************************/
  int k_level, k_tv, k_p1, k_p2, k_flag = 0;
  if (argc < 5) {
    cerr << "Not enough arguments!" << endl;
    exit(1); }
  k_level = atoi(argv[1]);
  k_tv    = atoi(argv[2]);
  k_p1    = atoi(argv[3]);
  k_p2    = atoi(argv[4]);

  /************************************************************
   ** Loop over each line!			    
   ************************************************************/
  while (cin.getline(A,n)) {

    /**********************************************************
     ** Begining of cell declaration.
     **********************************************************/
    if (strncmp(A,"%%Cell(",7) == 0) {
      cell_flag = 1; 

      //-- Find 1-level index. --------------------------------//
      char *p = A + 7;
      int i1 = get_int(p), i2, level;

      //-- Find cell's level and (if needed) second index. ----//
      if (*p == ',') {
	level = 2;
	i2 = get_int(++p); }
      else
	level = 1;

      //-- Find cell's truth value. ---------------------------//
      cin.getline(B,5);
      int tv = (B[0] == 'T');
      
      //-- Decide whether or not cell should be in file. ------//
      k_flag = ((k_level > 2 || level == k_level) && 
		(k_tv > 1 || k_tv == tv) &&
		(k_p1 > 1 || k_p1 == (i1 % 2)) &&
		(level != 2 || k_p2 > 1 || k_p2 == (i2 % 2)));

      //-- If cell should stay in file, write out header. -----//
      if (!k_flag) {
	cout << A << endl;
	strcpy(A,B); }
    }

    /************************************************************
     ** To print line or not to print line.
     ************************************************************/
    if (!cell_flag || !k_flag)
      cout << A << endl;

    /************************************************************
     ** End of cell declaration.
     ************************************************************/
    if (strncmp(A,"fill",4)   == 0 ||
	strncmp(A,"stroke",6) == 0 ||
	strncmp(A + strlen(A) - 3,"DOT",3) == 0)
      cell_flag = 0;
  }
}
