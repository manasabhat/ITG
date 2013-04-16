/*
"Intelligent Thumbnails Generation" done as 
(1)Intenrship in SARANYU TECHNOLOGIES
(2)Final year Project
Author : 1PI09IS049,
         MANASA K,
         ISE,
         PESIT,
         Bangalore.							*/

#include "header.h"
CvCapture* capture;
int total_frames;
int total_samples;
int* valid_frames;
int failure_flag;
int failure_type;
int* consider_flags;
int valid_index;
IplImage* img;

IplImage* resize_image( IplImage* frame )
{
#if SHOW_IMAGE
	show_image( frame );
#endif
/*	int scale_width = frame->width/500;
	int scale_height = frame->height/500;
	if( scale_width == 0) {
		 scale_width = 1;
	}
	if(scale_height == 0) {
		scale_height =1;
	}
*/
	float aspect_ratio = (float)frame->height/frame->width;
	int res_width = 300;
	int res_height = res_width*aspect_ratio;
	IplImage* temp = cvCreateImage(cvSize(res_width,res_height),frame->depth,frame->nChannels);

//	IplImage* temp = cvCreateImage( cvSize(frame->width/scale_width,frame->height/scale_height),frame->depth,frame->nChannels);
	cvResize( frame,temp );
	//IplImage* temp = cvCreateImage( cvSize(frame->width/scale_width,frame->height/scale_height),frame->depth,frame->nChannels);
#if SHOW_IMAGE
	show_image( temp );
#endif
#if PRINT_DEBUG
	cout<<"RESIZE:"<<temp->width<<","<<temp->height<<endl;
#endif
	return(temp);
}


int check_validity(int pos,int size)
{
	float face;
	float bright;
	float blur;
	float entropy;
	float* correlations;
	int j;
	correlations = (float*)malloc(sizeof(float)*valid_index);
	int i;
#if TRACE_STEPS
	cout<<"size:"<<size<<endl;
#endif
	if(!consider_flags[REPEATED]==1) {
	for(i=0;i<size;i++) {
		if(abs(valid_frames[i]-pos)<100) {
#if TRACE_STEPS
			cout<<"rejected:repeated frames\n";
#endif
			return(REPEATED);
		}
	}
	}
	cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,pos);
	img = resize_image(cvQueryFrame(capture));
	if(!consider_flags[BRIGHTNESS]==1) {
	bright = brightness(resize_image(img));
	if(bright<0.2 ||bright>0.8) {
#if TRACE_STEPS
		cout<<"reject : brightness out of range\n";
#endif
		return(BRIGHTNESS);
	}
	}
	if(!consider_flags[FACE]) {
	face = detect_draw(resize_image(img));
#if PRINT_DEBUG
	cout<<"face:"<<face<<endl;
#endif
	if(face==0) {
#if TRACE_STEPS
		cout<<"reject : no faces found \n";
#endif
		return(FACE);
	}
	}
	if(!consider_flags[BLUR]) {
	blur = blurriness(resize_image(img));
#if TRACE_STEPS
	cout<<"blur:"<<blur<<endl;
#endif
	if(blur>0.7) {
#if TRACE_STEPS
		cout<<"reject : blur is out of range\n";
#endif
		return(BLUR);
	}
	}
	if(!consider_flags[ENTROPY]) {
	entropy = randomness( resize_image(img));
#if TRACE_STEPS
	cout<<"entropy:"<<entropy<<endl;
#endif
	if(entropy<0.015) {
#if TRACE_STEPS
		cout<<"rejected : less entropy "<<entropy<<endl;
#endif
		return(ENTROPY);
	}
	}
//find correlations with respect to the previously saved frames
	for(j=0;j<valid_index;j++) {
		correlations[j] = correlation(*samples[j],*img);
#if PRINT_DEBUG
		cout<<"j:"<<j<<"valid_index:"<<valid_index<<endl;
		cvShowImage("image in check - sample",samples[j]);
		cvWaitKey(0);
		cvShowImage("image in check - img",img);
		cvWaitKey(0);
#endif
	}
	
