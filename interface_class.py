from ctypes import *
import numpy.ctypeslib as npct
import numpy as np
# lib = cdll.LoadLibrary('./libinterface_class.so')
lib = npct.load_library('libinterface_class', '.')


class Box(Structure):
    _fields_ = [
        ("xmin", c_int),
        ("ymin", c_int),
        ("xmax", c_int),
        ("ymax", c_int)
    ]


class Path(Structure):
    _fields_ = [
        ('length', c_int),
        ('data', POINTER(c_int)),
    ]


class Interface:

    def __init__(self, name):
        lib.Interface_new.argtypes = [c_char_p]
        lib.Interface_new.restype = c_void_p

        lib.Interface_simple_arguments.argtypes = [c_void_p, c_int, c_float]
        lib.Interface_simple_arguments.restype = c_int

        lib.Interface_returning_string_as_pointer.argtypes = [c_void_p, c_char_p]
        lib.Interface_returning_string_as_pointer.restype = c_char_p

        lib.Interface_simple_arrays.argtypes = [c_void_p, c_int * 10]
        lib.Interface_simple_arrays.restype = c_int * 3

        lib.Interface_intersect_bboxes.argtypes = [c_void_p, Box, Box]
        lib.Interface_intersect_bboxes.restype = Box

        lib.Interface_multiply_by_3.argtypes = [c_void_p, POINTER(c_int),
            POINTER(c_int), POINTER(c_int)]
        lib.Interface_multiply_by_3.restype = c_int

        lib.Interface_run_astar.argtypes = [c_void_p, POINTER(c_int),
                                            POINTER(c_int),
                                            POINTER(c_int), POINTER(c_int)]
        lib.Interface_run_astar.restype = Path

        name = c_char_p(name.encode('utf-8'))
        self.obj = lib.Interface_new(name)

    def simple_arguments(self, i, f):
        return lib.Interface_simple_arguments(self.obj, int(i), float(f))

    def simple_arrays(self, l):
        assert len(l) == 10
        ten_integer_array = c_int * 10
        return tuple(lib.Interface_simple_arrays(self.obj, ten_integer_array(*l)))

    def returning_string_as_pointer(self, s):
        s = c_char_p(s.encode('utf-8'))
        return (lib.Interface_returning_string_as_pointer(self.obj, s)).decode()

    def intersect_bboxes(self, bbox1, bbox2):
        return lib.Interface_intersect_bboxes(self.obj, Box(*bbox1), Box(*bbox2))

    def multiply_by_3(self, arr):
        c_intp = POINTER(c_int)  # ctypes integer pointer
        arr_out = np.zeros_like(arr)
        shape = np.array(arr.shape, dtype=np.int32)
        lib.Interface_multiply_by_3(
            self.obj,
            arr.ctypes.data_as(c_intp),  # Cast numpy array to ctypes integer pointer
            arr_out.ctypes.data_as(c_intp),
            shape.ctypes.data_as(c_intp))
        return arr_out

    def run_astar(self, gridmap, start, finish):
        c_intp = POINTER(c_int)  # ctypes integer pointer
        shape = np.array(gridmap.shape, dtype=np.int32)
        start = np.array(start, dtype=np.int32)
        finish = np.array(finish, dtype=np.int32)

        path = lib.Interface_run_astar(
            self.obj,
            gridmap.ctypes.data_as(c_intp),  # Cast numpy array to ctypes integer pointer
            shape.ctypes.data_as(c_intp),
            start.ctypes.data_as(c_intp),
            finish.ctypes.data_as(c_intp)
        )

        path = [(path.data[i*2], path.data[i*2 + 1]) for i in range(path.length)]
        return path

    def __del__(self):
        """destruct unmanaged object"""
        return lib.Interface_delete(self.obj)


if __name__ == "__main__":
    cl = Interface('Frodo')
    # print(cl.simple_arguments(2, 5.1))
    #
    # a = cl.returning_string_as_pointer("xyz")
    # print(a)
    # print(len(a))
    #
    # print(cl.simple_arrays(list(range(10))))
    # b3 = cl.intersect_bboxes((0, 0, 2, 2), (1, 1, 3, 3))
    # print(b3.xmin, b3.ymin, b3.xmax, b3.ymax)

    # arr = np.random.randint(0, 5, (4, 3))
    # print(arr)
    # print(cl.multiply_by_3(arr))

    from utils import load_and_prepare_map

    gray, img = load_and_prepare_map("maps/maze.jpg")
    start = (10, 10)
    finish = (565, 630)
    print(cl.run_astar(gray, start, finish))


