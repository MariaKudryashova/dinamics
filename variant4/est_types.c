#define __USE_MINGW_ANSI_STDIO 1

#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <time.h>

int rows = 5;
int columns = 3;
double ** data;
const char name_file[] = "set.txt";
	
	
int init_array()
{
    data = (double**) malloc(sizeof(double *) * rows);
    
	//создаем массив указателей на строки двумерного массива
    if (data == NULL) { 
        fprintf(stderr, "Error allocate memory.\n");    
        return 2;       
    } 
	
	//создаем одномерный массив для хранения данных
    data[0] = (double *) malloc(sizeof(double) * rows*columns);
    if (data[0] == NULL) {
        fprintf(stderr, "Error allocate memory.\n");
        free(data);      
        return 2;
    }
	
    //"пришиваем" соответствующие строки к указателям
    for (size_t i = 1; i < rows; i++)
        data[i] = data[i-1] + columns;
	
	/* заполняем массив случайными: 
    int i, k;
    for (i = 0; i < rows; i++)
        for (k = 0; k < columns; k++)
            data[i][k] = 1.1234567891234;
 */
	
	return 1;
}


	

int read_data()
{			
	
    FILE *input = NULL;
    char c;
	char str[1000];
	char * end;
	
	int i = 0;
	int k = 0;
	
	double d;
 
    input = fopen(name_file, "rt");
    if (input == NULL) {
        printf("Error opening file");
        _getch();
        exit(0);
    }
	
    while (!feof(input)) {
        c = fgetc(input);
		str[i] = c;
		
		if (c == ';')
		{
			d = strtod(str, &end);
			i = 0;
			printf("d = %f\n", d);
		}	
		
		
		i += 1;
    }
	
 
    fclose(input);
	
	
	
    //_getch();
   
   /*
	for(i=0;i<rows;i++){
		for(k=0;k<columns;k++){
			fscanf(f,"%0.15Lf", &data[i][k]);
			printf("data[%d,%d] = %0.15Lf\t",i,k,data[i][k]);
		}	
		printf("\n");
	}
	*/
	
}


int show_data()
{
	int i, k;
	// выводим элементы массива на экран 
    for (i = 0; i < rows; i++) {
        for (k = 0; k < columns; k++)
            printf("%0.15Lf \t", data[i][k]);
        puts("");
    }
}


int save_data()
{
	FILE* fout;	
	
	fout  = fopen(name_file, "w");
	printf("Save to file %s\n", name_file);	
    if (fout == 0)
    {
        fprintf(stderr, "Error open file\n");
        return 1;
    }
	
	int i,k;
	for(i=0 ;i<rows; i++)
	{
		for(k=0; k<columns; k++)
		{
			fprintf(fout, "%0.15Lf;", data[i][k]);
			
		}
		fprintf(fout,"\n");
	}	
}

/*
int test()
{
	float a = 32000.0;
    double b = 2.14e9;
    long double c = 5.32e-05;
 
    printf("%f - %e\n", a, a);
    printf("%f - %e\n", b, b);
    printf("%Lf - %Le\n", c, c);
 
 	getchar();
  
    return 0;
}
*/

int main()
{ 	
	clock_t start = clock();	
	
    init_array();
	read_data();
    //show_data();
	//save_data();
 
    /* освобождаем память и выходим */
    free(data[0]);
    free(data);
    	
	clock_t stop = clock();	
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;	
    printf("Time elapsed all in ms: %f \n", elapsed);	
		
	return 0;
}