BEGIN { p = length(rcsdir)+2; count = 0; history = ""; }

$1 == "head" { history = "" }

$1 == "date" { history = substr($6,0,length($6)-1) " " history }

$1 == "desc" {
  n = split(history,a);

  if (state == "algo" && a[1] != "new" && a[n] != "del" &&
      match(history,"algo") > 0) {
     count++;
     print shortname(FILENAME,p); }

  if (state == "bug" && a[1] != "new" && a[n] != "del" &&
      match(history,"bug") > 0) {
     count++;
     print shortname(FILENAME,p); }

  if (state == "del" && a[1] != "new" && a[n] == "del") {
    count++;
    print shortname(FILENAME,p); }

  if (state == "new" && a[1] == "new" && a[n] != "del") {
    count++;
    print shortname(FILENAME,p); }
}


END {
  printf "\n>> %d functions ", count
  if (state == "algo")
    print "have modified algorithms."
  if (state == "bug")
    print "have bug fixes."
  if (state == "del")
    print "were deleted."
  if (state == "new")
    print "are new."
  printf "\n"
}


function shortname(longname,p) {
  sname = substr(longname,p);
  sname = substr(sname,0,length(sname)-2);
  return sname;
}
