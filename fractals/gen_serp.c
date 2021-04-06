#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <time.h>
#include <complex.h>
#include <math.h>



//для Серпинского
int N = 500000;
int Exclude = 52;
double complex data[500000]; 


double complex f_serpinskii(double complex z, int j)
{
	double complex res = 0;
	if (j == 0)
	{
		res = 0.5 * z;
	}
	if (j == 1)
	{
		res = 0.5 * z + 0.5;
	}
	if (j == 2)
	{ 
		res = 0.5 * z + 0.25 + (sqrt(3)/4) * I;
	}
		
	return res;
}

int probability()
{
	int i = rand()%100;
	
	int j = 0;
	if (i < 90)
	{
		j = 0;
	}
	else if (i < 95)
	{
		j = 1;				
	}
	else if (i < 100)
	{
		j = 2;
	}
	j = rand()%3;
	//printf("i=%i\t j=%i\n", i,j);
	return j;
	
}

int gen_serpinskii()
{
	double complex z0 = 1.0 + 1.0 * I;
	printf("Z0 = %f + %fi\n", creal(z0), cimag(z0));
	
	int i, j;
	double complex zi;
	data[0] = z0;
	
	for(i = 1; i <= (N + Exclude + 1); i++)
	{
		j = probability();

		
		zi = f_serpinskii(z0, j);
		if (i > Exclude)
		{		
			data[i-Exclude] = zi;
			//printf("Z%i = f%i(Z%i)= %f + %fi\n", i, j, i-1, creal(data[i-Exclude]), cimag(data[i-Exclude]));
		}
		z0 = zi;
	}	
}
int save_serpinskii()
{
	FILE* fout;	
	fout  = fopen("set_serpinskii.txt", "w");
	printf("Saving to file\n");	
    if (fout == 0)
    {
        fprintf(stderr, "Error open file\n");
        return 1;
    }
	int i;
	for (i = 1; i < N; i++)
	{		
		fprintf(fout, "%f;%f\n", creal(data[i]), cimag(data[i]));
	}
    fclose(fout);
	printf("Done\n");	
}


int main()
{ 	
	clock_t start = clock();	
	
	gen_serpinskii();	
	save_serpinskii();
		
	clock_t stop = clock();	
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;	
    printf("Time elapsed all in ms: %f \n", elapsed);	
		
	return 0;
}