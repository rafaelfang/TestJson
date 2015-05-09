#!/usr/local/bin/perl
#
# testing old mufold alignment module in batch
#


$filename = $ARGV[0];
$timeLogFilename=$ARGV[1];
open(FILE1,"$filename");
open(FILE2,">>$timeLogFilename");
@lines=<FILE1>;
close(FILE1);

$database="MUFOLD_01092013_";
foreach $line(@lines) {
	chomp($line);
	$cmd="~cf797/test/mufold_src/TEST/mufold.exe ~cf797/test/Proteins/${line}.fasta ${database} ~cf797/test/oldMufoldBatchTest/test${line}MUFOLD/ ${line}";
	print $cmd."\n";
	$dir="mkdir -p ~cf797/test/oldMufoldBatchTest/test${line}MUFOLD";
	print $dir."\n";	
	system($dir);
	$start_run = time();
	system($cmd);
	$end_run = time();
	$run_time = $end_run - $start_run;
	print FILE2 "$line running time: $run_time \n";
}
close(FILE2);


