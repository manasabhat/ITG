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
