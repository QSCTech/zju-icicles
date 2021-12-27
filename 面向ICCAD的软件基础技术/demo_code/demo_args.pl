#!/usr/bin/perl -w

use strict;# 这样可以少一些错误?

print "The input arguments are:\n";
#怎么获得argv的? 自动获得, 怎么提取?  用标量来提取.
foreach $a (@ARGV)
{
	print "$a \n";
} 

my $n = @ARGV;
print "There are totally $n of them.\n\n";

print "In this program, I can also see environment variables' values\n";
$n = $ENV{"PATH"};
print "For example - the \$PATH is $n \n";
$n = $ENV{"HOME"};
print "For example - the \$HOME is $n \n";

