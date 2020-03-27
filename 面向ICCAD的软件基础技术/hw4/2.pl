#! /usr/bin/perl
$file = '8queen.out';
open(INFO,$file);
@lines =  <INFO>;
close(INFO);
foreach $line (@lines)
{	
	# $line =~ s/[\,\[\]\(\)]//g;
	
	$line =~ /(\d+)/;
	print $line;
}

