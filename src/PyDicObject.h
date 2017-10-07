#ifndef DIC_OBJECT_H
#define DIC_OBJECT_H

#include<map>
#include"Object.h"

using namespace std;

typedef struct tagPyDictObject
{
    PyObject_HEAD;
    map<long, PyObject*> dict;
}PyDictObject;

PyObject* PyDict_Create();
PyObject* PyDict_GetItem(PyObject* target, PyObject* key);
int PyDict_SetItem(PyObject* target, PyObject* key, PyObject* value);
static void dict_print(PyObject* object);

extern PyTypeObject PyDict_Type;

#endif
