#!/usr/bin/perl -w
#
#  $ cat ave0.out ave1.out | ./rt-relative.pl relativeperf.tmpl

%dict = ();

if ($#ARGV != 0) {
    print "usage: rt-replace.pl latex-template-file\n";
    exit;
}

$tmpl = $ARGV[0];
open IN, "<$tmpl" or die "Can't open $tmpl";

while (my $line = <STDIN>) {
    @res = split(/\s+/, $line);
    push @{ $dict{"XXX$res[0]"} }, $res[1];
}

while (my $line = <IN>) {
    foreach $k (keys (%dict)) {
        $norm = $dict{$k}[0]/$dict{$k}[1];
        $norm = sprintf("%.3f", $norm);
        $line =~ s/$k/$norm/ig;
    }
    print $line;
}
