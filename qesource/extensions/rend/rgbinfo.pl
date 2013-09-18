#!/usr/local/bin/perl
while (<>) {
  if(/(\d+)\s+(\d+)\s+(\d+)\s+(.*)/) {
    $name = $4;
    
    print("T[\"$name\"] = ",($1*256 + $2)*256 + $3,";\n"); 
  }
}
