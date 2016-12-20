#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bigint.h"


typedef struct BigInt * val_t;

struct Stack_Node 
{
	val_t val;
	struct Stack_Node *prev;
};

struct Stack
{
	struct Stack_Node *top;
};


struct Stack Stack_new();
void Stack_delete(struct Stack *);

bool Stack_empty(struct Stack *);

val_t * Stack_top(struct Stack *);
void Stack_push(struct Stack *, val_t);
void Stack_pop(struct Stack *);
