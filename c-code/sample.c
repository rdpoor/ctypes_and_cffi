/**
 * Sample test functions in C, written to be called from Python.
 */

#include "sample.h"
#include <stdio.h>
#include <string.h>

float float_add(float x, float y) {
    float sum = x + y;
    printf("in C add_two(%f, %f) => %f\n", x, y, sum);
    return sum;
 }

float float_add_ref(float x, float *y) {
    float sum = x + *y;
    printf("in C add_two(%f, @%p->%f) => %f\n", x, y, *y, sum);
    return sum;
}

point_t *point_get(point_t *p) {
    printf("in C point<%p>(%f, %f\n", p, p->x, p->y);
    return p;
}

point_t *point_set(point_t *p, float x, float y) {
    printf("in C point_set(<%p>, %f, %f\n", p, x, y);
    p->x = x;
    p->y = y;
    return p;
}

point_t *point_move(point_t *p) {
    p->x += 1;
    p->y += 1;
    return p;
}

line_t *line_get(line_t *line) {
    printf("in C line<%p>:\n", line);
    printf("  p1 ");
    point_get(&line->p1);
    printf("  p2 ");
    point_get(&line->p2);
    return line;
}

line_t *line_set(line_t *line, point_t *p1, point_t *p2) {
    point_set(&line->p1, p1->x, p1->y);
    point_set(&line->p2, p2->x, p2->y);
    return line;
}

/**
 * @brief The simple_function function simply returns counting numbers. Each
 * time it is called in increments counter and returns that value.
 */
int simple_function(void) {
    static int counter = 0;
    counter++;
    return counter;
}

/**
 * @brief The add_one_to_string function adds one to each character in a char
 * array that is passed in. We’ll use this to talk about Python’s immutable
 * strings and how to work around them when we need to.
 */
void add_one_to_string(char *input) {
    int ii = 0;
    for (; ii < strlen(input); ii++) {
        input[ii]++;
    }
}

