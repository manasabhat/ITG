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
ifstream myfile;
int* frame_no;
float* face;
float* bright;
float* blurry;
float* entropy;
float** correlations;
int n;
int* flag;
int index_samples;
float** abs_metrics;
int* thumbnails;

int parse( char* fname)
{
	int j;
	int i;
//	int total;
//	int n;
	float value;
	cout<<"parse\n";
	ifstream myfile(fname,ifstream::in);
//	ifstream myfile("input/file.txt",ifstream::in);
	myfile>>total_frames;
	myfile>>total_samples;
//	frame* frames;
//	frames = (frame*)malloc(sizeof(frame)*total);
	frame_no = (int*)malloc(sizeof(int)*total_samples);
	face = (float*) malloc(sizeof(int)*total_samples);
	bright = (float*)malloc(sizeof(int)*total_samples);
	blurry = (float*)malloc(sizeof(int)*total_samples);
	entropy = (float*)malloc(sizeof(int)*total_samples);
	correlations = (float**)malloc(sizeof(float*)*total_samples);
	for(int i=0;i<total_samples;i++) {
		correlations[i] = (float*)malloc(sizeof(int)*i);
	}
	cout<<"no of frames taken as samples:"<<total_samples<<endl;
	myfile>>n;
	cout<<"no of frames expected from user:"<<n<<endl;
	i=0;
	while(i<total_samples) {
		myfile>>value;
		myfile>>value;
		frame_no[i] = value;
		myfile>>value;
		bright[i] = value;
		myfile>>value;
		face[i] = value;
		myfile>>value;
		blurry[i] = value;
		myfile>>value;
		entropy[i]=value;
		for(j=0;j<i;j++) {
			myfile>>value;
			correlations[i][j] = value;
		}
//		cout<<"value:"<<value<<endl;
		i++;
	}		
	return(0);
}

int display()
{
	int i;
	for(i=0;i<total_samples;i++) {
		cout<<frame_no[i]<<"\t"<<bright[i]<<"\t"<<face[i]<<"\t"
		<<blurry[i]<<"\t"<<entropy[i]<<"\t";
		for(int j=0;j<i;j++) {
			cout<<correlations[i][j]<<"\t";
		}
		cout<<endl;
	}

	return(0);
}
	
int show_frames( int* thumbnails,int size)
{
	cout<<"show frame no:\n";
	for(int i=0;i<size;i++) {
		thumbnails[i] = frame_no[thumbnails[i]];
		cout<<thumbnails[i]<<endl;
	}
	return(0);
}

int abs_metric_calc()
{
	int i,j;
	int size = total_samples/n;
	float res;
	cout<<"abs metric calc\n";
	
//brightness,blurriness,entropy,randomness
	for(i=0;i<n;i++) {
		for(j=0;j<size;j++) {
			res = 1 - fabs(bright[i*size+j] -0.5) *2;
			abs_metrics[i][j] = res*0.125;
			res = 1 - blurry[i*size+j];
			abs_metrics[i][j] += res*0.125;
			res = entropy[i*size+j];
			res = (res)/5.0;
			abs_metrics[i][j] += res*0.125;
			res = 1 - fabs(face[i*size+j] - 0.25);
			abs_metrics[i][j] += res*0.125;
		}
	}

	return(0);
}

int show_frame_no()
{
	cout<<"total sample:"<<total_samples<<endl;
	cout<<"n:"<<n<<endl;
	int size = total_samples/n;
	cout<<"size:"<<size<<endl;
	int i;
	for(i=0;i<n;i++) {
//		cout<<frame_no[flag[i]]<<"\t";
		cout<<flag[i]<<"\t";
	}
	cout<<endl;
	return(0);
}

int minimum_pos( int* array,int size )
{
	int pos =0;
	int i;
	int temp = array[0];
	for(i=0;i<size;i++) {
#if PRINT_DEBUG
		cout<<array[i]<<"\t";
#endif
		if(array[i]<temp) {
			pos = i;
			temp = array[i];
		}
	}
	return(pos);
}
