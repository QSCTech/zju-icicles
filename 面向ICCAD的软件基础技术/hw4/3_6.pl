#! /usr/bin/perl
$file = 'words';
open(INFO,$file);
@lines =  <INFO>;
close(INFO);
foreach $line (@lines)
{
	if( $line =~ /(.)\1(.)\2(.)\3/ )
	{
		print $line;
	}
}

