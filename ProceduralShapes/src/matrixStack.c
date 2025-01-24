#include "matrixStack.h"

MStack mStackInit() {
  return (MStack){.top = 0};
}

void mStackPush(MStack *stack, mat4 element) {
  if (stack->top + 1 >= NUM_MATRICES) {
    printf("Stack Overflow\n");
    exit(EXIT_FAILURE);
  } 
  glm_mat4_copy(element, stack->elements[stack->top++]);
}

void mStackPop(MStack *stack, mat4 dest) {
  if (stack->top - 1 <= 0) {
    printf("Stack Underflow\n");
    exit(EXIT_FAILURE);
  }
  if (dest) {
    glm_mat4_copy(stack->elements[stack->top], dest);
  }
  stack->top--;
}

void mStackClear(MStack *stack) {
  stack->top = 0;
}

vec4 *mStackGet(MStack *stack) {
  return stack->elements[stack->top - 1];
}
