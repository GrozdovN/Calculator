#pragma once
#include "stack.h"



struct stack stack_new()
{
	struct stack s = {NULL};
	return s;
}

bool stack_empty(struct stack s)
{
	return (s.top == NULL) ? true : false;
}

val_t stack_top(struct stack *s)
{
	return s->top->val;
}

void stack_push(struct stack *s, val_t v)
{
	struct stack__node *node = (struct stack__node *) malloc(sizeof(struct stack__node));
	node->val = v;
	node->prev = s->top;
	s->top = node;
	return;
}

void stack_pop(struct stack *s)
{
	//bigInt_delete(s.top->val)
	if (s->top == NULL) return;
	struct stack__node *prev = s->top->prev;
	free(s->top);
	s->top = prev;
	return;
}

void stack_delete(struct stack *s)
{
	while (s->top != NULL)
	{
		stack_pop(s);
	}
	return;
}






