#!/usr/bin/perl -w

use strict;

my $verbose = 0;

# my @points = (0, 1, 2, 2147483647, 2147483646, 2147483645);
my @points = (0, 1, 2147483647, 2147483646);

sub ran () {
    return int (rand (2147483648));
}

sub maybe_ran () {
    if (rand() < 0.5) {
	return ran();
    } else {
	return $points[rand @points];
    }
}

my @exes;
my %wrong;
my %illegal;
my %right;
my %partitions;
my %illegals;
my $num_exes;

sub run_test ($$$$$$) {
    (my $x1, my $y1, my $x2, my $y2, my $x3, my $y3) = @_;
    if ($verbose) {
	print "----------------------------------------\n";
	print "$x1 $y1 $x2 $y2 $x3 $y3\n";
    }

    my %answers;
    my %results;
    my %votes;
    my $n=0;
    
    foreach my $exe (@exes) {
	$n++;
	print "$exe\n" if $verbose;
	open INF, "'./$exe' $x1 $y1 $x2 $y2 $x3 $y3 2>/dev/null |" or die;
	my $line = <INF>;
	close INF;
	if (!defined($line)) {
	    print "illegal: blank output\n" if $verbose;
	    $line = "";
	    $illegal{$exe}++;
	    $illegals{$exe}{$line}++;
	} elsif ($line =~ /^(((scalene|isosceles|equilateral) (acute|obtuse|right))|not a triangle)\n$/) {
	    chomp $line;
	    $votes{$line}++;
	} else {
	    chomp $line;
	    print "illegal: $line\n" if $verbose;
	    $illegal{$exe}++;
	    $illegals{$exe}{$line}++;
	}
	$results{$exe} = $line;
    }

    my @answers = keys %votes;

    my @pop = sort { $votes{$b} <=> $votes{$a}; } @answers;
    foreach my $x (@pop) {
	# rint "$x $votes{$x}\n";
    }
    if ($votes{$pop[0]} > ($num_exes / 2)) {
	my $winner = $pop[0];
	$partitions{$winner}++;
	print "winner: $winner\n" if $verbose;
	foreach my $x (@exes) {
	    if ($results{$x} eq $winner) {
		$right{$x}++;
	    } else {
		$wrong{$x}++;
	    }
	}
    }
}

foreach my $exe (glob "*/triangle") {
    next unless -e $exe;
    push @exes, $exe;
    $wrong{$exe} = 0;
    $illegal{$exe} = 0;
    $right{$exe} = 0;
}
$num_exes = scalar @exes;

my $N = 46656;

my $n;
my $pct;

sub reset_pct () {
    $n = 0;
    $pct = 0;
}

sub update_pct () {
    $n++;
    my $p = int (100.0 * $n / $N);
    if ($p > $pct) {
	$pct = $p;
	print "$p %\n";
    }
}

if (0) {
    reset_pct();
    for (my $i=0; $i<scalar(@points); $i++) {
	my $x1 = $points[$i];
	for (my $j=0; $j<scalar(@points); $j++) {
	    my $y1 = $points[$j];
	    for (my $k=0; $k<scalar(@points); $k++) {
		my $x2 = $points[$k];
		for (my $l=0; $l<scalar(@points); $l++) {
		    my $y2 = $points[$l];
		    for (my $m=0; $m<scalar(@points); $m++) {
			my $x3 = $points[$m];
			for (my $n=0; $n<scalar(@points); $n++) {
			    my $y3 = $points[$n];			
			    run_test ($x1, $y1, $x2, $y2, $x3, $y3);
			    update_pct();
			}
		    }
		}
	    }
	}
    }
}

if (1) {
    for (my $i=0; $i<4; $i++) {
	for (my $j=0; $j<4; $j++) {
	    for (my $k=0; $k<4; $k++) {
		for (my $l=0; $l<4; $l++) {
		    for (my $m=0; $m<4; $m++) {
			for (my $n=0; $n<4; $n++) {
			    run_test ($i, $j, $k, $l, $m, $n);
			    #run_test (2147483647 - $i, 2147483647 - $j, 2147483647 - $k, 2147483647 - $l, 2147483647 - $m, 2147483647 - $n);
			    #run_test (2147483647 - $i, $j, 2147483647 - $k, $l, 2147483647 - $m, $n);
			    #run_test ($i, 2147483647 - $j, $k, 2147483647 - $l, $m, 2147483647 - $n);
			}
		    }
		}
	    }
	}
    }
}

if (0) {    
    reset_pct();
    for (my $i=0; $i<$N; $i++) {
	my $x1 = ran();
	my $y1 = ran();
	my $x2 = ran();
	my $y2 = ran();
	my $x3 = ran();
	my $y3 = ran();
	run_test ($x1, $y1, $x2, $y2, $x3, $y3);
	update_pct();
    }
}

if (0) {    
    reset_pct();
    for (my $i=0; $i<$N; $i++) {
	my $x1 = maybe_ran();
	my $y1 = maybe_ran();
	my $x2 = maybe_ran();
	my $y2 = maybe_ran();
	my $x3 = maybe_ran();
	my $y3 = maybe_ran();
	run_test ($x1, $y1, $x2, $y2, $x3, $y3);
	update_pct();
    }
}

print "\nresults:\n";
foreach my $exe (@exes) {
    print "$exe : right $right{$exe}, wrong $wrong{$exe}, illegal $illegal{$exe}\n";
}
print "\nillegal outputs:\n";
foreach my $exe (@exes) {
    next if scalar (keys %{$illegals{$exe}}) == 0;
    print "$exe : ";
    foreach my $s (sort keys %{$illegals{$exe}}) {
	print "'$s' ";
    }
    print "\n";
}
print "\npartitions covered:\n";
foreach my $s (sort keys %partitions) {
    my $n = $partitions{$s};
    print "  $s $n\n";
}
