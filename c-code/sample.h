/**
 * Sample test functions in C, written to be called from Python.
 */

#ifndef _SAMPLE_H_
#define _SAMPLE_H_

typedef struct {
    float x;
    float y;
} point_t;

typedef struct {
    point_t p1;
    point_t p2;
} line_t;

float float_add(float x, float y);
float float_add_ref(float x, float *y);

point_t *point_get(point_t *p);
point_t *point_set(point_t *p, float x, float y);

line_t *line_get(line_t *line);
line_t *line_set(line_t *line, point_t *p1, point_t *p2);

#endif
