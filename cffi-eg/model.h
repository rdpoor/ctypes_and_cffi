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

/**
 * @file model.h
 *
 * @brief model represents the internal state of a toy-tstat.  This module
 * provides methods for getting and setting individual fields, as well as
 * a pair of methods to convert the model to and from a JSON representation.
 */

#ifndef _MODEL_H_
#define _MODEL_H_

// *****************************************************************************
// Includes

#include <stdbool.h>

// *****************************************************************************
// C++ Compatibility

#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************
// Public types and definitions

typedef enum {
    SYSTEM_MODE_OFF,
    SYSTEM_MODE_COOL,
    SYSTEM_MODE_HEAT
} system_mode_t;

typedef struct {
    float ambient;
    float cool_setpoint;
    float heat_setpoint;
    system_mode_t system_mode;
    bool relay_y;
    bool relay_w;
} model_t;

// *****************************************************************************
// Public declarations

/**
 * @brief Initialize the model
 */
model_t *model_init(model_t *model);

float model_get_ambient(model_t *model);
void model_set_ambient(model_t *model, float value);

float model_get_cool_setpoint(model_t *model);
void model_set_cool_setpoint(model_t *model, float value);

float model_get_heat_setpoint(model_t *model);
void model_set_heat_setpoint(model_t *model, float value);

system_mode_t model_get_system_mode(model_t *model);
void model_set_system_mode(model_t *model, system_mode_t value);

bool model_get_relay_y(model_t *model);
void model_set_relay_y(model_t *model, bool value);

bool model_get_relay_w(model_t *model);
void model_set_relay_w(model_t *model, bool value);

const char *model_system_mode_to_string(system_mode_t system_mode);

model_t *model_apply_logic(model_t *model);

const char *bool_to_string(bool value);

// *****************************************************************************
// End of file

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _MODEL_H_ */
