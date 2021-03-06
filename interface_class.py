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

        lib.Interface_delete.argtypes = [c_void_p]

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
        gridmap = gridmap.astype(np.int32)
        gridmap[gridmap == 0] = 9
        gridmap[gridmap == 255] = 1
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
    import cv2
    from time import time
    from PIL import Image
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

    gray, img, start, finish = load_and_prepare_map("maps/maze.jpg")
    s = time()
    path = cl.run_astar(gray, start, finish)
    print("astar run {} secs".format(time() - s))

    for i in range(len(path)-1):
        x, y = path[i]
        x1, y1 = path[i + 1]
        if 0 <= x <= img.shape[1] and 0 <= y <= img.shape[1]:
            # x, x1 = np.clip((x, x1), 0, img.shape[1])
            # y, y1 = np.clip((y, y1), 0, img.shape[0])
            cv2.line(img, (x, y), (x1, y1), (0, 255, 0), 1)
        else:
            break

    img = cv2.resize(img, (700, 700))
    Image.fromarray(img).show()


