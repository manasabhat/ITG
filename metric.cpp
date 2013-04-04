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

float brightness(IplImage* image)
{
	IplImage* temp;
    temp = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,3);
    cvCvtColor( image,temp,CV_RGB2YCrCb);
    cvSetImageCOI(temp,1);
    CvScalar scal = cvAvg( temp );
    float metric = (float)scal.val[0]/255;
    return(metric);
}

float blurriness( IplImage* image)
{

	IplImage* clm_dst = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
IplImage* row_dst = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
IplImage* act_var_v = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
IplImage* act_var_h = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
IplImage* blur_var_v = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
IplImage* blur_var_h = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
IplImage* var_v = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
IplImage* var_h = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
IplImage* diff_v = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
IplImage* diff_h = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
	
	IplImage* temp = cvCreateImage( cvSize(image->width,image->height),image->depth,image->nChannels);
	cvCopy( image,temp);
#if PRINT_DEBUG
	if(glb_img==NULL) {
		cout<<"global image is Null\n";
	}
	cout<<"global image type:"<<glb_img->width<<","<<glb_img->height<<endl;
	cout<<"temp img type:"<<temp->width<<","<<temp->height<<endl;
#endif
//	clm_dst = cvCreateImage( cvSize(image->width,image->height),image->depth,image->nChannels);
//	row_dst = cvCreateImage( cvSize(image->width,image->height),image->depth,image->nChannels);
	
	cvSmooth( temp,row_dst,CV_BLUR,1,9);
	cvSmooth( temp,clm_dst,CV_BLUR,9,1);
#if SHOW_IMAGE
	cvShowImage("act image",image);
	cvWaitKey(0);
	cvShowImage("row dst",row_dst);
	cvWaitKey(0);
	cvShowImage("clm dst",clm_dst);
	cvWaitKey(0);
	cvCvtColor(row_dst,row_dst,CV_RGB2YCrCb);
	cvCvtColor(clm_dst,clm_dst,CV_RGB2YCrCb);
	cvShowImage("row dst",row_dst);
	cvWaitKey(0);
	cvShowImage("clm dst",clm_dst);
	cvWaitKey(0);
#endif

//	act_var_v = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_32F,image->nChannels);
//	act_var_h = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_32F,image->nChannels);
//	blur_var_v = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_32F,image->nChannels);
//	blur_var_h = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_32F,image->nChannels);
	
	int i,j;
	CvScalar scal;
	CvScalar scal1;
	CvScalar scal2;
    for( i=0;i<image->height;i++) {
         for( j=0;j<(image->width-1);j++) {
             scal1 = cvGet2D(image,i,j);
             scal2 = cvGet2D(image,i,j+1);
             scal.val[0] = abs(scal1.val[0] - scal2.val[0]);
             cvSet2D(act_var_h,i,j,scal);
//             cout<<scal.val[0]<<" ";
         }
		 scal.val[0] = 0;
		 cvSet2D(act_var_h,i,j,scal);
//         cout<<"\n";
     }
//	 cout<<"*********************************************\n";
//	 cout<<"2nd part"<<endl;
     for( i=0;i<image->width;i++) {
         for( j=0;j<(image->height-1);j++) {
             scal1 = cvGet2D( image,j,i);
             scal2 = cvGet2D( image,j+1,i);
             scal.val[0] = abs(scal1.val[0] - scal2.val[0]);
             cvSet2D(act_var_v,j,i,scal);
//             cout<<scal.val[0]<<" ";
         }
		 scal.val[0] = 0;
		 cvSet2D(act_var_v,j,i,scal);
//         cout<<"\n";
     }

	for( i=0;i<image->height;i++) {
		for( j=0;j<(image->width-1);j++) {
			scal1 = cvGet2D(row_dst,i,j);
			scal2 = cvGet2D(row_dst,i,j+1);
			scal.val[0] = abs(scal1.val[0] - scal2.val[0]);
			cvSet2D(blur_var_h,i,j,scal);
//			cout<<scal.val[0]<<" ";
		}
		scal.val[0] = 0;
		cvSet2D(blur_var_h,i,j,scal);
//		cout<<"\n";
	}
//	cout<<"*********************************************\n";
//	cout<<"2nd part"<<endl;
	for( i=0;i<image->width;i++) {
		for( j=0;j<(image->height-1);j++) {
			scal1 = cvGet2D( clm_dst,j,i);
			scal2 = cvGet2D( clm_dst,j+1,i);
			scal.val[0] = abs(scal1.val[0] - scal2.val[0]);
			cvSet2D(blur_var_v,j,i,scal);
//			cout<<scal.val[0]<<" ";
		}
		scal.val[0] = 0;
		cvSet2D(blur_var_v,j,i,scal);

//		cout<<"\n";
	}
#if PRINT_DEBUG
	cout<<"image:"<<image->width<<" "<<image->height<<endl;
	cout<<"image:"<<image->width<<" "<<image->height<<endl;
	cout<<"act_v:"<<act_var_v->width<<" "<<act_var_h->height<<endl;
	cout<<"act_h:"<<act_var_h->width<<" "<<act_var_h->height<<endl;
	cout<<"blur_v:"<<blur_var_v->width<<" "<<blur_var_h->height<<endl;
	cout<<"blur_h:"<<blur_var_h->width<<" "<<blur_var_h->height<<endl;
#endif

//	diff_v = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_32F,image->nChannels);
//	diff_h = cvCreateImage( cvSize(image->width,image->height),IPL_DEPTH_32F,image->nChannels);
	for(i=0;i<image->height;i++) {
		for(j=0;j<image->width;j++) {
			scal1 = cvGet2D(act_var_v,i,j);
			scal2 = cvGet2D(blur_var_v,i,j);
			scal.val[0] = abs(scal1.val[0] - scal2.val[0]);
//			cout<<scal.val[0]<<" ";
			cvSet2D( diff_v,i,j,scal);
		}
//		cout<<"("<<i<<","<<j<<")\n";
	}
//	cout<<"diff: ("<<diff_v->height<<","<<diff_v->width<<")\n";
	for( i=0;i<act_var_h->height;i++) {
	    for( j=0;j<act_var_h->width;j++) {
		    scal1 = cvGet2D(act_var_h,i,j);
    	    scal2 = cvGet2D(blur_var_h,i,j);
	        scal.val[0] = abs(scal1.val[0] - scal2.val[0]);
//			cout<<scal.val[0]<<" ";
        	cvSet2D( diff_h,i,j,scal);
	  	}
//		cout<<endl;
	}   

	int max = 0;
//	var_v = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_32F,image->nChannels);
//	var_h = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_32F,image->nChannels);
	
	for(i=0;i<image->height;i++) {
		for( j=0;j<image->width;j++) {	
			scal = cvGet2D(diff_v,i,j);
			if(max<scal.val[0]) {
				max = scal.val[0];
			}
		}
	}
#if PRINT_DEBUG
	cout<<"max buff_v:"<<max<<endl;
#endif
	for(i=0;i<image->height;i++) {
		for(j=0;j<image->width;j++) {
			scal.val[0] = max;
			cvSet2D(var_v,i,j,scal);
		}
	}

	max = 0;
	for(i=0;i<image->height;i++) {
    for( j=0;j<image->width;j++) {
        scal = cvGet2D(diff_h,i,j);
	        if(max<scal.val[0]) {
	            max = scal.val[0];
	        }   
	    }   
	} 
#if PRINT_DEBUG  
	cout<<"max buff_h:"<<max<<endl;
#endif
	for(i=0;i<image->height;i++) {
	    for(j=0;j<image->width;j++) {
	        scal.val[0] = max;
	        cvSet2D(var_h,i,j,scal);
	    }
	}
	int act_sum_v =0;
	int act_sum_h =0;
	int diff_sum_v =0;
	int diff_sum_h =0;
	for(i=0;i<image->height;i++) {
		for(j=0;j<image->width;j++) {
			scal = cvGet2D(act_var_v,i,j);
			act_sum_v += scal.val[0];
		}
	}
	for(i=0;i<image->height;i++) {
		for(j=0;j<image->width;j++) {
			scal = cvGet2D( act_var_h,i,j);
			act_sum_h += scal.val[0];
		}
	}
	for(i=0;i<image->height;i++) {
	    for(j=0;j<image->width;j++) {
	        scal = cvGet2D( diff_v,i,j);
	        diff_sum_v += scal.val[0];
    	}
	}
	for(i=0;i<image->height;i++) {
	    for(j=0;j<image->width;j++) {
	        scal = cvGet2D( diff_h,i,j);
	        diff_sum_h += scal.val[0];
	    }
	}
#if PRINT_DEBUG
	cout<<"actual image sum of vertical variation : "<<act_sum_v<<endl;
	cout<<"horizontal : "<<act_sum_h<<endl;
	cout<<"sum of defference of variation vertically:"<<diff_sum_v<<endl;
	cout<<"horizontally:"<<diff_sum_h<<endl;
#endif
	float blur_v=0 ;
	float blur_h=0;
	float blur =0;
	blur_v = (float)abs(act_sum_v - diff_sum_v)/act_sum_v;
	blur_h = (float)abs(act_sum_h - diff_sum_h)/act_sum_h;
#if PRINT_DEBUG
	cout<<"blur metrics: vertically:"<<blur_v<<endl;
	cout<<"              horizontally:"<<blur_h<<endl;
#endif
	if( blur_v>	blur_h) {
		blur = blur_v;
	}
	else
		blur = blur_h;
#if PRINT_DEBUG
	cout<<"blur:"<<blur<<endl;
#endif
	return(blur);
}


