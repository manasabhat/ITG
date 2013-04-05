/*
"Intelligent Thumbnails Generation" done as 
(1)Intenrship in SARANYU TECHNOLOGIES
(2)Final year Project
Author : 1PI09IS049,
         MANASA K,
         ISE,
         PESIT,
         Bangalore.							*/

#include<highgui.h>
#include<string.h>
#include<cv.h>
#include "sys/stat.h"
#include<math.h>
#include<stdlib.h>
#include<sstream>
#include<fstream>
#include<iostream>
#define TRACE_IMAGE 0
#define SHOW_IMAGE 0
#define TRACE_STEPS 1
#define PRINT_DEBUG 0
#define WRITE_FILE 1
#define REPEATED 1
#define BRIGHTNESS 2
#define FACE 3
#define BLUR 4
#define ENTROPY 5

using namespace std;
using namespace cv;

//global variables for low level
extern CvCapture* capture;
extern int total_frames;
extern int total_interval;
extern int total_samples;
extern int* valid_frames;
extern int valid_index;
extern string op_path;
extern std::ofstream fp;
extern std::ostream* fout;
extern IplImage** samples;
extern IplImage* img;

//global variables for second level & third level
extern ifstream myfile;
extern int* frame_no;
extern float* face;
extern float* bright;
extern float* blurry;
extern float* entropy;
extern float** correlations;
extern int n;
extern int* flag;
extern int index_samples;
extern float** abs_metrics;
extern int* output_thumbnails;

//three levels
int low_level( char*);
int second_level();
int third_level();

//functions of low levels
int create_video(char*);
int divide_interval();
int output_path(char*);
int file_write();
int show_image(IplImage*);
float brightness(IplImage*);
float blurriness(IplImage*);
float correlation( IplImage,IplImage);
float detect_draw(IplImage*);
float randomness(IplImage*);
IplImage* resize_image(IplImage*);
int check_validity(int,int);
int collect_valid(int,int);
int show_valid();

//functions of second level
int greedy();
int parse(char*);
int process();
int show_frame_no();
int best_frame( int,int);
int minimum_pos(int*,int);
int abs_metric_calc();
int show_frames(int*,int);
int backtracking();

//functions of third level
int top_level();
int show_output_thumbnails();
