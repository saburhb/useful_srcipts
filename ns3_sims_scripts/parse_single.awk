#!/usr/bin/awk -f

BEGIN {
        FS=" ";
	file=ARGV[1]
}

{
	stime=$1
	sseq=$2
	bytes=$3

	time_out="time_"file
	seq_out="seq_"file
	bytes_out="bytes_"file

	print stime >> ("/Users/sabur/Documents/sims_results/"time_out) 
	print sseq >> ("/Users/sabur/Documents/sims_results/"seq_out) 
	print bytes >> ("/Users/sabur/Documents/sims_results/"bytes_out) 
}

END {

}