int detect_draw(IplImage* img)
{
	char* cascadename = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*) cvLoad(cascadename,0,0,0);
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* objects;
	CvSeq* temp_obj;
	static CvScalar colors[]={ {{0,0,255}},{{0,128,255}},{{0,255,255}},{{0,255,0}},
    {{255,128,0}},{{255,255,0}},{{255,0,0}},{{255,0,255}} };


	int total_faces = 0;
#if PRINT_DEBUG
    cout<<"detect and draw\n";
#endif
    //char *cascadename = "/usr/local/share/OpenCV/haarcascades/haarcascade_eye.xml";	
	IplImage* temp = resize_image(img);
//	temp = resize_image(img);
	cvSmooth( temp,temp,CV_GAUSSIAN );
#if PRINT_DEBUG
	cout<<"after smooth\n";
#endif
#if SHOW_IMAGE
	show_image( temp );
#endif
	//CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*) cvLoadHaarClassifierCascade(cascadename,0,0,0);
	//cvEqualizeHist( temp,temp ); - should be a 8 bit 1 channel image
	int total = temp->height*temp->width;
	cvClearMemStorage( storage );
	//CvSeq* objects = cvHaarDetectObjects( small_img,cascade,storage,1.1,2,0,cvSize(30,30));
	objects = cvHaarDetectObjects( temp,cascade,storage,1.2,2,CV_HAAR_DO_CANNY_PRUNING,cvSize(5,5),cvSize(img->height,img->width));//cvSize(img->height,img->width));//cvSize(30,30));
	float entropy_face;
	total_faces = objects->total;
	CvRect* r;
	//int cvRunHaarClassifierCascade(const CvHaarClassifierCascade* cascade, CvPoint pt, int start_stage=0 )
    for(int i=0;i< (objects? objects->total : 0) ; i++) {
		r = (CvRect*)cvGetSeqElem( objects,i );
		cvRectangle(temp,cvPoint(r->x,r->y),cvPoint(r->x+r->width,r->y+r->height),colors[5]);
#if PRINT_DEBUG
		cout<<"("<<r->x<<","<<r->y<<")"<<endl;
		cout<<"("<<r->width<<","<<r->height<<")"<<endl;
#endif
#if TRACE_IMAGE
		cvShowImage("image with rect", temp);
		cvWaitKey(100);
#endif
	}
