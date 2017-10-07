#include <iostream>
#include <string.h>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <map>
#include <ctype.h>

#include"PyDicObject.h"
#include"PyIntObject.h"
#include"PyStrObject.h"

using namespace std;

void ExcutePrint(string symbol);
void ExcuteCommand(string& command);
PyObject* GetObjectBySymbol(string& symbol);
 void ExcuteAdd(string& target, string& source);
 bool IsSourceAllDigit(string source);
void Excute();

PyDictObject *m_LocalEnvironment = new PyDictObject;

void ExcuteCommand(string& command)
 {
     string::size_type pos = 0;
     if((pos = command.find("print ")) != string::npos)
     {
     ExcutePrint(command.substr(6));
     }
     else if((pos = command.find(" = ")) != string::npos)
     {
     string target = command.substr(0, pos);
     string source = command.substr(pos+3);
     ExcuteAdd(target, source);
     }
 }

void ExcuteAdd(string &target, string &source){
    string::size_type pos;
    PyObject *strValue = NULL;
    PyObject *resultValue = NULL;

    if(IsSourceAllDigit(source)){
        PyObject *intValue = PyInt_Create(atoi(source.c_str()));
        PyObject *key = PyStr_Create(target.c_str());
        PyDict_SetItem((PyObject *)m_LocalEnvironment, key, intValue);
    } else if(source.find("\"") != string::npos){
        strValue = PyStr_Create(source.substr(1, source.size()-2).c_str());
        PyObject *key = PyStr_Create(target.c_str());
        PyDict_SetItem((PyObject *)m_LocalEnvironment, key, strValue);
    } else if((pos = source.find("+")) != string::npos){
        string left = source.substr(0, pos);
        if(left[left.size()-1] == ' ')
            left = left.substr(0, left.size()-1);
        string right = source.substr(pos+1);
        if(right[0] == ' ')
            right = right.substr(1, right.size());
        PyObject *leftObject = GetObjectBySymbol(left);
        PyObject *rightObject = GetObjectBySymbol(right);
        if(leftObject != NULL && rightObject != NULL && leftObject->type == rightObject->type){
            resultValue = (leftObject->type)->add(leftObject, rightObject);
            PyObject *key = PyStr_Create(target.c_str());
            PyDict_SetItem((PyObject *)m_LocalEnvironment, key, resultValue);
        }
    }
}


 void ExcuteAdd2(string& target, string& source)
 {
     string::size_type pos;
     if(IsSourceAllDigit(source))
     {
         PyObject* intValue = PyInt_Create(atoi(source.c_str()));
         PyObject* key = PyStr_Create(target.c_str());
        PyDict_SetItem((PyObject *)m_LocalEnvironment, key, intValue);
     }
     else if(source.find("\"") != string::npos)
     {
         PyObject* strValue = PyStr_Create(source.substr(1,
        source.size()-2).c_str());
         PyObject* key = PyStr_Create(target.c_str());
         PyDict_SetItem((PyObject *)m_LocalEnvironment, key, strValue);
     }
     else if((pos = source.find("+")) != string::npos)
     {
        string left1 = source.substr(0, pos);
         PyObject* leftObject = GetObjectBySymbol(left1);
        string right2 = source.substr(pos+1);
         PyObject* rightObject = GetObjectBySymbol(right2);
         if(leftObject != NULL && rightObject != NULL && leftObject->type == rightObject->type)
         {
             PyObject* resultValue =
            (leftObject->type)->add(leftObject, rightObject);
             PyObject* key = PyStr_Create(target.c_str());
             PyDict_SetItem((PyObject *)m_LocalEnvironment, key, resultValue);
          }
         (m_LocalEnvironment->type)->print((PyObject *)m_LocalEnvironment);
     }
 }

PyObject* GetObjectBySymbol(string& symbol)
 {
     PyObject* key = PyStr_Create(symbol.c_str());
     PyObject* value = PyDict_GetItem((PyObject *)m_LocalEnvironment, key);
     if(value == NULL)
     {
        cout << "[Error] : " << symbol << " is not defined!!" << endl;
        return NULL;
     }
     return value;
 }

 void ExcutePrint(string symbol)
 {
     PyObject* object = GetObjectBySymbol(symbol);
     if(object != NULL)
     {
        PyTypeObject* type = object->type;
        type->print(object);
     }
 }

 bool IsSourceAllDigit(string source)
 {
    bool result = true;
    for(int i=0; i!=source.size(); i++){
        result = isdigit(source[i]);
        if(!result)
            break;
    }
    return result;
}

string info = "********** Python Research **********\n";
string prompt = ">>> ";
string m_Command = "";

 void Excute()
 {
     cout << info;
     cout << prompt;
     while(getline(cin, m_Command)){
     if(m_Command.size() == 0){
        cout << prompt;
        continue;
     }
     else if(m_Command == "exit"){
        return;
     }
     else{
        ExcuteCommand(m_Command);
     }
        cout << prompt;
     }
 }

 int main(){

    Excute();
    return 1;
 }
