#! /usr/bin/perl
$file = 'words';
open(INFO,$file);
@lines =  <INFO>;
close(INFO);
foreach $line (@lines)
{
	if( $line =~ /([aeiouAEIOU]{4,})/ )
	{
		print $line;
	}
}

