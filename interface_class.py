"""foo.py - a simple demo of importing a calss from C++"""
import ctypes

lib = ctypes.cdll.LoadLibrary('./libinterface_class.so')


class Interface:
    """The Foo class supports two methods, bar, and foobar..."""
    def __init__(self, val):
        lib.Interface_new.argtypes = [ctypes.c_int]
        lib.Interface_new.restype = ctypes.c_void_p

        lib.Interface_bar.argtypes = [ctypes.c_void_p]
        lib.Interface_bar.restype = ctypes.c_char_p

        lib.Interface_foobar.argtypes = [ctypes.c_void_p, ctypes.c_int]
        lib.Interface_foobar.restype = ctypes.c_int
        
        lib.Interface_delete.argtypes = [ctypes.c_void_p]

        self.obj = lib.Interface_new(val)


    def bar(self):
        """bar returns a string continaing the value"""
        return (lib.Interface_bar(self.obj)).decode()


    def foobar(self, val):
        """foobar takes an integer, and adds it to the value in the Foo class
        - returning the result"""
        return lib.Interface_foobar(self.obj, val)
        
    def __del__(self):
        """destruct unmanaged object"""
        return lib.Interface_delete(self.obj)
