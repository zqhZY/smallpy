#ifndef STR_OBJECT_H
#define STR_OBJECT_H

#include"Object.h"

typedef struct tagPyStrObject
{
     PyObject_HEAD;
     int length;
     long hashValue;
     char value[50];
}PyStringObject;

PyObject* PyStr_Create(const char* value);
static void string_print(PyObject* object);
static long string_hash(PyObject* object);
static PyObject* string_add(PyObject* left, PyObject* right);

extern PyTypeObject PyString_Type;

#endif
