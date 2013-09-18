 {
  # FILE
  #   l2b.awk - format a line as a block of text.
  #
  # INPUTS
  #   sc ... starting column of text
  #   ll ... line length
  #
  # FUNCTION
  #   Takes lines of text and formats them as follows:
  #   COLUMN  1         sc                                         ll
  #           <subject> <text......................................>
  #                     <0 or more lines of additional text........>
  #
  #   Where <subject> is the first word of the line. The text in the first
  #   output line may start to the right of column 'sc' if <subject> has
  #   more than 'sc-2' characters. Line breaking is done only at blanks -
  #   if a single word has more than 'll-sc' characters will go beyond
  #   column 'll'.

  # Compute format string for subject from sc and length of subject and
  # print subject.
  subject = $1;
  if (length(subject) > sc-2) {
    col = length(subject)+1; fmt = "%s";
  }
  else {
    col = sc-1; fmt = sprintf("%%-%ds",sc-2);
  }
  printf(fmt,subject);

  # Print text doing line breaking and indentation.
  if (sc > 1)
    fmt = sprintf("\n%%%ds%%s",sc-1);
  else
    fmt = sprintf("\n%s");
  for (i=2;i<=NF;i++)
    if (col+length($i) > ll) {
      col = sc+length($i); printf(fmt," ",$i);
    }
    else {
      col += 1+length($i); printf(" %s",$i);
    }
  printf("\n");
 }

