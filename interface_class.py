from ctypes import *
import numpy.ctypeslib as npct
import numpy as np
lib = cdll.LoadLibrary('./libinterface_class.so')
# lib = npct.load_library('libinterface_class', '.')

# TODO box structure

# TODO astar path output


class Interface:

    def __init__(self, name):
        lib.Interface_new.argtypes = [c_char_p]
        lib.Interface_new.restype = c_void_p

        # TODO arugment types for all methods

        name = c_char_p(name.encode('utf-8'))
        self.obj = lib.Interface_new(name)

    def simple_arguments(self, i, f):
        # TODO
        return

    def simple_arrays(self, l):
        # TODO
        return

    def returning_string_as_pointer(self, s):
        # TODO
        return

    def intersect_bboxes(self, bbox1, bbox2):
        # TODO
        return

    def multiply_by_3(self, arr):
        # TODO
        return

    def run_astar(self, gridmap, start, finish):
        # TODO
        return

    def __del__(self):
        """destruct unmanaged object"""
        return lib.Interface_delete(self.obj)


if __name__ == "__main__":
    import cv2
    from PIL import Image
    cl = Interface('Frodo')
    # print(cl.simple_arguments(2, 5.1))

    # a = cl.returning_string_as_pointer("xyz")
    # print(a)
    # print(len(a))

    # print(cl.simple_arrays(list(range(10))))
    # b3 = cl.intersect_bboxes((0, 0, 2, 2), (1, 1, 3, 3))
    # print(b3.xmin, b3.ymin, b3.xmax, b3.ymax)

    # arr = np.random.randint(0, 5, (4, 3))
    # print(arr)
    # print(cl.multiply_by_3(arr))

    # from utils import load_and_prepare_map
    # gray, img, start, finish = load_and_prepare_map("maps/maze.jpg")
    # path = cl.run_astar(gray, start, finish)
    #
    # for i in range(len(path)-1):
    #     x, y = path[i]
    #     x1, y1 = path[i + 1]
    #     if 0 <= x <= img.shape[1] and 0 <= y <= img.shape[1]:
    #         # x, x1 = np.clip((x, x1), 0, img.shape[1])
    #         # y, y1 = np.clip((y, y1), 0, img.shape[0])
    #         cv2.line(img, (x, y), (x1, y1), (0, 255, 0), 1)
    #     else:
    #         break
    #
    # img = cv2.resize(img, (700, 700))
    # Image.fromarray(img).show()



