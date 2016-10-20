#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <exception>
#include <string>
using namespace std;

class MyFontException:public std::exception
{
    public:
        MyFontException();
        virtual ~MyFontException();
        virtual const char* what(int help,string message) throw ();
    protected:
    private:
};

#endif // MYEXCEPTION_H
