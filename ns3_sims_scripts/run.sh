#!/bin/bash

SPATH=.
INFILE=$SPATH/combined_output.txt

######## Remove file if already existing #############

for f in ./{*_send.txt,*_recv.txt}; do
        [ -e "$f" ] && $(rm "$f")
done

####### Seperate Send files ########
$(grep SEND $INFILE | grep -i Skype >> skype_send.txt) 
$(grep SEND $INFILE | grep -i Vid >> vid_send.txt) 
$(grep SEND $INFILE | grep -i Youtube >> youtube_send.txt) 
#$(grep SEND $INFILE | grep -i FTP >> ftp_send.txt)

####### Seperate Receive files ########
$(grep RECEIVE $INFILE | grep -i Skype >> skype_recv.txt) 
$(grep RECEIVE $INFILE | grep -i Vid >> vid_recv.txt) 
$(grep RECEIVE $INFILE | grep -i Youtube >> youtube_recv.txt) 
#$(grep RECEIVE $INFILE | grep -i FTP >> ftp_recv.txt)



for f in ./{time_*,seq_*,bytes_*,output_*}; do
        [ -e "$f" ] && $(rm "$f")
done

########## Parse skype files ###########
if [ -s "skype_send.txt" ]
then
	$(perl -pi -e 's/Skype://g' skype_send.txt)
	$(perl -pi -e 's/SEND://g' skype_send.txt)
	$(./parse_single.awk skype_send.txt)
fi

if [ -s "skype_recv.txt" ]
then
	$(perl -pi -e 's/Skype://g' skype_recv.txt)
	$(perl -pi -e 's/RECEIVE://g' skype_recv.txt)
	$(./parse_single.awk skype_recv.txt)
fi


########## Parse Vid files ###########
if [ -s "vid_send.txt" ]
then
	$(perl -pi -e 's/Vid://g' vid_send.txt)
	$(perl -pi -e 's/SEND://g' vid_send.txt)
	$(./parse_single.awk vid_send.txt)
fi

if [ -s "vid_recv.txt" ]
then
	$(perl -pi -e 's/Vid://g' vid_recv.txt)
	$(perl -pi -e 's/RECEIVE://g' vid_recv.txt)
	$(./parse_single.awk vid_recv.txt)
fi

########## Parse youtube files ###########
if [ -s "youtube_send.txt" ]
then
	$(perl -pi -e 's/Youtube://g' youtube_send.txt)
	$(perl -pi -e 's/SEND://g' youtube_send.txt)
	$(./parse_single.awk youtube_send.txt)
fi

if [ -s "youtube_recv.txt" ]
then
	$(perl -pi -e 's/Youtube://g' youtube_recv.txt)
	$(perl -pi -e 's/RECEIVE://g' youtube_recv.txt)
	$(./parse_single.awk youtube_recv.txt)
fi


########## Process ftp files ###########
if [ -s "ftp_send.txt" ]
then
	$(perl -pi -e 's/FTP://g' ftp_send.txt)
	$(perl -pi -e 's/SEND://g' ftp_send.txt)
	$(./parse_single.awk ftp_send.txt)
fi

if [ -s "ftp_recv.txt" ]
then
	$(perl -pi -e 's/FTP://g' ftp_recv.txt)
	$(perl -pi -e 's/RECEIVE://g' ftp_recv.txt)
	$(./parse_single.awk ftp_recv.txt)
fi


################# Paket analysis and metrics ###############
if [ -s "time_skype_recv.txt" ]
then
	$(./PKTANA time_skype_send.txt seq_skype_send.txt bytes_skype_send.txt time_skype_recv.txt seq_skype_recv.txt bytes_skype_recv.txt >> output_skype.txt)
fi
if [ -s "time_vid_recv.txt" ]
then
	$(./PKTANA time_vid_send.txt seq_vid_send.txt bytes_vid_send.txt time_vid_recv.txt seq_vid_recv.txt bytes_vid_recv.txt >> output_vid.txt)
fi
if [ -s "time_youtube_recv.txt" ]
then
	$(./PKTANA time_youtube_send.txt seq_youtube_send.txt bytes_youtube_send.txt time_youtube_recv.txt seq_youtube_recv.txt bytes_youtube_recv.txt >> output_youtube.txt)
fi
if [ -s "time_ftp_recv.txt" ]
then
	$(./PKTANA time_ftp_send.txt seq_ftp_send.txt bytes_ftp_send.txt time_ftp_recv.txt seq_ftp_recv.txt bytes_ftp_recv.txt >> output_ftp.txt)
fi





