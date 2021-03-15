"""foo.py - a simple demo of importing a calss from C++"""
import ctypes

lib = ctypes.cdll.LoadLibrary('./libinterface_class.so')


class Interface:
    """The Foo class supports two methods, bar, and foobar..."""
    def __init__(self):
        # lib.Interface_new.argtypes = [ctypes.c_void_p]
        # lib.Interface_new.restype = ctypes.c_void_p

        lib.Interface_simple_arguments.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_float]
        lib.Interface_simple_arguments.restype = ctypes.c_int

        lib.Interface_returning_string_as_pointer.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        lib.Interface_returning_string_as_pointer.restype = ctypes.c_char_p

        self.obj = lib.Interface_new()

    def simple_arguments(self, i, f):
        """bar returns a string continaing the value"""
        return lib.Interface_simple_arguments(self.obj, int(i), float(f))

    def returning_string_as_pointer(self, s):
        """foobar takes an integer, and adds it to the value in the Foo class
        - returning the result"""
        s = ctypes.c_char_p(s.encode('utf-8'))
        return (lib.Interface_returning_string_as_pointer(self.obj, s)).decode()
        
    def __del__(self):
        """destruct unmanaged object"""
        return lib.Interface_delete(self.obj)


if __name__ == "__main__":
    cl = Interface()
    print(cl.simple_arguments(2, 5.1))

    a = cl.returning_string_as_pointer("xyz")
    print(a)
    print(len(a))
    # x.func.argtypes = [c_char_p, c_int, c_char_p]
    # >> > s = create_string_buffer(10)
    # >> > x.func(s, len(s), 'abcd')