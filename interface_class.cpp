#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <string.h>
#include <cstring>

// A simple class with a constuctor and some methods...
using namespace std;

class Interface
{
    string myname;
    public:
        Interface(char* name){
            myname = string(name);
            cout << "Hi, my name is " << name << endl;
        };

        int simple_arguments(int i, float f){
            int j = i + (int) f;
            return j;
        }

        const char*  returning_string_as_pointer(char* sptr, int n){
            static char s[15] = "The input was ";
            strcat(s, sptr);
//            string str(s);
            return s;
        }

//        int foobar(int);
//    private:
//        int val;
};

//const char* Interface::bar()
//{
//    std::string s;
//    std::string msg;
//
//    s = std::to_string(val);
//    msg = "The value is " + s;
//    const char* rv = msg.c_str();
//    return rv;
//}
//
//int Interface::foobar(int n)
//{
//    return val + n;
//}

// Define C functions for the C++ class - as ctypes can only talk to C...

extern "C"
{
#ifdef __linux__
    Interface* Interface_new(char* name) {return new Interface(name);}

    int Interface_simple_arguments(Interface* face, int i, float f) {
    return face->simple_arguments(i, f);}

    const char* Interface_returning_string_as_pointer(Interface* face, char* sptr, int n) {
    return face->returning_string_as_pointer(sptr, n);}

//    const char* Interface_bar(Interface* face) {return face->bar();}
//    int Interface_foobar(Interface* face, int n) {return face->foobar(n);}
    void Interface_delete(Interface* face)
    {
        if (face)
        {
            delete face;
            face = nullptr;
        }
    }
#elif _WIN32
    __declspec(dllexport) Foo* Foo_new(int n) {return new Foo(n);}
    __declspec(dllexport) const char* Foo_bar(Foo* foo) {return foo->bar();}
    __declspec(dllexport) int Foo_foobar(Foo* foo, int n) {return foo->foobar(n);}
    __declspec(dllexport) void Foo_delete(Foo* foo)
    {
        if (foo)
        {
            delete foo;
            foo = nullptr;
        }
    }
#else
#endif
}