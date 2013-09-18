 {
  # INPUTS
  #   sc ... starting column of text
  #   kc ... column of keyword
  #   ll ... line length
  #
  # VARIABLES
  #   scol ... actual starting column of text
  #   kcol ... actual column of keyword
  #     $1 ... subject
  #     t1 ... text to the left of the keyword
  #     t2 ... text to the right of the keyword
  #     $i ... keyword (i is the index of the keyword in the line)
  #   sfmt ... format string for printing of the subject
  #

  # Adjust scol and kcol.
  scol = sc; kcol = kc;
  if (length($1) > scol-2) scol = length($1) + 2;
  if (scol > kcol-2) kcol = scol+2;
  t1len = kcol-scol-1;
  t1fmt = sprintf("%%%ds",t1len);

  # Loop through all keywords and create KWIC lines.
  for (i=2;i<=NF;i++) {
    # Format t1 s.t. the keyword is aligned on its column.
    t1 = ""; j = i-1;
    while ((j >= 2) && (length(t1)+length($j)+1 <= t1len)) {
      t1 = $j " " t1; j--;
    }
    if (length(t1) < t1len)
      if (j >= 2) {
        l = t1len-length(t1)-1;
        t1 = substr($j,length($j)-l+1) " " t1;
      }
      else {
        t1 = sprintf(t1fmt,t1);
      }
    # Format t2 s.t. the line ends at column ll.
    t2 = ""; j = i+1;
    if (length($i)+kcol < ll) {
      t2len = ll-length($i)-kcol-1;
      while ((j <= NF) && (length(t2)+length($j)+1 <= t2len)) {
        t2 = t2 " " $j; j++;
      }
      if ((length(t2) < t2len) && (j <= NF)) {
        l = t2len-length(t2)-1;
        t2 = t2 " " substr($j,1,l);
      }
    }
    # Print KWIC line.
    sfmt = sprintf("%%-%ds",scol-2);
    print $i,sprintf(sfmt,$1),t1,$i,t2;
  }
}
