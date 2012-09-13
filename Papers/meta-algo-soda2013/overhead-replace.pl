#!/usr/bin/perl -w
# Reads PERFCTR_TIMING output from stdin and replaces patterns
# in the latex-template-file with running time averages:
# $ cat fib-overhead.diff | ./overhead-replace.pl coststable.tmpl TPSfib
# this file is called from build-overhead.sh

%dict = ();

if ($#ARGV != 1) {
    print "usage: overhead-replace.pl latex-template-file prefix\n";
    exit;
}

$tmpl = $ARGV[0];
$prefix = $ARGV[1];
open IN, "<$tmpl" or die "Can't open $tmpl";

while (my $line = <STDIN>) {
    if( $line =~ m/^START: \.\/(\w+)/ ) {
        $user_prog = $1;
        # print "program: $user_prog \n";
    } elsif( $line =~ /^XX.*\s+\(([\d\.]+)\)\s+([\d]+)$/ ) {
        @res = split(/\s+/, $line);
        $key = $prefix . $user_prog . $res[1];
        $per_steal_key = $prefix . $user_prog . "Ind" . $res[1];
        $per_steal_val = $1;
        $val = $2;
        # print "$key: $val \n";
        # print "$per_steal_key: $per_steal_val\n";
      	$dict{$key} = $val;
      	$dict{$per_steal_key} = $per_steal_val;
    }

    #    @res = split(/\s+/, $line);
    # used for *.ave files
#     if ($line =~ /.*\s+([\-\d\.]+)/) {
#         # for ave file instead of diff file, so only one column to parse
#         # prefix is either MIT or TPS
#         # res[1] = the second word in the input file
#         # uncomment the next line if want to use accumulative values
#         next if( exists($dict{"$prefix$res[1]"}) );
#     	$dict{"$prefix$res[1]"} = $1;
#     } 
#     else {
#         # just want the first part of data (running with 2 workers)
#         last;
#     }
    
    # This is used for *diff files
#     if ($line =~ /.*\s+([\-\d\.]+)\s+([\-\d+\.]+)/) {
# 	    $dict{"$prefix$res[1]"} = $1; # $1 is the accumulative value
# 	    # $dict{"$prefix$res[1]0"} = $1; # $1 is the accumulative value
# 	    # $dict{"$prefix$res[1]1"} = $2; # $2 is divided per steal 
#     }
}

while (my $line = <IN>) {
    foreach my $k (keys (%dict)) {
          # i for case insensitive and g for global replace
        $line =~ s/$k/$dict{$k}/;
    }
    print $line;
}


