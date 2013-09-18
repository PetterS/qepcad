/^\/\*===*$/ {

  # Inputs
  #   sc ... starting column of text
  #   ll ... line length

  # Get function name
  getline;
  while (NF == 0) getline;
  i = index($0,"<- ")+3;
  if (i == 3)
    if (index($1,"<macro>") != 0) name = $2
    else name = $1
  else name = substr($0,i,length($0)-i+1);
  i = index(name,"("); if (i > 1) name = substr(name,1,i-1);

  # Compute text alignment from sc and length of function name
  if (length(name) > sc-2) {
    col = length(name)+1; fmt = "%s";
  }
  else {
    col = sc-1; fmt = sprintf("%%-%ds",sc-2);
  }
  printf(fmt,name);

  # Print text doing line breaking and indentation.
  fmt = sprintf("\n%%%ds",sc-2);
  getline;
  while (NF == 0) getline;
  while (length($0) != 0) {
    for (i=1;i<=NF;i++) {
      if (col+length($i) > ll) {
        col = sc-1; printf(fmt," ");
      }
      col += 1+length($i); printf(" %s",$i);
    }
    getline;
  }
  printf("\n");
  close(FILENAME);
 }
