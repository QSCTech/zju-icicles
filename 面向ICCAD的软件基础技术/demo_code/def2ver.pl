#!/usr/bin/perl
#Hello John,
#
#Replying to ESNUG 377 #4 from Tommy Zounes of ST, I am sending you my DEF
#to Verilog perl script.  The syntax is:
#
#        def2ver <def_file> <design_name>
#
#        Input: <def_file>
#        Output: design_name.v
#
#It will read a DEF (version 5.2) and generate a flat Verilog.
#
#    - [ A Synopsys PhysOpt FAE ]
#
#********************************************************
#*		DEF2VER					*
#* DEF2VER: Generate Verilog from DEF 5.2		*
#* Date 9/15/01						*
#********************************************************
#* 							*
#* Version 1.0 Initial release 9.15/01 by TNN		*
#* 							*
#********************************************************
#* USAGE: def2ver <DEF> <design_name>	*
#********************************************************
$def_file = $ARGV[0];
$verilog = "$ARGV[1]";
$design = "$ARGV[1]";
#
open (DEF,"$def_file");
open (VER, ">$verilog.v");
open (NET,"+>jnk_jnk.dat");
open (WIRE,"+>jnk_wire.dat");
open (INS,"+>jnk_cell.dat");
#
$t = &time();
print "Running DEF parser program $t\n";
&def_parser();
$t = &time();
print "Processing nets $t\n";
&def_proc();
$t = &time();
print "Generate Wire file $t\n";
&proc_wire();
$t = &time();
print "Output Verilog $verilog.v $t\n";
&gen_ver();
$t = &time();
print "FINISHED $t\n";
#
#********************************************************
sub def_parser
{
$r_i = 0;
$pi = 0;
while (<DEF>)
  {
  	$prr = 1 if ($_ =~ /^NETS/);
  	$prr = 2 if ($_ =~ /^COMPONENTS/);
  	$prr = 3 if ($_ =~ /^PINS/);
  	$prr = 0 if ($_ =~ /^END/);
#
# NETS  Section
#
   	if ($prr == 1)
          {
               if ($_ =~ /- /) {$ll = $_; $pr = 1;}
               elsif ($_ =~ /\+/) {$nn =$_; $nn =~ s/\+.*//; $ll == $ll.$nn; $pr = 0;}
               elsif ($pr == 1)  {$ll = $ll.$_;}
               $ll =~ s/\n//g;
               print NET "$ll\n" if ($_ =~ /\;/);
          }
#
# Components Section
#
   	elsif ($prr == 2)
           {
                @c = split(" ",$_);
    		$r = $c[1];
    		$cell{$r} = $c[2];
    		$port{$r} = "";
                $ref[$r_i]=$r;
                $r_i++;
            }
#
# PINS  Section
#
   	elsif ($prr == 3)
            {
               if ($_ =~ /- /) {$l = $_;}
               else {$l = $l.$_;}
#
               $l =~ s/\n//g;
               if (($l =~ /- /) & ($l =~ /\;/))
                {
                   $tem = $l;
                   $tem =~ s/[\+,\-]//g;
                   $tem =~ s/USE.*//;
                   @pp = split(" ",$tem);
                   $pin[$pi] = $pp[0];
                   $pin_pro[$pi] = "$pp[4]:$pp[0]";
                   $net_pin[$pi] = $pp[2];
                   $pi++;
                   $l ="";
               }
              
            }
	}
close (DEF);
}
#********************************************************
sub def_proc
{
$nn = 1;
seek(NET,0,0);
@n = <NET>;
close(NET);
for ($i=0; $i<= $#n; $i++)
   {
       $n[$i] =~ s/[\-,\)]//g;
       @q = split(/\(/, $n[$i]);
       $net = $q[0];
       $net =~ s/\s//g;
       $wire[$n_i] = $net;
       $net =~ s/\s//g;
       $n_i++;
       $nn++;
       if ($nn == 100000) {print "Processed $i nets\n"; $nn =1;}

       for ($j=1; $j<=$#q;$j++)
        {
              $tem = $q[$j];
              @p = split(" ",$tem);
              $r = $p[0];
              $port{$r} = "$port{$r} \-$p[1]:$net\+" ;
         }
    }
@n = "";
}
#*****************************************************************
sub proc_wire
{

  for ($i= 0; $i< $n_i; $i++)
   {
      print WIRE "$wire[$i]:" if ($wire[$i]=~ /./);
   }
#
# print wire from pin section
#
  for ($i= 0; $i< $pi; $i++)
   {
      print WIRE "$net_pin[$i]:";
   }

  for ($i= 0; $i< $r_i; $i++)
   {
      $r = $ref[$i];
      $port{$r} =~ s/\-/\./g;
      $port{$r} =~ s/\:/\(/g;
      $port{$r} =~ s/\+/\)/g;
      $port{$r} =~ s/\) \./\)\, \./g;
      if ($port{$r} =~/[A-Z]/)
       {
          print INS "\t$cell{$r}  $r\( $port{$r} \)\; \n" ;
       }
      else
       {
          print "//ERROR: No nets connected to $r $cell{$r}\n";
       }
   }
}
#*******************************************************************
sub time
{
  my $t;
  $t = `date`;
  chop($t);
  return ($t);
}
#*******************************************************************
sub gen_ver
{
   my $t, $i, $j;
   $t = &time;
   print VER "// $verilog.v is generated from DEF2VER program\n";
   print VER "// at $t \n";


# Module statement
   print VER "module $verilog \( $pin[0]";
   for ($i=1; $i<$pi; $i++)
     {
           print VER ", $pin[$i]";
     }
   print VER "\)\;\n\n";

# ports statement
   @s_pin = sort(@pin_pro);
   $prev="NEW";
   $wid = 1;
   for ($i=0;$i< $pi; $i++)
    {
      $tem = $s_pin[$i];
      @jn = split("\:",$tem);
      $jn[0] =~ tr/A-Z/a-z/;
      if ($prev !~ /$jn[0]/)
       {
          print VER "\;\n" if ($prev !~ /NEW/);
          print VER "$jn[0] $jn[1]";
          $prev = $jn[0];
          $wid = 1;
       }
      else
       {
          print VER ", $jn[1]";
          $wid ++;
       }
       if ($wid > 4) {$prev = "DIFF" ; $wid = 1;}
    }
    print VER "\;";
# wires statement
seek(WIRE,0,0);
$wid = 1;
$jn = <WIRE>;
@n = split("\:",$jn);
print VER "\n\nwire ";
for ($i=0; $i<=$#n; $i++)
  {
     $n[$i] =~ s/\//__/g;
     if (($wid >= 4) && ($i < $#n)) {$nl = 1; $wid = 1;}
     elsif ($i == $#n) {$nl = 2;}
     else {$wid ++; $nl = 0;}

     print VER "$n[$i]";
     if ($nl == 1) {print VER "\;\nwire "; $nl = 0;}
     elsif ($nl == 2) {print VER "\;\n\n";}
     else {print VER "\, ";}
  }
close (WIRE);

# Inst statement
seek(INS,0,0);
while (<INS>) {$tem = $_; $tem =~ s/\//__/g; print VER $tem;}
close (INS);

#end module statement
print VER "\nendmodule\n";
}

