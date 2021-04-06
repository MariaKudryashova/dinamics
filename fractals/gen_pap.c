#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <time.h>
#include <complex.h>
#include <math.h>



//для Барнсли
int N = 20000;
complex double data[20000];


double complex func(double complex z,double a,double b,double c,double d,double e,double f)
{
	double complex zi;
	
	double z_real = creal(z);
	double z_imag = cimag(z);
	
	double x = a*z_real + b*z_imag + e;
	double y = c*z_real + d*z_imag + f;
	
	zi =  x + y * I;	
	
	//printf("a=%f; b=%f; c=%f; d=%f; e=%f; f=%f\n",a,b,c,d,e,f);
	//printf("Zi = %f + %fi\n", creal(zi), cimag(zi));
	//printf("\n");
	
	return zi;
}

double complex probability(double complex z)
{
	int k = rand()%100;
	double a,b,c,d,e,f,p;
	int j = 0;
	if (k < 1)
	{
		j = 0;
		a = 0;
		b = 0;
		c = 0;
		d = 0.16;
		e = 0;
		f = 0;
	}
	else if (k < 86)
	{
		j = 1;	
		a = 0.85;
		b = 0.04;
		c = -0.04;
		d = 0.85;
		e = 0;
		f = 0.4;		
	}
	else if (k < 93)
	{
		j = 2;
		a = 0.2;
		b = -0.26;
		c = 0.23;
		d = 0.22;
		e = 0;
		f = 0;
	}
	else if (k < 100)
	{
		j = 3;
		a = -0.15;
		b = 0.28;
		c = 0.26;
		d = 0.24;
		e = 0;
		f = 0.16;
	}
	double complex zi;
	zi = func(z,a,b,c,d,e,f);
	return zi;
}

int gen()
{
	double complex z0 = 1.0 + 1.0 * I;
	printf("Z0 = %f + %fi\n", creal(z0), cimag(z0));
	
	int i, j;
	double complex zi;
	
	data[0] = z0;
	
	for(i = 1; i <= N; i++)
	{
		zi = probability(z0);

		z0 = zi;
		data[i] = zi;
		//printf("data: %f;%f\n",data_x[i],data_y[i]);
	}	
}
int save()
{
	FILE* fout;	
	fout  = fopen("set_pap.txt", "w");
	printf("Saving to file\n");	
    if (fout == 0)
    {
        fprintf(stderr, "Error open file\n");
        return 1;
    }
	int i;
	for (i = 1; i < N; i++)
	{		
		fprintf(fout, "%i;%f;%f\n", i, creal(data[i]), cimag(data[i]));
	}
    fclose(fout);
	printf("Done\n");	
}


int main()
{ 	
	clock_t start = clock();	
	
	gen();	
	save();
		
	clock_t stop = clock();	
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;	
    printf("Time elapsed all in ms: %f \n", elapsed);	
		
	return 0;
}