#if WRITE_FILE
	(*fout)<<valid_index<<"\t"<<pos<<"\t"<<bright<<"\t"<<face<<"\t"<<blur
	<<"\t"<<entropy<<"\t";
	for(j=0;j<valid_index;j++) {
		(*fout)<<correlations[j]<<"\t";
	}
	(*fout)<<endl;
#endif
	return(0);
}

int collect_valid(int start,int end)
{
	consider_flags = (int*)malloc(sizeof(int)*6);
	failure_type =0;
	int count_failure =0;
	int valid =0;
	int pos; 
	int i;
	for(i=0;i<6;i++) {
		consider_flags[i]=0;
	}
	i =0;
#if TRACE_STEPS
	cout<<"total samples required:"<<total_samples<<endl;
#endif
	while(i<total_samples) {
		pos = (rand()%(end-start))+start;
#if TRACE_STEPS
		cout<<"pos:"<<pos<<endl;
#endif
		valid = check_validity(pos,i);
		if(count_failure>0 && failure_type==valid) {
			count_failure++;
		}
		if(count_failure==0) {
			failure_type = valid;
			if(valid) {
				count_failure++;	
			}
		}
		if(count_failure==5) {
			consider_flags[0]=1;
			consider_flags[failure_type]=1;
		}
#if TRACE_STEPS
		cout<<"count failure:"<<count_failure<<"\nvalid:"<<valid<<endl;
#endif
		if(!count_failure && !valid) {
			valid_frames[valid_index]=pos;
			samples[valid_index] = cvCreateImage( cvSize(img->width,img->height),img->depth,img->nChannels);
			cvCopy(img,samples[valid_index]);
			valid_index++;
#if TRACE_STEPS
			cout<<"valid_index:"<<valid_index<<endl;
#endif
			i++;
#if TRACE_STEPS
			cout<<"i:"<<i<<endl;
#endif
		}
		valid =0;
		count_failure = 0;
	}
	return(0);
}

int show_valid()
{
	string file_path;
	IplImage* frame;
	int i;
	int j;
#if TRACE_STEPS
	cout<<"show all valid frames:\n";
#endif
#if PRINT_DEBUG
#if WRITE_FILE
	(*fout)<<"show all valid frames:\n";
#endif
#endif
	
//show the stored frame numbers & if possible frames from video also
	for(i=0;i<total_samples*total_interval;i++) {	
		std::ostringstream file_name;
#if TRACE_STEPS
		cout<<valid_frames[i]<<endl;
#endif
#if PRINT_DEBUG
#if WRITE_FILE
		(*fout)<<valid_frames[i]<<endl;
#endif
#endif
		cout<<"op :"<<op_path<<endl;
		file_name<<"sample_thumbnail_";
		file_name<<i;
		file_name<<".jpeg";
		file_path =(string) (op_path+file_name.str());
		cout<<"file_name:"<<file_path.c_str()<<endl;
#if TRACE_STEPS
		cout<<"names:"<<file_path<<endl;
#endif
		cvSaveImage(file_path.c_str(),samples[i]);
		cvShowImage("frame",samples[i]);
		cvWaitKey(1000);
	}
	return(0);
}

int show_output_thumbnails()
{
	IplImage* frame;
	string file_path;
	for(int i=0;i<(n/2);i++) {
		std::ostringstream file_name;
	
		file_name<<"output_thumbnail_";
		file_name<<i;
		file_name<<".jpeg";
		file_path = string(op_path+file_name.str());
		cout<<"output file name:"<<file_path.c_str()<<endl;
		cout<<"frame no:"<<output_thumbnails[i]<<endl;
		cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,output_thumbnails[i]);
		frame = cvQueryFrame(capture);
		cvSaveImage(file_path.c_str(),frame);
		cvShowImage("output",frame);
		cvWaitKey(1000);
	}
	return(0);	
}