#if PRINT_DEBUG
		cout<<"faces:"<<total_faces<<endl;
#endif
    if(total_faces != 0 ) {
#if TRACE_IMAGE
		show_image(temp);
#endif
#if SHOW_IMAGE
		show_image( temp );
#endif
	}
#if PRINT_DEBUG 
	cout<<"end of detect and draw\n";
#endif
	return( total_faces );
}


float randomness( IplImage* image )
{
	float entropy;
	int total = (image->height-2)*(image->width-2);
	int diff = 0;
	int i=0;
	int j=0;
#if SHOW_IMAGE	
	cvShowImage("image",image);
	cvWaitKey(0);
#endif
	CvScalar scal1,scal2,scal3,scal4,scal5,scal6,scal7,scal8,scal;
	for(i=1; i<image->height-1; i++) {
		for(j=1; j<image->width-1; j++) {
//			cout<<"(i,j):("<<i<<","<<j<<")\n";
			scal1 = cvGet2D(image,i-1,j-1 );
			scal2 = cvGet2D(image,i-1,j);
			scal3 = cvGet2D(image,i-1,j+1);
			scal4 = cvGet2D(image,i,j+1);
			scal5 = cvGet2D(image,i+1,j+1);
			scal6 = cvGet2D(image,i+1,j);
			scal7 = cvGet2D(image,i+1,j-1);
			scal8 = cvGet2D(image,i,j-1);
			scal = cvGet2D(image,i,j);
			diff += abs(scal.val[0]-scal1.val[0])+abs(scal.val[0]-scal2.val[0])
				+abs(scal.val[0]-scal3.val[0])+abs(scal.val[0]-scal4.val[0])
				+abs(scal.val[0]-scal5.val[0])+abs(scal.val[0]-scal6.val[0])
				+abs(scal.val[0]-scal7.val[0])+abs(scal.val[0]-scal8.val[0]);
			
		}
	}
	entropy = ((float)diff)/((total)*6);
#if PRINT_DEBUG
	cout<<"total:"<<total<<endl;
	cout<<"diff : "<<diff<<endl;
	cout<<"entropy is:"<<entropy<<endl;
#endif
	return(entropy);
}

float correlation( IplImage img1,IplImage img2) 
{
#if PRINT_DEBUGS
	cvShowImage("img1",&img1);
	cvWaitKey(0);
	cvShowImage("img2",&img2);
	cvWaitKey(0);
#endif
	IplImage* res = cvCreateImage(cvSize(1,1),IPL_DEPTH_32F,1);
	cvMatchTemplate(&img1,&img2,res,CV_TM_CCORR_NORMED);
	CvScalar scal = cvGet2D( res,0,0);
	return( scal.val[0]);
}
