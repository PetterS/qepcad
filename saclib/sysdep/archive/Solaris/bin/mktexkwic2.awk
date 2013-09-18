BEGIN { printf("\\begin{description}\n");}

 {
  # FILE
  #   mktexkwic2.awk - make a description list from lines of text.
  #
  # INPUTS
  #   ll ... line length
  #
  # VARIABLES
  #   kw  ... current keyword
  #   su  ... last subject
  #   col ... current column

  # Check if keyword has changed.
  if (kw != $1) {
    if (kw != "") printf("  \\end{description}\n");
    printf("\\item[%s] \\ \\ \n",$1);
    printf("  \\begin{description}\n");
    kw = $1;
    su = "";
  }

  # Abort line if subject is the same as the last one.
  if (su == $2) next;

  printf("  \\item[%s] ",$2);
  col = length($2) + 10;

  # Print text doing line breaking and indentation.
  for (i=3;i<=NF;i++)
    if (col+length($i) > ll) {
      col = 4+length($i); printf("\n    %s",$i);
    }
    else {
      col += 1+length($i); printf(" %s",$i);
    }
  printf("\n");
 }

END { printf("  \\end{description}\n\\end{description}\n");}

