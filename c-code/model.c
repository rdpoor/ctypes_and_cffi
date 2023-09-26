/**
 * MIT License
 *
 * Copyright (c) 2023 Pro1iaq. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// *****************************************************************************
// Includes

#include "model.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// *****************************************************************************
// Private types and definitions

// *****************************************************************************
// Private (static) storage

// *****************************************************************************
// Private (forward) declarations

// *****************************************************************************
// Public code

/**
 * @brief Initialize the model
 */
model_t *model_init(model_t *model) {
    memset(model, 0, sizeof(model_t));
    return model;
}

model_t model_alloc(void) {
    return (model_t){};
}

float model_get_ambient(model_t *model) { return model->ambient; }
void model_set_ambient(model_t *model, float value) {
    printf("C: model_set_ambient(%p, %f\n", model, value);
    model->ambient = value;
}

float model_get_cool_setpoint(model_t *model) { return model->cool_setpoint; }
void model_set_cool_setpoint(model_t *model, float value) {
    printf("C: model_set_cool_setpoint(%p, %f\n", model, value);
    model->cool_setpoint = value;
}

float model_get_heat_setpoint(model_t *model) { return model->heat_setpoint; }
void model_set_heat_setpoint(model_t *model, float value) {
    printf("C: model_set_heat_setpoint(%p, %f\n", model, value);
    model->heat_setpoint = value;
}

system_mode_t model_get_system_mode(model_t *model) {
    return model->system_mode;
}
void model_set_system_mode(model_t *model, system_mode_t value) {
    printf("C: model_set_system_mode(%p, %d\n", model, value);
    model->system_mode = value;
}

bool model_get_relay_y(model_t *model) { return model->relay_y; }
void model_set_relay_y(model_t *model, bool value) {
    printf("C: model_set_relay_y(%p, %d\n", model, value);
    model->relay_y = value;
}

bool model_get_relay_w(model_t *model) { return model->relay_w; }
void model_set_relay_w(model_t *model, bool value) {
    printf("C: model_set_relay_w(%p, %d\n", model, value);
    model->relay_w = value;
}

const char *model_system_mode_to_string(system_mode_t system_mode) {
    const char *res = NULL;

    if (system_mode == SYSTEM_MODE_OFF) {
        res = "OFF";
    } else if (system_mode == SYSTEM_MODE_COOL) {
        res = "COOL";
    } else if (system_mode == SYSTEM_MODE_HEAT) {
        res = "HEAT";
    }
    printf("C: model_system_mode_to_string(%d) => %s\n", system_mode, res);
    return res;
}

model_t *model_apply_logic(model_t *model) {
    if (model->system_mode == SYSTEM_MODE_OFF) {
        model->relay_y = false;
        model->relay_w = false;
    } else if (model->system_mode == SYSTEM_MODE_COOL) {
        model->relay_y = model->cool_setpoint < model->ambient;
        model->relay_w = false;
    } else if (model->system_mode == SYSTEM_MODE_HEAT) {
        model->relay_y = false;
        model->relay_w = model->heat_setpoint > model->ambient;
    }

    printf("C: model_apply_logic(): m=%s, a=%f, c=%f, h=%f, y=>%d, w=%d\n",
        model_system_mode_to_string(model_get_system_mode(model)),
        model_get_ambient(model),
        model_get_cool_setpoint(model),
        model_get_heat_setpoint(model),
        model_get_relay_y(model),
        model_get_relay_y(model));

    return model;
}

const char *bool_to_string(bool value) {
    return value ? "True" : "False";
}

// *****************************************************************************
// Private (static) code

// *****************************************************************************
// End of file
