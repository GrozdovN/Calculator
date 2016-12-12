#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef int val_t;

struct stack__node 
{
	val_t val;
	struct stack__node *prev;
};

struct stack
{
	struct stack__node *top;
};


struct stack stack_new();
void stack_delete(struct stack *);

bool stack_empty(struct stack);

val_t stack_top(struct stack *);
void stack_push(struct stack *, val_t);
void stack_pop(struct stack *);
