#include <stdlib.h>
#include <stdio.h>
//#include < string.h >
#include <math.h>
#include <time.h>

double get_func_theta(double x)
{
	double res = 1;
	if (x < 0){
		res = 0;
	}
	return res;
}

void get_vector(double *a, int n, int num_vi, int m, int p, double **arr, size_t *arr_len)
{
	double *result = malloc(m);
	int t;
	int stop = n - 1 - num_vi - m*p;
	if (stop > 0){	
		if (result)
		{
			//элементы одного вектора
			for (int mi = 0; mi < m; mi++)
			{
				t = n - 1 - num_vi - mi*p;
				result[mi] = a[t];
				//printf("%d=%.3f ", t,result[mi]);	
			}
		}
	}
    *arr = result;
    *arr_len = m;
}



double avg2(int min_m, int max_m, int speed_m, int N, double min_eps, double max_eps, double speed_eps, double p, double * a, char namefileres[])
{
	printf("N: %d\n", N);
	printf("min_m: %i\n", min_m);
    printf("max_m: %i\n", max_m);
	printf("speed_m: %i\n", speed_m);
	printf("min_eps: %lf\n", min_eps);
	printf("max_eps: %lf\n", max_eps);
	printf("speed_eps: %lf\n", speed_eps);
	printf("p: %lf\n", p);
	
	printf("Test %i data: %lf\n", N-1, a[N-1]);
	
	//расчет количества значений эпсилон
	int num = ceil(log(max_eps/min_eps)/log(speed_eps));
	printf("Number epsilon: %i\n", num);	
	double eps[num];	
	int i;
	double j = min_eps;		
	for (i = 0; i < num; i++)
	{
		j = j*speed_eps;		
		eps[i] = j;		
		if (j > max_eps){			
			break;
		}
		//printf("eps: %f\n", eps[i]);	
	}
	
	int num_m = ceil((max_m - min_m)/speed_m);
	printf("Number m: %i\n", num_m);	
	i = 0;
	int ms[num_m];	
	for (i = 0; i <= num_m; i++)
	{
		ms[i] = min_m + i * speed_m;				
		//printf("ms: %f\n", ms[i]);	
	}	
	double ep;	
	int num_all = (num_m+1)*num;
	//printf("Number lines: %i\n", num_all);
	
	int res_m[num_all];
	double res_ep[num_all];
	double res_C[num_all];
		
	int msgi = 0;//количество строк для файла 
	int res_count = 0;//суммарное число строк в итоге, для проверки	
	
	//int n = N; //позже убрать тавтологию
	//int count_eps = num;
		
	for (int mi = 0; mi <= num_m; mi++)
	{
		int m = ms[mi];
		double M = N + 1 - m*p;//количество векторов заданной размерности
		//printf("Count of vectors fixed dimension m = %d: M = %lf\n", m, M);
		if (M > 2)
		{		
			
			for (int epi = 0; epi < num; epi++)
			{
				
				ep = eps[epi];
				
				int k = 0;//перебор двух векторов
				int h = 0;	
				
				double summ = 0;
				double C = 0;	
				for (k = 0; k < M; k++)
				{
					for (h = 0; h < M; h++)
					{
						//printf("k =%i \t h = %i\n", k, h);
						if (k != h)
						{
							//считаем дистанцию между векторами
							double dist = 0;
												
							int t1,t2;
							double v1, v2;
							int stop1 = N + 1 - h - m*p;
							int stop2 = N + 1 - k - m*p;
							//printf("stop1 =%i \t stop2 = %i\n", stop1, stop2);
							//тут проверка на вылет индекса в отрицательную область
							if ((stop1 > 0)&(stop2 > 0))
							{	
										
								//элементы вектора
								for (int w = 0; w < m; w++)
								{									
									//printf("w\n");
									
									
									t1 = N - 1 - k - w*p;
									//printf("t1=%i\n",t1);
									
									t2 = N - 1 - h - w*p;
									//printf("t2=%i\n",t2);
									
									v1 = a[t1];																	
									v2 = a[t2];	

									//printf("t1 = %i, t2 = %i \n", t1, t2);	
									dist += (v1 - v2)*(v1 - v2);
								}
							}							
							
							//printf("k=%d, h=%d : %.3f   %.3f\n", k, h, dist, sqrt(dist));	
							double s = ep - sqrt(dist);
							double t = get_func_theta(s);
							
							summ += t;
							
							break;
						}
					}
				}
				double mpow = M*(M-1);
				C = summ/mpow;				
				
				//printf("summ = %lf, M = %lf, mpow = %lf, C = %e\n", summ, M, mpow, C);
				//printf("%d, ep = %.3f,  C = %.3f\n", m, ep, C);
				//сохраняем данные в массивы
				res_m[msgi] = m;
				res_ep[msgi] = ep;
				res_C[msgi] = C;
				
				printf("!!! m = %i, ep = %f,  C = %0.30lf\n", res_m[msgi], res_ep[msgi], res_C[msgi]);

				msgi += 1;
				res_count += 1;	
			}	
		}		
	}
								
	FILE* fout;	
	fout  = fopen(namefileres, "w");
	printf("Save to file %s\n", namefileres);	
    if (fout == 0)
    {
        fprintf(stderr, "Error open file\n");
        return 1;
    }
	
	fseek(fout,0,SEEK_END);	
	msgi = 0;
	//fprintf(fout, "m;ep;C\n");
	for (msgi = 0; msgi < res_count; msgi++)
	{		
		fprintf(fout, "%i;%f;%0.30lf\n", res_m[msgi], res_ep[msgi], res_C[msgi]);
	}
   	
    fclose(fout);
	printf("Done\n");	
	
}
