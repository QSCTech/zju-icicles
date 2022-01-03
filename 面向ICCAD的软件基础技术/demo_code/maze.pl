#!/usr/bin/perl -w

use strict;

#e=east, n=north, s=south, w=west

my @maze=(  
     [ qw( e   swe we ws  ) ],
     [ qw( ne new sw ns ) ],
     [ qw( ns  -      ns wn  ) ],
     [ qw( ne w     ne w   ) ],
);

my %direction=( n=> [ -1, 0], s=> [1, 0], e=> [0, 1], w=> [0, -1]);
my %full=( e => 'East', n => 'North', w=>'West', s=>'South');
my($curr_x, $curr_y, $x, $y)=(0,0,3,3);
my $move;

sub disp_location {
    my($cx, $cy)=@_;
    print "You may move ";
    while($maze[$cx][$cy]=~/([nsew])/g) {
            print "$full{$1} ";
    }
    print "($maze[$cx][$cy])\n";
}

sub move_to {
    my($new, $xref, $yref)=@_;

    $new=substr(lc($new),0,1);
    if ($maze[$$xref][$$yref]!~/$new/) {
            print "Invalid direction, $new.\n";
            return;
    }
    $$xref += $direction{$new}[0];
    $$yref += $direction{$new}[1];
}

until ( $curr_x == $x and $curr_y == $y ) {
    disp_location($curr_x, $curr_y);
    print "Which way? ";
    $move=<STDIN>; chomp $move;
    exit if ($move=~/^q/);
    move_to($move, \$curr_x, \$curr_y);
}

print "You made it through the maze!\n";

