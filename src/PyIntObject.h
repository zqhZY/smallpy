#ifndef INT_OBJECT_H
#define INT_OBJECT_H

#include"Object.h"

typedef struct tagPyIntObject
{
    PyObject_HEAD;
    int value;
} PyIntObject;

PyObject* PyInt_Create(int value);
static void int_print(PyObject* object);
static PyObject* int_add(PyObject* left, PyObject* right);
static long int_hash(PyObject* object);

extern PyTypeObject PyInt_Type;

#endif // INT_OBJECT_H
