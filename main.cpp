/*
"Intelligent Thumbnails Generation" done as 
(1)Intenrship in SARANYU TECHNOLOGIES
(2)Final year Project
Author:	 1PI09IS049,
		 MANASA K,
		 ISE,
		 PESIT,
		 Bangalore.								*/

#include "header.h"

int main(int argc,char* argv[])
{
	char* vname;
//Lowest level algorithm, where the defined number of samples are taken by 
//user and he collects the required metrics from those and write all the 
//metrics to a file for further processing and save all samples in a folder 
//if required.
//These preprocessing can't be post poned. So,should be handled here only.
	if(argc<2) {
		cout<<"Please enter the video name:";
		cin>>vname;
	}
	else {
		vname = argv[1];
	}
	low_level( vname);

//File written in the lower level is taken as input and processed to get best
//thumbnails*2 no of frames and store those in an array.
	second_level();

//Expected number of thumbnails for user is selected from the already listed 
//frames and show that to user or save as needed.
	third_level();

	return(0);
}
