if (! $ENV{'saclib'})
{
    print "SACLIB Error: The saclib environment variable must be set!\n";
    exit(1);
}

open(SACMAC,"< $ENV{'saclib'}/include/sacmacros.h");
$maj = "?";
$min = "?";
$rev = "?";
while(<SACMAC>)
{
    if ($_ =~ /SACMAJVERS\s+(\d+)/) { $maj = $1; }
    if ($_ =~ /SACMINVERS\s+(\d+)/) { $min = $1; }
    if ($_ =~ /SACREVVERS\s+(\d+)/) { $rev = $1; }
} 
print "Saclib ${maj}.${min}.${rev}\n";
