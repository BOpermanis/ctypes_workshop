#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>

// A simple class with a constuctor and some methods...

class Interface
{
    public:
        Interface(int);
        const char* bar();
        int foobar(int);
    private:
        int val;
};

Interface::Interface(int n)
{
    val = n;
}

const char* Interface::bar()
{
    std::string s;
    std::string msg;
    
    s = std::to_string(val);
    msg = "The value is " + s;
    const char* rv = msg.c_str();
    return rv;
}

int Interface::foobar(int n)
{
    return val + n;
}

// Define C functions for the C++ class - as ctypes can only talk to C...

extern "C"
{
#ifdef __linux__
    Interface* Interface_new(int n) {return new Interface(n);}
    const char* Interface_bar(Interface* face) {return face->bar();}
    int Interface_foobar(Interface* face, int n) {return face->foobar(n);}
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