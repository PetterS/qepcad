#!/usr/local/bin/perl

open(IN,"temp") || die "Can't open temp: $!\n";

################################################################
$m = 0;
while(<IN>) {
  @data = split(/(\S+)\s(\S+)\s(\S+)\s(\S+)/,$_);
  if (!$data[2]) { last;}
  $a = $data[1];
  @temp = split(/\((\d+)\,\S+/,$a);
  if ($temp[1] > $m) { $m = $temp[1]; }
  shift(@data);
  $cell{$a} = "$data[2] $data[3]";
}

################################################################
foreach $i (1..$m) {
  $hand = "hand".$i;
  open($hand,">out$i.eps") || die "Can't open $hand: $!\n";
  print $hand "%!PS-Adobe-2.0 EPSF-1.2\n";
  print $hand "%%BoundingBox: 0.000 0.000 360.0 360.0\n";
  print $hand "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
  print $hand "0 setlinewidth\n";
  print $hand "40 40 scale\n";
  print $hand "5 5 translate\n"; }

################################################################
foreach $a ( sort(keys(%cell))) {
  @temp = split(/\((\d+)\,\S+/,$a);
  $hand = "hand".$temp[1];
  print $hand "newpath\n";
  print $hand $cell{$a};
  print $hand " 0.05 0 360 arc\n stroke\n"; }

while(<IN>) {
  @data = split(/\((\(.+\)),(\(.+\))\)/,$_);
  @temp = split(/\((\d+)\,\S+/,$data[1]);
  $hand = "hand".$temp[1];
  print $hand "newpath\n$cell{$data[1]} moveto\n$cell{$data[2]} lineto\nstroke\n";
}


