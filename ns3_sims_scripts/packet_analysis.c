#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

	double stime[10001],rtime[10001];
	int sseq[10001], rseq[10001], sbytes[10001], rbytes[10001];
	int mov_index[30], bit_rate[30];
	int t_bytes, count_limit;
	int send_count;

	if(argc != 7){
		printf("\n Number of arguments provided: %d", argc);
		printf("\n Need to provide 6 arguments");
		return 1;
	}
	
	FILE *ft1 = fopen(argv[1], "r");
	FILE *fs1 = fopen(argv[2], "r");
	FILE *fb1 = fopen(argv[3], "r");
	FILE *ft2 = fopen(argv[4], "r");
	FILE *fs2 = fopen(argv[5], "r");
	FILE *fb2 = fopen(argv[6], "r");
	

	/***************************************************************/
	/***************** Populate Data Structures ********************/
	char line[30];
	int temp_t1,ind_t1;
	for(ind_t1=0; fgets(line,25,ft1) != NULL; ind_t1++)
            {
                stime[ind_t1] = atof(line);
            }
            fclose(ft1);

	int temp_s1,ind_s1;
        for(ind_s1=0; fgets(line,25,fs1) != NULL; ind_s1++)
            {
                sseq[ind_s1] = atoi(line);
            }
            fclose(fs1);

	int temp_b1,ind_b1;
        for(ind_s1=0; fgets(line,25,fb1) != NULL; ind_b1++)
            {
                sbytes[ind_b1] = atoi(line);
            }
            fclose(fb1);

	int temp_t2,ind_t2;
        for(ind_t2=0; fgets(line,25,ft2) != NULL; ind_t2++)
            {
                rtime[ind_t2] = atof(line);
            }
            fclose(ft2);

	int temp_s2,ind_s2;
        for(ind_s2=0; fgets(line,25,fs2) != NULL; ind_s2++)
            {
                rseq[ind_s2] = atoi(line);
            }
            fclose(fs2);

	int temp_b2,ind_b2;
        for(ind_b2=0; fgets(line,25,fb2) != NULL; ind_b2++)
            {
                rbytes[ind_b2] = atoi(line);
            }
            fclose(fb2);

	
	for (int k=0; k<20; k++)
	{
		printf("\n [ %f \t %d \t %d]     [ %f \t %d \t %d]", stime[k], sseq[k], sbytes[k], rtime[k], rseq[k], rbytes[k]	);
	}	


	for(int i=100; i<10001; i++){
		if(sseq[i] == 0){
			send_count=i;
			printf("\n\n!!!!!!!!! SEND COUNT: %d  !!!!!!!!!!!\n\n", send_count);
			break;	
		}
	}

	for(int i=100; i<10001; i++){
		if(rseq[i] == 0){
			count_limit=i;
			printf("\n\n!!!!!!!!! COUNT LIMIT : %d  !!!!!!!!!!!\n\n", count_limit);
			break;	
		}
	}

	/**********************  Process Packet Data  ***************************/

	/**************************************************************************/
	/**************** Calculate Lost Packets and Bad Packets ******************/
	
	float diff;
	int bad_pkt_index[10001];
	int pi=0;
	int lost_pkt_index[10001];
	int li=0;
	for(int i=0; i<send_count; i++)
	{
		int j=0;
		while(j < count_limit)
		{
			if(sseq[i] == rseq[j]){
				if(sbytes[i] == rbytes[j]){
					diff = (rtime[j] - stime[i])*1000;
					if(diff > 75){
						bad_pkt_index[pi++] = i;
					}			
				}
				else{
					printf("\n Bytes Mismatch");
					lost_pkt_index[li++] = i;
				}
				break;
			}
			if(j==(count_limit-1)){
				lost_pkt_index[li++] = i;
				//printf("\n ###### LOST PACKET is %d #######\n", i);			
			}
			j++;
		}
	}

	printf("\n ************* The list of lost packets: ***************\n");
	for(int i=1; i<10001; i++){
		if(lost_pkt_index[i] == 0)
			break;
		printf("%d, ", lost_pkt_index[i]);
	}	

	printf("\n\n\n\n ************* The list of bad packets: *****************\n");
	for(int i=1; i<10001; i++){
		if(bad_pkt_index[i] == 0)
                        break;
		printf("%d, ", bad_pkt_index[i]);
	}	

	/****************************************************************************/
	/****************************************************************************/


	/**************************************************************************/
	/******************* Calculate Throughput, Bitrate ************************/

	int k=2;
	for(int i=0; i<count_limit; i++){

		if(rtime[i] < k){
			t_bytes=t_bytes + rbytes[i];
		}
		else{
			mov_index[k-2] = i;
			bit_rate[k-2] = t_bytes;
			t_bytes=0;
			k++;			
		}
	}

	printf(" \n\n\n **************** Moving bitrate (kbps) ***************\n\n");
	for(int i=0; i<28; i++){
		printf("%f, ", (double)(bit_rate[i])*8/1000);
	}
	

	printf("\n\n\n");
	
	/****************************************************************************/
	/****************************************************************************/

	return 0;		
}
