# About `ctypes_and_cffi`

This repository demonstrates two approaches for accessing C functions and data
structures from Python code, `ctypes` and `cffi`.

Two sub-directories, `ctypes-eg` and `cffi-eg`, each provide a makefile that
sets up the proper environment and calls `test_model.py` using the same source
code, and both provide the same results.

The main differences betwen `ctypes` and `cffi` can be summarized as follows:
* ctypes is built into Python -- no external package.  `cffi` is an external
module.
* In `ctypes`, you must declare structures and function signatures in Python to
parallel the C-side structures and function signatures.  `cffi` parses the C
sources to automate (almost) all of that.
* `ctypes` sets up all the interfaces at runtime.  `cffi` requirs an extra
compilation step to generate a `.so` file.
* `ctypes` incurs more runtime overhead.  `cffi` is more runtime efficient.

## Short synopsis

### Set up the environment
```
r@NUC-10:/mnt/c/Users/r/Projects/Pro1/git/ctypes_and_cffi$ pipenv shell
Launching subshell in virtual environment...
 . /home/r/.local/share/virtualenvs/ctypes_and_cffi-3BtaEe2O/bin/activate
r@NUC-10:/mnt/c/Users/r/Projects/Pro1/git/ctypes_and_cffi$  . /home/r/.local/share/virtualenvs/ctypes_and_cffi-3BtaEe2O/bin/activate
```
### Run `ctypes` version of `test_model`
```
(ctypes_and_cffi) r@NUC-10:/mnt/c/Users/r/Projects/Pro1/git/ctypes_and_cffi$ cd ctypes-eg/
(ctypes_and_cffi) r@NUC-10:/mnt/c/Users/r/Projects/Pro1/git/ctypes_and_cffi/ctypes-eg$ make
gcc -shared -o libmodel.so model.o
./test_model.py
m1 = <__main__.c_model object at 0x7fad18fc2fc0>
C: model_set_ambient(0x7fad18e50230, 23.400000
m1.ambient = 23.399999618530273
C: model_set_system_mode(0x7fad18e50230, 2
m1.system_mode = 2
C: model_system_mode_to_string(2) => HEAT
b'HEAT'
C: model_set_heat_setpoint(0x7fad18e50230, 24.500000
C: model_system_mode_to_string(2) => HEAT
C: model_apply_logic(): m=HEAT, a=23.400000, c=0.000000, h=24.500000, y=>0, w=0
y=False, w=True
```
### Run `cffi` version of `test_model`
```
(ctypes_and_cffi) r@NUC-10:/mnt/c/Users/r/Projects/Pro1/git/ctypes_and_cffi/ctypes-eg$ cd ../cffi-eg/
(ctypes_and_cffi) r@NUC-10:/mnt/c/Users/r/Projects/Pro1/git/ctypes_and_cffi/cffi-eg$ make
# technique to get around cffi's lack of #include support
gcc -E model.h > model.h.preprocessed
./build_model.py
./test_model.py
=== Using low-level ffi calls:
m1 = <cdata 'model_t *' owning 20 bytes>
C: model_set_ambient(0x7fffc91bac10, 23.400000
m1.ambient = 23.399999618530273
C: model_set_system_mode(0x7fffc91bac10, 2
m1.system_mode = 2
C: model_system_mode_to_string(2) => HEAT
b'HEAT'
C: model_set_heat_setpoint(0x7fffc91bac10, 24.500000
C: model_system_mode_to_string(2) => HEAT
C: model_apply_logic(): m=HEAT, a=23.400000, c=0.000000, h=24.500000, y=>0, w=0
y=False, w=True
=== Using Python wrappers:
m2 = <__main__.Model object at 0x7f0b079c89a0>, m2.model = <cdata 'model_t *' owning 20 bytes>
C: model_set_ambient(0x7fffc91bac60, 23.400000
m2.ambient = 23.399999618530273
C: model_set_system_mode(0x7fffc91bac60, 2
m2.system_mode = 2
C: model_system_mode_to_string(2) => HEAT
b'HEAT'
C: model_set_heat_setpoint(0x7fffc91bac60, 24.500000
C: model_system_mode_to_string(2) => HEAT
C: model_apply_logic(): m=HEAT, a=23.400000, c=0.000000, h=24.500000, y=>0, w=0
y=False, w=True
(ctypes_and_cffi) r@NUC-10:/mnt/c/Users/r/Projects/Pro1/git/ctypes_and_cffi/cffi-eg$

```

## Some links

## CTYPES

| To find out the correct calling convention you have to look into the C header file or the documentation for the function you want to call.

https://dbader.org/blog/python-ctypes-tutorial
https://github.com/jima80525/ctypes_example/tree/master
https://towardsdatascience.com/do-you-hate-how-slow-python-is-this-is-how-you-can-make-it-run-faster-532468fe1583
https://docs.python.org/3/library/ctypes.html

## CFFI

| CFFI automakes (most but not all) of the typing, but requires an extra one-
time compilation step.

https://dbader.org/blog/python-cffi
https://github.com/jima80525/ctypes_example/tree/master
https://towardsdatascience.com/make-python-faster-with-cffi-python-bindings-eb5402bc35dd
https://cffi.readthedocs.io/en/latest/cdef.html

## Both
https://realpython.com/python-bindings-overview/
https://github.com/realpython/materials/tree/master/python-bindings


