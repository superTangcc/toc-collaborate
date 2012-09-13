#!/usr/bin/perl -w
#
# Reads the output from rt-ave.pl from stdin and replaces patterns
# in the latex-template-file with running time averages:
#
#  $ cat wall-clock.out | ./rt-ave.pl | ./rt-replace.pl resultstable.tmpl TPS

%dict = ();

if ($#ARGV != 1) {
    print "usage: rt-replace.pl latex-template-file prefix\n";
    exit;
}

$tmpl = $ARGV[0];
$prefix = $ARGV[1];
open IN, "<$tmpl" or die "Can't open $tmpl";

while (my $line = <STDIN>) {
    @res = split(/\s+/, $line);
    $dict{"$prefix$res[0]"} = $res[1];
}

while (my $line = <IN>) {
    foreach my $k (keys (%dict)) {
        $line =~ s/$k/$dict{$k}/ig;
    }
    print $line;
}
