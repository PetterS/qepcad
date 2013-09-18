 {
  # FILE
  #   strip1st.awk - removes the first word from each line.
  #
  # FUNCTION
  #   The first word and the first blank character after it are removed
  #   from each line. The remainder is printed with blanks etc. exactly
  #   as in the original file.

  print substr($0,length($1)+2);
 }
