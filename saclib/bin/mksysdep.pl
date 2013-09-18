################################################
# mksysdep.pl V 0.0
# Created by Chris Brown, 20 May, 208
################################################
if ($#ARGV == 0 && ($ARGV[0] eq "-h" || $ARGV[0] eq "--help"))
{
    print "sconf/mksysdep.pl\n".
"sconf [x86linux|sparcsolaris|x86_64linux|x86macos|x86_64macos]\n\n".
"This script installs system dependent files for\n".
"saclib.  It attempts to diagnose architecture and\n".
"processor type and install the proper files.  You\n".
"can give the arch/os type explicitly as one of the\n".
"arguments listed above, and the script will install\n".
"what you've asked for regardless of its diagnosis.\n";
    exit 0;
}

if (! $ENV{'saclib'})
{
    print "SACLIB Error: The saclib environment variable must be set!\n";
    exit(1);
}

### Get architecture type
$ptype = "unknown";
$uname = `uname -mp`;
if ($uname =~ /i\S*86/)
{
    $ptype = "x86";
}
elsif ($uname =~ /x86_64/)
{
    $ptype = "x86_64";
}
elsif ($uname =~ /Sun|sun|SUN|Sparc|sparc|SPARC/)
{
    $ptype = "sparc";
}
else
{
    print "SACLIB Warning: Could not determine processor type!\n";
}

### Get OS type
$ostype = "unknown";
$uname = `uname -s`;
if ($uname =~ /linux|Linux|LINUX/)
{
    $ostype = "linux";
}
elsif ($uname =~ /Sun|sun|SUN|solaris|Solaris/)
{
    $ostype = "solaris";
}
elsif ($uname =~ /Darwin|darwin|DARWIN/)
{
    $ostype = "macos";
    ### Do we have a 32-bit or 64-bit kernel running?
    $macosKernelTest = `ioreg -l -p IODeviceTree | grep firmware-abi | grep EFI64`;
    if ($macosKernelTest) { $ptype = "x86_64"; } elsif ($ptype == "x86_64") { $ptype = "x86"; }
}
else
{
    print "SACLIB Warning: Could not determine OS type!\n";
}

### Call appropriate install script
if ($#ARGV == 1 && $ARGV[0] eq "x86linux")
{
    print "SACLIB Warning: Installing x86linux system dependent files!\n";
    system("bash -c \"pushd >/dev/null $ENV{'saclib'}/sysdep/linuxX86 ; ./install ; popd >/dev/null\"");
}
elsif ($#ARGV == 1 && $ARGV[0] eq "x86macos")
{
    print "SACLIB Warning: Installing x86macos system dependent files!\n";
    system("bash -c \"pushd >/dev/null $ENV{'saclib'}/sysdep/macosX86 ; ./install ; popd >/dev/null\"");
}
elsif ($#ARGV == 1 && $ARGV[0] eq "x86_64macos")
{
    print "SACLIB Warning: Installing x86_64macos system dependent files!\n";
    system("bash -c \"pushd >/dev/null $ENV{'saclib'}/sysdep/macosX86_64 ; ./install ; popd >/dev/null\"");
}
elsif ($#ARGV == 1 && $ARGV[0] eq "x86_64linux")
{
    print "SACLIB Warning: Installing x86_64linux system dependent files!\n";
    system("bash -c \"pushd >/dev/null $ENV{'saclib'}/sysdep/linuxX86_64 ; ./install ; popd >/dev/null\"");
}
elsif ($#ARGV == 1 && $ARGV[0] eq "sparcsolaris")
{
    print "SACLIB Warning: Installing sparcsolaris system dependent files!\n";
    system("bash -c \"pushd >/dev/null $ENV{'saclib'}/sysdep/solarisSparc ; ./install ; popd >/dev/null\"");
}
elsif ($ptype eq "x86" && $ostype eq "linux")
{
    system("bash -c \"pushd >/dev/null $ENV{'saclib'}/sysdep/linuxX86 ; ./install ; popd >/dev/null\"");    
}
elsif ($ptype eq "x86" && $ostype eq "macos")
{
    system("bash -c \"pushd >/dev/null $ENV{'saclib'}/sysdep/macosX86 ; ./install ; popd >/dev/null\"");    
}
elsif ($ptype eq "x86_64" && $ostype eq "macos")
{
    system("bash -c \"pushd >/dev/null $ENV{'saclib'}/sysdep/macosX86_64 ; ./install ; popd >/dev/null\"");    
}
elsif ($ptype eq "x86_64" && $ostype eq "linux")
{
    system("bash -c \"pushd >/dev/null $ENV{'saclib'}/sysdep/linuxX86_64 ; ./install ; popd >/dev/null\"");    
}
elsif ($ptype eq "sparc" && $ostype eq "solaris")
{
    system("bash -c \"pushd >/dev/null $ENV{'saclib'}/sysdep/solarisSparc ; ./install ; popd >/dev/null\"");
}
