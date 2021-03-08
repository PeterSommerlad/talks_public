#include "Stack.h"
#include <stdlib.h>
#include <assert.h>

typedef struct Stack {
	int top;
	int thestack[10];
} Stack;


Stack* makeStack() {
	void* s = calloc(1, sizeof(Stack));
	return (Stack*) (s);
}

int countStack(Stack* s) {
	return s->top;
}

void destroyStack(Stack* s) {
	free(s);
}

void pushStack(Stack* s, int i) {
	s->thestack[s->top++] = i;
	assert(s->top <= (sizeof(s->thestack) / sizeof(*(s->thestack))));
}

int topOfStack(Stack* s) {
	assert(s->top > 0 && (s->top <= (sizeof(s->thestack) / sizeof(*(s->thestack)))));
	return s->thestack[s->top - 1];
}

void popStack(Stack* s) {
	assert(s->top > 0);
	s->top--;
}
