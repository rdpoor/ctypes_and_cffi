#!/usr/bin/env python
"""
Simple examples of calling C functions through ctypes module

Synopsis:
  python pipenv shell
  make all
  make clean # optional
"""
import ctypes
import os

# define enum values that parallel the C definition
(SYSTEM_MODE_OFF, SYSTEM_MODE_COOL, SYSTEM_MODE_HEAT) = (0, 1, 2)

# define a Structure that parallels the C definition
class c_model(ctypes.Structure):
    _fields_ = [
        ("ambient", ctypes.c_float),
        ("cool_setpoint", ctypes.c_float),
        ("heat_setpoint", ctypes.c_float),
        ("system_mode", ctypes.c_int),
        ("relay_y", ctypes.c_bool),
        ("relay_w", ctypes.c_bool)]

if __name__ == "__main__":

    # NOTE: There's almost certainly a way to wrap all the function definitions
    # into a c_model class so it behaves more like a regular Python class, but I
    # haven't found an idiom that feels right yet.  So keeping it simple...

    libname = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                           "libmodel.so"))
    LIBC = ctypes.CDLL(libname)

    LIBC.model_set_ambient.argtypes = [ctypes.POINTER(c_model), ctypes.c_float]
    LIBC.model_get_ambient.argtypes = [ctypes.POINTER(c_model)]
    LIBC.model_get_ambient.restype = ctypes.c_float

    LIBC.model_set_heat_setpoint.argtypes = [ctypes.POINTER(c_model), ctypes.c_float]
    LIBC.model_get_heat_setpoint.argtypes = [ctypes.POINTER(c_model)]
    LIBC.model_get_heat_setpoint.restype = ctypes.c_float

    LIBC.model_set_system_mode.argtypes = [ctypes.POINTER(c_model), ctypes.c_int]
    LIBC.model_get_system_mode.argtypes = [ctypes.POINTER(c_model)]
    LIBC.model_get_system_mode.restype = ctypes.c_int

    LIBC.model_get_relay_y.argtypes = [ctypes.POINTER(c_model)]
    LIBC.model_get_relay_y.restype = ctypes.c_bool

    LIBC.model_get_relay_w.argtypes = [ctypes.POINTER(c_model)]
    LIBC.model_get_relay_w.restype = ctypes.c_bool

    LIBC.model_apply_logic.argtypes = [ctypes.POINTER(c_model)]
    LIBC.model_apply_logic.restype = ctypes.POINTER(c_model)

    LIBC.model_system_mode_to_string.argtypes = [ctypes.c_int]
    LIBC.model_system_mode_to_string.restype = ctypes.c_char_p

    m1 = c_model()
    print(f'm1 = {m1}')
    LIBC.model_set_ambient(m1, 23.4)
    print(f'm1.ambient = {LIBC.model_get_ambient(m1)}')
    LIBC.model_set_system_mode(m1, SYSTEM_MODE_HEAT)
    print(f'm1.system_mode = {LIBC.model_get_system_mode(m1)}')
    print(LIBC.model_system_mode_to_string(LIBC.model_get_system_mode(m1)))
    LIBC.model_set_heat_setpoint(m1, 24.5)
    LIBC.model_apply_logic(m1)
    print(f'y={LIBC.model_get_relay_y(m1)}, w={LIBC.model_get_relay_w(m1)}')
