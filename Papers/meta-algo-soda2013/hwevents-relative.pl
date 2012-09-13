#!/usr/bin/perl -w
#
#  $ cat L1-misses.out~ | ./hwevents-relative.pl L1-misses-norm.tmpl L1

# $dict keeps track of all the original values
%dict = ();
# $norm_dict keeps track of the normalized values
%norm_dict = ();

if ($#ARGV != 1) {
    print "usage: hwevents-relatve.pl latex-template-file event-label\n";
    exit;
}

$tmpl = $ARGV[0];
$label = $ARGV[1];
open IN, "<$tmpl" or die "Can't open $tmpl";
# $last = the last index for arrays getting outa norm_dict
$last = 0;

while (my $line = <STDIN>) {
    @res = split(/\s+/, $line);
    for($i=1; $i<=$#res; $i++) {
        push @{ $dict{"$res[0]"} }, $res[$i];
    }
    # sanity check
    if($last == 0) {
        $last = $#res - 1;
    } elsif ($#res != -1) {
        ($last == $#res - 1) or
            die "Unexpected format: rows have different # of columns.\n";
    }
}

# normalize all the values by the last value
my $norm;
foreach my $k (keys (%dict)) {
    for($i=0; $i<$last; $i++) {
        $norm = $dict{$k}[$i] / $dict{$k}[$last];
        $norm = sprintf("%.6f", $norm);
        $key = $k . "Norm" . $label . $i; 
        $norm_dict{$key} = $norm;
    }
}

# sum up all the values and subtract the last value
# my $norm;
# foreach my $k (keys (%dict)) {
#     $norm = 0;
#     for($i=0; $i<$last; $i++) {
#         $norm += $dict{$k}[$i];
#     }
#     $ave = ($norm + $$dict{$k}[$last]) / 2;
#     $norm -= $dict{$k}[$last];
#     $norm = $norm / $ave;
#     $norm = sprintf("%.6f", $norm);
#     $key = $k . "Norm" . $label . "0"; 
#     $norm_dict{$key} = $norm;
# }

while (my $line = <IN>) {
    foreach my $k (keys (%norm_dict)) {
        $val = $norm_dict{$k};
        $line =~ s/$k/$val/ig;
# print "key: $k\n";
# print "val: $val\n";
    }
    print $line;
}

