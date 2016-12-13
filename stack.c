//#pragma once
#include "stack.h"



struct Stack Stack_new()
{
	struct Stack s = {NULL};
	return s;
}

bool Stack_empty(struct Stack *s)
{
	return (s->top == NULL) ? true : false;
}

val_t * Stack_top(struct Stack *s)
{
	if (s->top == NULL)
	{
		return NULL;
	}
	return &(s->top->val);
}

void Stack_push(struct Stack *s, val_t v)
{
	struct Stack_Node *node = (struct Stack_Node *) malloc(sizeof(struct Stack_Node));
	node->val = v;
	node->prev = s->top;
	s->top = node;
	return;
}
void Stack_pop(struct Stack *s)
{
	if (s->top == NULL)
	{
		return;
	}
	struct Stack_Node *prev = s->top->prev;
	free(s->top);
	s->top = prev;
	return;
}

void Stack_delete(struct Stack *s)
{
	while (s->top != NULL)
	{
		Stack_pop(s);
	}
	return;
}






