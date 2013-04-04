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

int low_level( char* vname)
{
	cout<<"low level()\n";

//create video capture
    create_video(vname);

//take valid frame randomly from the video
    divide_interval();

//show valid frames
    show_valid();

	return(0);
}
