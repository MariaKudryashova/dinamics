#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include "estimate.h"
#include <malloc.h>
#include <time.h>

int N;
int min_m;
int max_m;
int speed_m;
double min_eps;
double max_eps;
double speed_eps;
double p;
char NAME_FILERESULT[50];
char NAME_DATAFILE[50];
double *data; //динамический массив

//const char* NAME_DATAFILE = "data100.txt";

int read_file() 
{
	FILE *f; 
	f=fopen("config.txt","r");	
    int i;
	char name[512];
	
	fscanf(f,"%i",&N);
	fscanf(f,"%i",&min_m);
	fscanf(f,"%i",&max_m);
	fscanf(f,"%i",&speed_m);
	fscanf(f,"%lf",&min_eps);
	fscanf(f,"%lf",&max_eps);
	fscanf(f,"%lf",&speed_eps);
	fscanf(f,"%lf",&p);
	fscanf(f,"%s",&NAME_DATAFILE);
	fscanf(f,"%s",&NAME_FILERESULT);
	

	//printf("N: %i\n", N);
	//printf("min_m: %i\n", min_m);
    //printf("max_m: %i\n", max_m);
	//printf("speed_m: %i\n", speed_m);
	//printf("min_eps: %lf\n", min_eps);
	//printf("max_eps: %lf\n", max_eps);
	//printf("speed_eps: %lf\n", speed_eps);
	//printf("p: %lf\n", p);
	
	//printf("namefile_data: %s\n", NAME_DATAFILE);
	//printf("namefile_result: %s\n", NAME_FILERESULT);
	
}

int read_data(double d[], int n)
{		
	
	FILE *f; 
	f=fopen(NAME_DATAFILE,"r");	
    int i;
	for(i=0;i<n;i++)
	{
		fscanf(f,"%e",&d[i]);
	}	
	
	//printf("Test %i d: %e\n", N-2, d[N-2]);
	//printf("Test %i d: %e\n", N-1, d[N-1]);
	//for(i=0;i<N;i++)
	//{
	//	printf("data: %f\n", data[i]);
	//}	
	//free(data);		
	fclose(f);
	printf("load %d datas from %s\n", N, NAME_DATAFILE);
	
}

int main()
{ 	
	clock_t start = clock();	
	read_file();
	
	data = (double*)malloc(N * sizeof(double));	
	
	read_data(data, N);	
	
	printf("\\---------Estimates---------\\\n");
	
	//printf("Test %i data: %e\n", N-1, data[N-1]);
	
	avg2(min_m, max_m, speed_m, N, min_eps, max_eps, speed_eps, p, data, NAME_FILERESULT);	
	
	
	free(data);
	clock_t stop = clock();	
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;	
    printf("Time elapsed all in ms: %f \n", elapsed);	
		
	return 0;
}