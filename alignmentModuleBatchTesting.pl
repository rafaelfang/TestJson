#!/usr/local/bin/perl
#
# testing alignment module in batch
#


$filename = $ARGV[0];
$timeLogFilename=$ARGV[1];
open(FILE1,"$filename");
open(FILE2,">>$timeLogFilename");
@lines=<FILE1>;
close(FILE1);

foreach $line(@lines) {
	
	$cmd = "./mufoldAlignment -hhsearch $line";
	print $cmd."\n";
	$start_run = time();
	system($cmd);
	$end_run = time();
	$run_time = $end_run - $start_run;
	print FILE2 "$line running time: $run_time \n";
}
close(FILE2);


