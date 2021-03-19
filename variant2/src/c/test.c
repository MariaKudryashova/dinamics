/*
 * gcc -fPIC -shared -o libtest.so test.c
 */

#include <Python.h>
#include <stdio.h>
#include "test.h"
#include "struct.h"
#include < string.h >
#include <math.h>
#include <time.h>

// Список функций модуля
static PyMethodDef methods[] = {
    {"func_hello", func_hello, METH_NOARGS, "func_hello"}, // Функция без аргументов
    {"func_ret_int", func_ret_int, METH_VARARGS, "func_ret_int"}, // Функция с аргументами
    {"func_ret_double", func_ret_double, METH_VARARGS, "func_ret_double"},
    {"func_ret_str", func_ret_str, METH_VARARGS, "func_ret_str"},
    {"func_many_args", func_many_args, METH_VARARGS, "func_many_args"},
    {"func_ret_struct", func_ret_struct, METH_VARARGS, "func_ret_struct"},
	{"func_estimates", func_estimates, METH_VARARGS, "func_estimates"},//моя функция
	{"func_theta", func_theta, METH_VARARGS, "func_theta"}, // моя функция - функция Хевисайда,
    {"func_avg", func_avg, METH_VARARGS, "func_avg"}, // работа с массивом avg
	{NULL, NULL, 0, NULL}
};

// Описание модуля
static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT, "_test", "Test module", -1, methods
};

// Инициализация модуля
PyMODINIT_FUNC 
PyInit__test(void) {
    PyObject *mod = PyModule_Create(&module);

    // Добавляем глобальные переменные
    PyModule_AddObject(mod, "a", PyLong_FromLong(a)); // int
    PyModule_AddObject(mod, "b", PyFloat_FromDouble(b)); // double
    PyModule_AddObject(mod, "min_m", PyFloat_FromDouble(min_m)); // double
    PyModule_AddObject(mod, "max_m", PyFloat_FromDouble(max_m)); // double
    PyModule_AddObject(mod, "max_eps", PyFloat_FromDouble(max_eps)); // double
	PyModule_AddObject(mod, "p", PyFloat_FromDouble(p)); // double
    
	PyModule_AddObject(mod, "c", Py_BuildValue("b", c)); // char

    // Добавляем структуру
    
    // Завершение инициализации структуры
    if (PyType_Ready(&test_st_t_Type) < 0)
        return NULL;
    
    Py_INCREF(&test_st_t_Type);
    PyModule_AddObject(mod, "test_st_t", (PyObject *) &test_st_t_Type);
    
    return mod;
}

/**
 * Тестовые функции, тестовые переменные.
 */

int a = 5;
double b = 5.12345;
double min_m = 3;
double max_m = 8;
double max_eps = 30;
double p = 2;
char c = 'X'; // 88

static PyObject *
func_hello(PyObject *self, PyObject *args) { // Можно без args, но будет warning при компиляции.
    puts("Hello!");
    Py_RETURN_NONE;
}

/**
 * Получение значения переменной содержащей значение типа int и возврат его.
 */
static PyObject *
func_ret_int(PyObject *self, PyObject *args) {
    int val;

    // Проверка кол-ва аргументов
    if (PyTuple_Size(args) != 1) {
        PyErr_SetString(self, "func_ret_int args error");
    }

    PyArg_ParseTuple(args, "i", &val);
    /* 
     * Альтернативный вариант.
     * 
    // Получаем аргумент
    PyObject *obj = PyTuple_GetItem(args, 0);
    // Проверяем его на тип int/long
    if (PyLong_Check(obj)) {
        PyErr_Print();
    }
    // Приводим (PyObject *) к int
    val = _PyLong_AsInt(obj);
     */
    printf("C get func_ret_int: %d\n", val);
    return Py_BuildValue("i", val);
}

/**
 * Получение значения переменной содержащей значение типа double и возврат его.
 */
static PyObject *
func_ret_double(PyObject *self, PyObject *args) {
    double val;

    if (PyTuple_Size(args) != 1) {
        PyErr_SetString(self, "func_ret_double args error");
    }

    PyArg_ParseTuple(args, "d", &val);

    printf("C get func_ret_double: %f\n", val);
    return Py_BuildValue("f", val);
}

/**
 * Получение string и возврат его.
 */
