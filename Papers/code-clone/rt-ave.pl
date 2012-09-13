#!/usr/bin/perl -w
#
# Reads the output of series of test runs from stdin and prints the
# mean of the running time for each application to stdout:
#
#   $ cat results.out | ./rt-ave.pl > rt-ave.out

my $app = "";
my $n = 0;
my $sum = 0;

while (my $line = <STDIN>) {
    if ($line =~ /START\:\s*[\.\/]*(.*?)\s+.*/) {
	if ($n > 0) {
	    my $ave = $sum / $n;
	    printf "%-15s %.3f\n", $app, $ave;
	}

	$app = $1;
	$n = 0;
	$sum = 0;
    }

    if ($app ne "" && $line =~ /Running time.*?(\d*\.\d*)\s+s/) {
	$sum += $1;
	$n++;
    }
}

if ($n > 0) {
    my $ave = $sum / $n;
    printf "%-15s %.3f\n", $app, $ave;
}
