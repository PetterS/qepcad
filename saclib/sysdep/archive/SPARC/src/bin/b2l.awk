/^[^ ]/ {
  # FILE
  #   b2l.awk - concatenates a block of text to a single line.
  #
  # FUNCTION
  # Takes an input file which consists of one or more blocks of the
  # following format:
  #
  # <subject> <text>
  #   <0 or more lines of additional text beginning with at least one blank>
  #
  # and outputs each of these block as a single line of text.

  if (subcnt != 0)
    printf("%s %s\n",subject,text);
  subject = $1; 
  text = substr($0,length($1)+2,length($0)-length($1)-1);
  subcnt++;
}
/^ / {text = text $0}
END {printf("%s %s\n",subject,text)}
