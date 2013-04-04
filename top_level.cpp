#include "header.h"
int* output_thumbnails;

int top_level()
{
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

	for( int i=0;i<n;i++) {
			cout<<"index:"<<flag[i]<<"\t";
			cout<<abs_metrics[i][flag[i]]<<endl;
	}

	while( index_thumbnail<n/2) {
		max_val =-1;
		max_ind =0;
		for(int i=0;i<n;i++) {
			cout<<"i:"<<i<<endl;
			flag_thumbnail =1;
			int k = index_thumbnail;
			if(!k) {
				pres_val = abs_metrics[i][flag[i]];
			}
			else {
				pres_val = 0;
			}
			pres = flag[i];
			while ( k && flag_thumbnail) {
				cout<<"k:"<<k<<endl;
				k--;
				cout<<"already:"<<output_thumbnails[k]<<endl;
				cout<<"present:"<<pres<<endl;
				if( pres ==output_thumbnails[k] ) {
					flag_thumbnail =0;
				}
				else {
					if(pres>output_thumbnails[k]) {
						pres_val += 1-correlations[pres%size][output_thumbnails[k]%size];
					}
					else {
						pres_val += 1-correlations[output_thumbnails[k]%size][pres%size];
					}
					pres_val += abs(frame_no[pres]-frame_no[output_thumbnails[k]])/size_in_frames;
					cout<<frame_no[pres]<<endl;
				}
			}
			if( flag_thumbnail && (pres_val > max_val)) {
				max_ind = i;
				max_val = pres_val;
				cout<<"better than previous:"<<flag[max_ind]<<endl;
			}
		}
		output_thumbnails[index_thumbnail] = flag[max_ind];
		cout<<"output_thumbnails:"<<output_thumbnails[index_thumbnail]<<endl;
		index_thumbnail++;
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

