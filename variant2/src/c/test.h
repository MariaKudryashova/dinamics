#ifndef _TEST_H_
#define	_TEST_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include <Python.h>
    
#include <stdio.h>
#include <string.h>

typedef struct test_st_s test_st_t;

extern int a;
extern double b;
extern double min_m;
extern double max_m;
extern double max_eps;
extern double p;
extern char c;

static PyObject *func_hello(PyObject *self, PyObject *args);
static PyObject *func_ret_int(PyObject *self, PyObject *args);
static PyObject *func_ret_double(PyObject *self, PyObject *args);
static PyObject *func_ret_str(PyObject *self, PyObject *args);
static PyObject *func_many_args(PyObject *self, PyObject *args);
static PyObject *func_ret_struct(PyObject *self, PyObject *args);
static PyObject *func_estimates(PyObject *self, PyObject *args);//объявление моей функции
static PyObject *func_theta(PyObject *self, PyObject *args);//функция Хевисайда
static PyObject *func_avg(PyObject *self, PyObject *args);//функция avg работы с массивами

struct test_st_s {
    PyObject_HEAD // Макрос объявления нового типа, объекта фиксированного размера
    int val1;
    double val2;
    char val3;
};

#ifdef	__cplusplus
}
#endif

#endif	/* _TEST_H_ */
