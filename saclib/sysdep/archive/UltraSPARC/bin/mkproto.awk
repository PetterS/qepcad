BEGIN { FS = "("; in_function = 0; first_var = 0; }

/^\/\*.*$/,/^.*\*\/$/ {
  next;
}

/^.*\(.*\)$/ {
  # Function declaration
  in_function = 1; first_var = 1;
  FS = " ";
  printf("extern %s\tP__((",$1);
  next;
}

/^.* .*$/ {
  # Outside function declaration
  if (in_function == 0)
    next;
  # Inside function declaration
  type = $1;
  semicolon = 0; i = 2;
  while (semicolon == 0) {                    # Parse variable declarations
    if (i > NF) {                               # end of line?
      getline;
      i = 1;
    }
    lastchar = substr($i,length($i),1);
    if (lastchar == ";") {                      # check for trailing semicolon
      semicolon = 1;
      s = substr($i,1,length($i)-1);              # and remove it
    }
    else if (lastchar == ",") {                 # check for trailing comma
      s = substr($i,1,length($i)-1);              # and remove it
    }
    else
      s = $i;
    nf = split(s,vars,",");                     # get variables
    for (j=1; j<=nf; j++) {                     # print them
      if (first_var == 1) {
        printf("%s %s",type,vars[j]);
        first_var = 0;
      }
      else
        printf(", %s %s",type,vars[j]);
    }
    i++;
  }
}


/^{/ {
  # End of function declaration
  if (in_function == 1) {
    in_function = 0;
    if (first_var == 1)
      printf("void));\n");
    else
      printf("));\n");
  }
  exit;
}

END { if (in_function == 1)  printf("));\n"); }

