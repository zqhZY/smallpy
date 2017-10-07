#ifndef TYPE_OBJECT_H
#define TYPE_OBJECT_H

#include"Object.h"

PyTypeObject PyType_Type ={
    PyObject_HEAD_INIT(&PyType_Type),
    "type",
    0,
    0,
    0
};

#endif