static PyObject *
func_ret_str(PyObject *self, PyObject *args) {
    char *val;

    if (PyTuple_Size(args) != 1) {
        PyErr_SetString(self, "func_ret_str args error");
    }

    PyArg_ParseTuple(args, "s", &val);
    /* 
     * Альтернативный вариант.
     * 
    PyObject *obj = PyTuple_GetItem(args, 0);
    
    PyObject* pResultRepr = PyObject_Repr(obj);
    val = PyBytes_AS_STRING(PyUnicode_AsEncodedString(pResultRepr, "utf-8", "ERROR"));
     */
    printf("C get func_ret_str: %s\n", val);
    return Py_BuildValue("s", val);
}

/**
 * Получение значения переменных содержащих значения типа int, double, char *.
 */
static PyObject *
func_many_args(PyObject *self, PyObject *args) {
    int val1;
    double val2;
    char *val3;

    if (PyTuple_Size(args) != 3) {
        PyErr_SetString(self, "func_ret_str args error");
    }

    PyArg_ParseTuple(args, "ids", &val1, &val2, &val3);

    printf("C get func_many_args: int - %d, double - %f, string - %s\n", val1, val2, val3);
    return Py_BuildValue("ifs", val1, val2, val3);
}


static PyObject *
func_ret_struct(PyObject *self, PyObject *args) {
    
    test_st_t *st;
    
    // Получаем структуру из Python
    if (!PyArg_ParseTuple(args, "O", &st)) // O - объект данных
        Py_RETURN_NONE;
    
    printf("C get test_st: val1 - %d, val2 - %f, val3 - %d\n", st->val1++, st->val2++, st->val3++);

    return Py_BuildValue("O", st);
}

/**
 * Моя функция: Получение значения переменной содержащей значение типа double и возврат его.
 */
static PyObject *
func_estimates(PyObject *self, PyObject *args) {
    double val;

    if (PyTuple_Size(args) != 1) {
        PyErr_SetString(self, "func_estimates args error");
    }

    PyArg_ParseTuple(args, "d", &val);

    printf("C get func_estimates: %f\n", val);
    return Py_BuildValue("f", val);
}

/**
 * Моя реализация - функция Хевисайда
 */
static PyObject *
func_theta(PyObject *self, PyObject *args) {
    int val;
	int res;
	res = 1;

    // Проверка кол-ва аргументов
    if (PyTuple_Size(args) != 1) {
        PyErr_SetString(self, "func_theta args error");
    }

    PyArg_ParseTuple(args, "i", &val);
   
    printf("C get func_theta: %d\n", val);
	printf("Hi from DLL\n");
	if (val < 0){
		res = 0;
	}
	
    return Py_BuildValue("i", res);
}

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
	//один вектор - проверка на существование вектора
	//с номером num_vi
	int t;

	int stop = n - 1 - num_vi - m*p;
	if (stop > 0){			
			
	
	if (result){
	//элементы одного вектора
	for (int mi = 0; mi < m; mi++){
		t = n - 1 - num_vi - mi*p;
		result[mi] = a[t];
		//printf("%d=%.3f ", t,result[mi]);	
	}
	}
	}
	/* Set output parameters */
    *arr = result;
    *arr_len = m;

}

