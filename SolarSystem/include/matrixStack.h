#ifndef MATRIX_STACK_H
#define MATRIX_STACK_H

#include <cglm/cglm.h>

#define NUM_MATRICES 100

typedef struct {
  mat4 elements[NUM_MATRICES];
  int top;
} MStack;

MStack mStackInit();
// Pushes <element> on to <stack>
void mStackPush(MStack *stack, mat4 element);
// Pops from the top of <stack>, storing the popped element in <dest> (NULL if there is no dest)
void mStackPop(MStack *stack, mat4 dest);
// Returns the top of <stack>
vec4 *mStackGet(MStack *stack);
// Resets <stack.top> to 0
void mStackClear(MStack *stack);

#endif
