#!/usr/bin/env python
from _model import lib, ffi

class Model():
    def __init__(self):
        # NOTE:
        #   self is <Model object at 0x7f827bd306a0>
        #   self.model is <cdata 'model_t *' owning 20 bytes>
        self.model = ffi.new("model_t *")

    def set_ambient(self, celsius):
        lib.model_set_ambient(self.model, celsius)

    def get_ambient(self):
        return lib.model_get_ambient(self.model)

    def set_heat_setpoint(self, celsius):
        lib.model_set_heat_setpoint(self.model, celsius)

    def set_system_mode(self, system_mode):
        lib.model_set_system_mode(self.model, system_mode)

    def get_system_mode(self):
        return lib.model_get_system_mode(self.model)

    def get_relay_y(self):
        return lib.model_get_relay_y(self.model)

    def get_relay_w(self):
        return lib.model_get_relay_w(self.model)

    def apply_logic(self):\
        lib.model_apply_logic(self.model)

def system_mode_to_string(system_mode):
    return ffi.string(lib.model_system_mode_to_string(system_mode))

if __name__ == '__main__':
    # using low-level ffi calls...
    print('=== Using low-level ffi calls:')
    m1 = ffi.new("model_t *")
    print(f'm1 = {m1}')
    lib.model_set_ambient(m1, 23.4)
    print(f'm1.ambient = {lib.model_get_ambient(m1)}')
    lib.model_set_system_mode(m1, lib.SYSTEM_MODE_HEAT)
    print(f'm1.system_mode = {lib.model_get_system_mode(m1)}')
    print(ffi.string(lib.model_system_mode_to_string(lib.model_get_system_mode(m1))))
    lib.model_set_heat_setpoint(m1, 24.5)
    lib.model_apply_logic(m1)
    print(f'y={lib.model_get_relay_y(m1)}, w={lib.model_get_relay_w(m1)}')

    # using Python wrappers...
    print('=== Using Python wrappers:')
    m2 = Model()
    print(f'm2 = {m2}, m2.model = {m2.model}')
    m2.set_ambient(23.4)
    print(f'm2.ambient = {m2.get_ambient()}')
    m2.set_system_mode(lib.SYSTEM_MODE_HEAT)
    print(f'm2.system_mode = {m2.get_system_mode()}')
    print(system_mode_to_string(m2.get_system_mode()))
    m2.set_heat_setpoint(24.5)
    m2.apply_logic()
    print(f'y={m2.get_relay_y()}, w={m2.get_relay_w()}')