double avg(double *a, int n) 
{
	clock_t start = clock();
	
	//n - количество точек временного ряда
	int NN = 1170; //всего строк, произведение количества ms*eps
	int count_eps = 172;
	
	int res_m[1170];
	double res_ep[1170];
	double res_C[1170];
	
	int msgi = 0;//количество строк для файла 
	int res_count = 0;//суммарное число строк в итоге, для проверки
	
	printf("Count point of time series = %d\n", n);
	//инициализировали ms, eps
	int num_m = 6; //количество размерностей
	int ms[6] = {3, 4, 5, 6, 7, 8};//задаем размерности
	int p = 2;//параметр р в расчетах фиксированный
	
	//расчитаем значения эпсилона
	double eps[172];
	int i;
	double j = 15; //стартовое значение эпсилона
	int num = 500; //общее количество в эпсилон-массиве не должно превысить эту цифру
	int max_eps = 70;//конечное значение эпсилона
	double multi = 1.02;//множитель для увеличения эпсилона
	for (i = 0; i < num; i++)
	{
		j = j*multi;
		//printf("i = %d j = %.3f multi = %.3f \n", i, j, multi);
		eps[i] = j;		
		if (j > max_eps){			
			break;
		}
	}

	//считаем корр интеграл для фиксир ep
	double ep = 1.01;
	int epi = 0; //индекс для эпсилон-массива
	int mi = 0; //индекс для массива размерностей
	
	for (mi = 0; mi < num_m; mi++)
	{
		int m = ms[mi];
		int M = n + 1 - m*p;//количество векторов заданной размерности
		printf("Count of vectors fixed dimension m = %d: M = %d\n", m, M);
		if (M > 2)
		{		
			for (epi = 0; epi < count_eps; epi++)
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
						if (k != h)
						{
							//считаем дистанцию между векторами
							double dist = 0;
												
							int t1,t2;
							double v1, v2;
							int stop1 = n + 1 - h - m*p;
							int stop2 = n + 1 - k - m*p;
							//тут проверка на вылет индекса в отрицательную область
							if ((stop1 > 0)&(stop2 > 0))
							{		
								//элементы вектора
								for (int w = 0; w < m; w++)
								{
									t1 = n - 1 - k - w*p;
									t2 = n - 1 - h - w*p;
									v1 = a[t1];
									v2 = a[t2];

									//printf("t1 = %.3f, t2 = %.3f \n", t1, t2);	
									dist += (v1 - v2)*(v1 - v2);
								}
							}							
							
							//printf("k=%d, h=%d : %.3f   %.3f\n", k, h, dist, sqrt(dist));	
							double s = ep - sqrt(dist);
							double t = get_func_theta(s);
							
							summ += t;
						}
					}
				}
				C = summ/(M*(M-1));
				
				
				//printf("%d, ep = %.3f,  C = %.3f\n", m, ep, C);
				//сохраняем данные в массивы
				res_m[msgi] = m;
				res_ep[msgi] = ep;
				res_C[msgi] = C;
				//printf("!!! m = %d, ep = %.3f,  C = %.3f\n", res_m[msgi], res_ep[msgi], res_C[msgi]);

				msgi += 1;
				res_count += 1;

			}	
		}
	}
	
	clock_t stop_est = clock();
	
	//печатаем в файл итоги	
	printf("Print to files \n");
	FILE * fp;
	fp = fopen("data_p.txt","w");
	fprintf(fp, "m;ep;C \n");
	for (msgi = 0; msgi < NN; msgi++)
	{
		if (msgi >= res_count)
		{
			break;
		}
		fprintf(fp,"%d;%.3f;%.10f\n", res_m[msgi], res_ep[msgi], res_C[msgi]);
		//printf("!!! m = %d, ep = %.3f,  C = %.3f\n", res_m[msgi], res_ep[msgi], res_C[msgi]);
	}		
	fclose(fp);
	fp = fopen("data_log_p.txt","w");
	
	fprintf(fp, "m;ep;log_ep,log_C \n");
	for (msgi = 0; msgi < NN; msgi++)
	{
		if (msgi >= res_count)
		{
			break;
		}
		fprintf(fp,"%d;%.3f;%.10f;%.10f\n", res_m[msgi], res_ep[msgi], log(res_ep[msgi]), log(res_C[msgi]));
		//printf("!!! m = %d, ep = %.3f,  C = %.3f\n", res_m[msgi], res_ep[msgi], res_C[msgi]);
	}		
	fclose(fp);
	//char * message = "Hello \n world!\n An apple a day keeps the doctor away";
    //char * filename = "data.txt";
    //char cc[256];
    //FILE *fp;
     
    // запись в файл
    //if((fp= fopen(filename, "w"))==NULL)
    //{
    //    perror("Error occured while opening file");
    //    return 1;
    //}
    // записываем строку
    //fputs(message, fp);
 
    //fclose(fp);
	
	clock_t stop_all = clock();
	
	double elapsed_est = (double)(stop_est - start) * 1000.0 / CLOCKS_PER_SEC;
	double elapsed_all = (double)(stop_all - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time elapsed estimates in ms: %f \n", elapsed_est);
	printf("Time elapsed all in ms: %f \n", elapsed_all);	
	return 0;        
}

	



/**
 * Расширение для работы с массивами
 вызов функции double avg(double *, int)
 */
static PyObject *
func_avg(PyObject *self, PyObject *args) {
	PyObject *bufobj;
	Py_buffer view;
	double result;
	if (!PyArg_ParseTuple(args, "O", &bufobj)){
		return NULL;
	}
	if (PyObject_GetBuffer(bufobj, &view, PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT) == -1){
		return NULL;
	}
	if (view.ndim != 1){
		PyErr_SetString(PyExc_TypeError, "Expected a 1-dimensional array");
		PyBuffer_Release(&view);
		return NULL;
	}
	if (strcmp(view.format, "d") != 0) {
		PyErr_SetString(PyExc_TypeError, "Expected an array of doubles");
		PyBuffer_Release(&view);
		return NULL;
	}		
	
result = avg(view.buf, view.shape[0]);


PyBuffer_Release(&view);

return Py_BuildValue("d", result);

}


