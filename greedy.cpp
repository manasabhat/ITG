/*
"Intelligent Thumbnails Generation" done as 
(1)Intenrship in SARANYU TECHNOLOGIES
(2)Final year Project
Author : 1PI09IS049,
         MANASA K,
         ISE,
         PESIT,
         Bangalore.
*/
#include "header.h"

int best_frame( int start,int size)
{	
	int i;
	int j;
	int pos = size;
	int best_index = 0;
	float diff = 0.5;
	float temp;
	float temp1;
	int* local_flags = (int*)malloc(sizeof(int)*size);
//bright	
	for(i=0;i<size;i++) {
		pos = size;
		temp = fabs(bright[i+start]-0.5);
		for(j=0;j<size;j++) {
			if(i!=j) {
				temp1 = fabs(bright[j+start]-0.5);
#if PRINT_DEBUG
				cout<<"(temp,temp1):("<<temp<<","<<temp1<<")\n";
#endif
				if(temp < temp1) {
					pos--;
				}
			}
		}
		local_flags[i] = pos;
#if PRINT_DEBUG
		cout<<"pos,i:"<<pos<<"\t"<<i<<endl;
#endif
#if TRACE_STEPS
		cout<<pos<<"\t";
#endif
	}
#if TRACE_STEPS
	cout<<endl;
#endif
//blurry
	for(i=0;i<size;i++) {
		pos = size;
	    temp = blurry[i+start];
	    for(j=0;j<size;j++) {
			if( i!= j) {
		        temp1 = blurry[j+start];
		        if(temp < temp1) {
	   	     	    pos--;
   		 	    }
			}
	    }
    	local_flags[i] += pos;
#if TRACE_STEPS
		cout<<pos<<"\t";
#endif
	}
#if TRACE_STEPS
	cout<<endl;
#endif
//entropy
	for(i=0;i<size;i++) {
		pos =size;
		temp = entropy[i+start];
		for(j=0;j<size;j++) {
			if(i!=j) {
				temp1 = entropy[j+start];
				if( temp>temp1) {
					pos--;
				}
			}
		}
		local_flags[i] += pos;
#if TRACE_STEPS
		cout<<pos<<"\t";
#endif
	}
#if TRACE_STEPS
	cout<<endl;
#endif
//distance
	int prev;
	prev = flag[index_samples];
	if(index_samples>0) {
		for(i=0;i<size;i++) {
			pos = size;
			temp = frame_no[i+start]-prev;
			for(j=0;j<size;j++) {
				if(i != j) {
					if((frame_no[j+start]-prev)<temp) {
						pos--;
					}
				}
			}
			local_flags[i] += pos;
#if TRACE_STEPS
			cout<<pos<<"\t";
#endif
		}
	}
#if TRACE_STEPS
	cout<<endl;
#endif
//correlation - the one which has least correlation
//create a temporary location where sum of correlations for all the images are stored
//then ge tthe least based on that
	float temp_sum=0;
	float next_sum =0;
	int k;
	float* sum = (float*)malloc(sizeof(float)*size);
	for(i=0;i<index_samples;i++) {
		for(j=0;j<size;j++) {
			sum[j] += correlations[j+start][flag[i]];
		}
	}
	for(i=0;i<size;i++) {
		pos = size;
		for(j=0;j<size;j++) {
			if(sum[i]<sum[j]) {
				pos--;
			}
		}
		local_flags[i] += pos;
#if TRACE_STEPS
		cout<<pos<<"\t";
#endif
	}
	cout<<endl;

	for(i=0;i<size;i++) {
		cout<<local_flags[i]<<"\t";
	}
	cout<<endl;
	best_index = minimum_pos( local_flags,size);

#if PRINT_DEBUG
	cout<<"start:"<<start<<endl;
#endif
	return(best_index+start);
}

int greedy()
{
//Get the mean and sdv of bright, blurry and entropy
//For those which are in range, make flag 1
//Consider only those who have flag 1, arrange them in decreasing order of entropy
//Pick the best with minimum distance
	int i;
	int pos;
	int size = total_samples/n;
	abs_metrics = (float**) malloc(sizeof(float*)*n);
	for(i=0;i<n;i++) {
		abs_metrics[i] = (float*)malloc(sizeof(float)*size);
	}
	abs_metric_calc();
	cout<<"size:"<<size<<endl;
	flag = (int*)malloc(sizeof(int)*n);
	index_samples=0;
	while(index_samples<n) {
		pos = best_frame(index_samples*size,size);
		flag[index_samples] = pos;
		index_samples++;
	}
	return(0);
}
