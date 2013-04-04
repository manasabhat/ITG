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

int second_level()
{
	cout<<"second level: op_path "<<op_path<<"\n";
	
//calling parse with proper file name as suffix to the folder name
	parse((char*) (op_path+"file.txt").c_str() );

//calling greedy 
//	greedy();

//OR
//calling backtracking programming 
	backtracking();

//show the thumbnails
	show_frames(flag,n);

	return(0);
}
