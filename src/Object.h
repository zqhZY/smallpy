#ifndef OBJECT_H
#define OBJECT_H

#define PyObject_HEAD \
 int refCount;\
 struct tagPyTypeObject *type

 #define PyObject_HEAD_INIT(typePtr)\
 0, typePtr

#include<string>

using namespace std;

 typedef struct tagPyObject
{
    PyObject_HEAD;
}PyObject;

//definition of PyTypeObject
typedef void (*PrintFun)(PyObject* object);
typedef PyObject* (*AddFun)(PyObject* left, PyObject* right);
typedef long (*HashFun)(PyObject* object);

typedef struct tagPyTypeObject
{
     PyObject_HEAD;
     string name;
     PrintFun print;
     AddFun add;
     HashFun hash;
}PyTypeObject;

extern PyTypeObject PyType_Type; 
#endif
