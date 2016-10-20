#include "MyException.h"
#include <string>
#include <iostream>

using namespace std;

MyFontException::MyFontException()
{
    //ctor
}

MyFontException::~MyFontException()
{
    //dtor
}

const char* MyFontException::what(int help,string filename) throw() {
    if(help==1){
        cout << ("Could not load font " + filename).c_str() <<endl;
    }
    else{
        cout << ("Could not load picture " + filename).c_str() << endl;
    }
}
