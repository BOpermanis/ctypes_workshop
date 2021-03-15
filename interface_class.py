"""foo.py - a simple demo of importing a calss from C++"""
from ctypes import *

lib = cdll.LoadLibrary('./libinterface_class.so')


class Interface:
    """The Foo class supports two methods, bar, and foobar..."""
    def __init__(self, name):
        lib.Interface_new.argtypes = [c_char_p]
        lib.Interface_new.restype = c_void_p

        lib.Interface_simple_arguments.argtypes = [c_void_p, c_int, c_float]
        lib.Interface_simple_arguments.restype = c_int

        lib.Interface_returning_string_as_pointer.argtypes = [c_void_p, c_char_p]
        lib.Interface_returning_string_as_pointer.restype = c_char_p

        lib.Interface_simple_arrays.argtypes = [c_void_p, c_int * 10]
        lib.Interface_simple_arrays.restype = c_int * 3

        name = c_char_p(name.encode('utf-8'))
        self.obj = lib.Interface_new(name)

    def simple_arguments(self, i, f):
        """bar returns a string continaing the value"""
        return lib.Interface_simple_arguments(self.obj, int(i), float(f))

    def simple_arrays(self, l):
        """bar returns a string continaing the value"""
        assert len(l) == 10
        ten_integer_array = c_int * 10
        return tuple(lib.Interface_simple_arrays(self.obj, ten_integer_array(*l)))

    def returning_string_as_pointer(self, s):
        """foobar takes an integer, and adds it to the value in the Foo class
        - returning the result"""
        s = c_char_p(s.encode('utf-8'))
        return (lib.Interface_returning_string_as_pointer(self.obj, s)).decode()
        
    def __del__(self):
        """destruct unmanaged object"""
        return lib.Interface_delete(self.obj)


if __name__ == "__main__":
    cl = Interface('Frodo')
    print(cl.simple_arguments(2, 5.1))

    a = cl.returning_string_as_pointer("xyz")
    print(a)
    print(len(a))

    print(cl.simple_arrays(list(range(10))))

