#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <time.h>
#include <complex.h>
#include <math.h>


//для Кантора
int N = 500000;
int Exclude = 8;
double data[500000];

int probability()
{
	int i = rand()%100;
	
	int j = 0;
	if (i < 50)
	{
		j = 0;
	}
	else if (i < 100)
	{
		j = 1;				
	}
	
	return j;
	
}

double f_kantor(double x0, int j)
{
	double res = 0;
	if (j == 0)
	{
		res = x0/3.;
	}
	if (j == 1)
	{
		res = x0/3. + 2./3.;
	}
	return res;
}

double est_kantor(double x0)
{	
	int i;
	double xi;
	
	for(i = 1; i < N+2; i++)
	{
		int j = probability();
		xi = f_kantor(x0, j);
		
		if (i > Exclude)
		{
			//data[i] = xi;			
			break;
		}
		x0 = xi;
	}	
	return xi;
}

int gen_kantor()
{
	double step = 1./N;
	double xi = 0;
	
	for (int i = 0; i < N+2; i++)
	{
		xi = xi + step;		
		data[i] = est_kantor(xi);	
		//printf("i = %i \t x_in = %f\t x_out = %0.30lf\n", i, xi, data[i]);
	}
}
int save_kantor()
{
	FILE* fout;	
	fout  = fopen("set_kantor500_probabl.txt", "w");
	printf("Saving to file\n");	
    if (fout == 0)
    {
        fprintf(stderr, "Error open file\n");
        return 1;
    }
	int i;
	for (i = 1; i < N+2; i++)
	{		
		fprintf(fout, "%e\n", data[i]);
	}
    fclose(fout);
	printf("Done\n");	
}
int main()
{ 	
	clock_t start = clock();	
		
	gen_kantor();
	save_kantor();
	
	clock_t stop = clock();	
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;	
    printf("Time elapsed all in ms: %f \n", elapsed);	
		
	return 0;
}