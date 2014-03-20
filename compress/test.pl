#!/usr/bin/perl -w

use strict;

my @dirs = (
    "team1",
    "team2",
    "team3",
    "group4",
    "team5",
    "team6",
    "team7",
    );

my @files = ();

open INF, "find /lib/modules/3.11.0-17-generic -name '*.ko' |" or die;
# open INF, "ls ~/*.pbm |" or die;

while (my $line = <INF>) {
    chomp $line;
    push @files, $line;
}
close INF;

system "rm -rf tmp";
system "mkdir tmp";
chdir "tmp" or die;

my $n=0;
foreach my $fn (@files) {
    system "cp $fn .";
    print "$fn\n";
    die unless ($fn =~ /\/([a-zA-Z0-9_\-\.]*)$/);
    my $root = $1;
    print "$root\n";
    foreach my $dir (@dirs) {
	print "  $dir : ";
	my $exe = "../$dir/rhuff";
	my $cfile = "${root}.hurl";
	system "rm -f $cfile";
	system "$exe -c $root";
	my $size = -s $cfile;
	if (defined $size) {
	    print "  size = $size\n";
	}
    }
    $n++;
    exit 0 if ($n>=100);
}
