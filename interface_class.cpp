#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <string.h>
#include <cstring>

using namespace std;

struct Box {
    int xmin, ymin, xmax, ymax;
};

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

        int* simple_arrays(int* arr){
            for(int i=0; i < 10; i++)
                cout << "array element " << arr[i] << endl;

            int arr_out[3] = {2, 4, 3};
            return arr_out;
        }

        const char* returning_string_as_pointer(char* sptr, int n){
            static char s[15] = "The input was ";
            strcat(s, sptr);
            return s;
        }

        Box intersect_bboxes(Box b1, Box b2){
            Box intersection;
            intersection.xmin = max(b1.xmin, b2.xmin);
            intersection.ymin = max(b1.ymin, b2.ymin);
            intersection.xmax = min(b1.xmax, b2.xmax);
            intersection.ymax = min(b1.xmax, b2.xmax);
            return intersection;
        }


};
// Define C functions for the C++ class - as ctypes can only talk to C...

extern "C"
{
#ifdef __linux__
    Interface* Interface_new(char* name) {return new Interface(name);}

    int Interface_simple_arguments(Interface* face, int i, float f) {
    return face->simple_arguments(i, f);}

    const char* Interface_returning_string_as_pointer(Interface* face, char* sptr, int n) {
    return face->returning_string_as_pointer(sptr, n);}

    int* Interface_simple_arrays(Interface* face, int* arr) {
    return face->simple_arrays(arr);}

    Box Interface_intersect_bboxes(Interface* face, Box b1, Box b2) {
    return face->intersect_bboxes(b1, b2);}

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