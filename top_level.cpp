/*
"Intelligent Thumbnails Generation" done as 
(1)Intenrship in SARANYU TECHNOLOGIES
(2)Final year Project
Author : 1PI09IS049,
         MANASA K,
         ISE,
         PESIT,
         Bangalore.								*/

#include "header.h"
int* output_thumbnails;

int top_level()
{
	int k;
	int pres;
	float max_val;
	float pres_val;
	int flag_thumbnail;
	int max_ind;
	int index_thumbnail =0;
	float res;
	int size = total_samples/n;
	int size_in_frames = total_frames*2/n;
	output_thumbnails = (int*)malloc(sizeof(int)*(n/2));
	cout<<"flags:"<<endl;
	for(int i=0;i<n;i++) {
//		flag[i] = flag[i]+i*size;
		cout<<flag[i]<<"\t";
	}
	cout<<endl;

	cout<<"n/2:"<<n/2<<endl;
	
	max_val =0;
	for( int i=0;i<n;i++) {
			cout<<"index:"<<flag[i]<<"\t";
			pres_val = abs_metrics[i][flag[i]%size];
			cout<<pres_val<<endl;
			if(pres_val>max_val) {
				max_val = pres_val;
				max_ind = i;
			}
	}
	output_thumbnails[0] = flag[max_ind];
	index_thumbnail++;

	pres_val = pres = 0;	
	max_val = max_ind = 0;
	int reference;
	while(index_thumbnail < n/2) {
		for( int i=0;i<n;i++) {
			k = index_thumbnail;
			pres = flag[i];
			cout<<"k:"<<k<<endl;
			flag_thumbnail = 1;
			while(k--) {
				if(output_thumbnails[k] == pres) {
					flag_thumbnail = 0;	
				}
			}
			k = index_thumbnail;
			if(flag_thumbnail) {
				while(k--) {
					reference = output_thumbnails[k];
					cout<<"k:"<<k<<"\t"<<reference<<"\t"<<pres<<endl;
						cout<<"k:"<<k<<"\t"<<reference<<"\t"<<pres<<"\t";
						if(reference < pres ) {
							pres_val += 1-correlations[reference][pres];
						}
						else {
							pres_val += 1-correlations[pres][reference];
						}
						pres_val += fabs(frame_no[pres] - frame_no[reference]);
						cout<<pres_val<<endl;
				}
				if( pres_val>max_val) {
					max_val = pres_val;
					max_ind = pres;
				}	
			}
		}
		output_thumbnails[index_thumbnail++] = max_ind;
	}

//see the valid frame numbers		
	for(int i=0;i<n/2;i++) {
		cout<<" i:"<<output_thumbnails[i]<<endl;
	}
//final selection algorithm : where each frame is *as far from other and
//												  *as different as possible
	
	show_output_thumbnails();

	return(0);
}

