#ifndef SRC_STACK_H_
#define SRC_STACK_H_

// Abstract Data Type in C

#ifdef __cplusplus
extern "C" {
#endif

struct Stack* makeStack();
void destroyStack(struct Stack* s);
int  countStack(struct Stack* s);
void pushStack(struct Stack* s, int i);
int  topOfStack(struct Stack* s);
void popStack(struct Stack* s);

#ifdef __cplusplus
}
#endif


#endif /* SRC_STACK_H_ */
