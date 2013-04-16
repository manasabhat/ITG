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
int total_interval;
string op_path;
std::ofstream fp;
std::ostream* fout=&cout;
IplImage** samples;

int create_video( char* name)
{
	int n;
	capture = cvCreateFileCapture( name);
	total_frames = cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
	cout<<"total:"<<total_frames<<endl;
	cout<<"enter the number of thumbnails:"<<endl;
	cin>>n;
	total_interval = n*2;
	cout<<"enter the number of samples per interval:";
	cin>>total_samples;
//	total_samples = total_samples*2;
	valid_frames = (int*)malloc(sizeof(int)*total_interval*total_samples);
	output_path( name);
#if WRITE_FILE
	file_write();
#endif
	return(0);
}

int divide_interval()
{
	int i;
	int size;
	valid_index=0;
	size = total_frames/total_interval;
	samples = (IplImage**)malloc(sizeof(IplImage*)*total_interval*total_samples);
	for( i= 0;i<total_interval;i++) {
		collect_valid(i*size,(i+1)*size-1 );
	}
	return(0);
}

int show_image(IplImage* image)
{
	cvShowImage("image",image);
	cvWaitKey(500);
	return(0);
}

int output_path( char* video)
{
    IplImage* image;
    string ip_path;
    int k;
    int size;
    int valid;
    ip_path = video;
    size = ip_path.length();
    k =size;
    while((k!=0)&&(ip_path.substr(k-1,1)!=".")) {
        k--;
    }
    if(k!=0) {
        size = k-1;
    }
    else {
        k = size-1;
    }
    while((k!=0)&&(ip_path.substr(k-1,1)!="/")) {
#if PRINT_DEBUG
        cout<<ip_path.substr(k-1,1)<<endl;
#endif
        k--;
    }
    size = size-k;
#if PRINT_DEBUG
    cout<<"size of file name:"<<size<<endl;
#endif
    ip_path = ip_path.substr(k,size);
    ip_path = ip_path+"/";
#if TRACE_STEPS
    cout<<ip_path<<endl;
#endif
    op_path = "output_"+ip_path;
#if TRACE_STEPS
    cout<<op_path<<endl;
#endif
    mkdir(op_path.c_str(),0777);
    return(0);
                                                    
}

int file_write()
{
    string file_name;
    file_name = op_path+"file.txt";
    fp.open( file_name.c_str());
    fout = &fp;
	(*fout)<<total_frames<<"\t"<<total_samples*total_interval<<"\t"<<total_interval<<endl;
//  (*fout)<<"manasa here\n";
    return(0);
}

