 {
  for (i=2;i<=NF;i++) {
    kw = tolower($i);
    j = index(kw,"-");
    if (j > 0) {
      print substr(kw,1,j-1),$0;
      print substr(kw,j+1,length(kw)-j),$0;
    }
    else
      print kw,$0;
  }
 }
