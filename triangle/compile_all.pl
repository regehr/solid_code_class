#!/usr/bin/perl -w

use strict;

my @dirs = ();
foreach my $d (glob "*") {
    if (-d $d) { 
	push @dirs, $d; 
    } 
}

foreach my $d (@dirs) {
    print "$d\n";
    chdir $d or die;
    system "make";
    chdir ".." or die;
}
