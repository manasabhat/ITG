#include "header.h"

int show_valid(int* flag)
{
	int size = total_samples/n;
	int i;
	for(i=0;i<n;i++) {
#if PRINT_DEBUG
//		cout<<frame_no[flag[i]]<<"\t";
#endif
//		cout<<flag[i]+i*size<<"\t";
		cout<<flag[i]<<"\t";
	}
	cout<<endl;
	return(0);
}

float get_correlation( int* flag)
{
#if PRINT_DEBUGS
	cout<<"flags:"<<endl;
	show_valid(flag);
	cout<<"get correlations:"<<endl;
#endif
	int size = total_samples/n;
	float res;
	for(int i=0;i<n;i++) {
		for( int j=i+1;j<n;j++) {
			res += correlations[flag[j]+j*size][flag[i]+i*size];
#if PRINT_DEBUG
			cout<<"("<<flag[j]+j*size<<","<<flag[i]+i*size<<")\t";
			cout<<correlations[flag[j]+j*size][flag[i]+i*size]<<"\t";
#endif
		}
	}
	return( res);
}

int initialize_stack(int* stack)
{
	index_samples=0;
	while(index_samples<n) {
		stack[index_samples++] = 0;
	}
}

int stack_empty(int* stack) 
{
#if TRACE_STEPS
	cout<<"stack empty index_samples:"<<index_samples<<endl;
#endif
	if(index_samples<0) {
		return(0);
	}
	else {
		return(1);
	}
}

int stack_pop_push( int* stack) 
{
	int temp;
	int size = total_samples/n;
	temp = stack[--index_samples];
#if TRACE_STEPS
	cout<<"index_samples:"<<index_samples<<endl;
#endif
	temp = temp+1;
	if(temp == size) {
		if(index_samples==0) {
			index_samples = -1;
			return(0);
		}
		else {
			temp = temp%size;
			if(!stack_pop_push(stack)) {
				return(0);
			}
		}
	}
	stack[index_samples++] = temp;
	return(1);
}

int show_stack(int* stack) 
{
	cout<<"show stack:"<<endl;
	for(int i=0;i<n;i++) {
		cout<<stack[i]<<"\t";
	}
	cout<<endl;
}

int copy(int* src,int* dst,int size) 
{
	int interval_size = total_samples/n;
	for(int i=0;i<size;i++) {
		dst[i] = src[i]+i*interval_size ;
	}
	return(0);
}


int show_matrix(float** matrix,int rows,int cols) 
{	
	for(int i=0;i<rows;i++) {
		for(int j=0;j<cols;j++) {
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
	return(0);
}

float get_path_metrics( int* flag)
{
#if PRINT_DEBUGS
	cout<<"flags:"<<endl;
	show_valid(flag);
	cout<<"get correlations:"<<endl;
#endif
	int freq=0;
	float distance;
	int size = total_samples/n;
	float res;
	for(int i=0;i<n;i++) {
		for( int j=i+1;j<n;j++) {
			freq++;
			res += (1-correlations[flag[j]+j*size][flag[i]+i*size]);
#if PRINT_DEBUG
			cout<<"("<<flag[j]+j*size<<","<<flag[i]+i*size<<")\t";
			cout<<correlations[flag[j]+j*size][flag[i]+i*size]<<"\t";
#endif
		}
	}
	res = res/freq;
	for(int i=0;i<n-1;i++) {
	distance += (frame_no[flag[i+1]] - frame_no[flag[i]]);
	}
	distance = distance/(n);
	distance = distance*0.125;
	res = distance + res*0.125;
	
	for(int i=0;i<n;i++) {
		res += abs_metrics[i][flag[i]];
	}

	return( res);
}

int backtracking()
{
//Find the setof frames which minimizes the correlation as we done in ITG_3.2
//and also consider other metrics with meaningful weightage as follows
//	 metric			weightage	where(path traversal)
//(1)correlation	0.25		on fly
//(2)distance		0.25		on fly
//(3)brightness		0.125		|
//(4)blurriness		0.125		|________ create a matrix with weighted value
//(5)entropy		0.125		|			(of these 4 metrics)
//(6)face			0.125		|


	int i;
	int pos;
	int size = total_samples/n;
	abs_metrics = (float**)malloc(sizeof(float*)*n);
	for(i=0;i<n;i++) {
		abs_metrics[i]=(float*)malloc(sizeof(float)*size);
	}
	float best_metric;	
	cout<<"size:"<<size<<endl;
	flag = (int*) malloc(sizeof(int)*n);
	int* stack = (int*) malloc(sizeof(int)*n);
	index_samples =0;
//create a matrix with weighted value of all 4 metrics
// -brightness, -blurriness, -entropy, -face metric
	abs_metric_calc();
//show a 2D matrix
	show_matrix( abs_metrics,n,size);

	initialize_stack(stack );
#if TRACE_STEPS
	show_valid(stack);
#endif
	float present;
	i=0;
//	while(i<pow(size,n)) {
	while(stack_empty(stack)) {
#if TRACE_STEPS
		cout<<"i:"<<i<<endl;
		show_valid(stack);
#endif
		present = get_path_metrics(stack);
		if(i==0) {
			best_metric = present;
			copy(stack,flag,n);
#if PRINT_DEBUG
			cout<<"present:"<<present<<endl;
#endif
		}
		else if(present>best_metric) {
			best_metric = present;
			copy(stack,flag,n);
#if PRINT_DEBUG
			cout<<"present<best_corr:"<<best_metric<<endl;
			show_valid( flag);
#endif
		}
#if PRINT_DEBUG
		cout<<"correlation:"<<present<<"\t";
#endif
		stack_pop_push(stack);
		i++;
	}		
	return(0);
}
