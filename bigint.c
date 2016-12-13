//#pragma once
#include "bigint.h"



struct BigInt* BigInt_new()
{
	struct BigInt *num = (struct BigInt *) malloc(sizeof(struct BigInt));
	struct BigInt tmp = { .isPositive = 1, .length = 0, .head = NULL, .tail = NULL};
	*num = tmp;
	return num;
}



void BigInt_delete(struct BigInt *number)
{
	if (number->tail != NULL)
	{
		for (struct BigInt_Node *node = number->head->next; node != NULL; node = node->next)
		{
			free(node->prev);
		}
		free(number->tail);
	}
	free(number);
	return;
}

void BigInt_read(struct BigInt *number)
{	
	return;
}

void BigInt_write(struct BigInt *number)
{	
	return;
}


bool BigInt_equals(struct BigInt *left, struct BigInt *right)
{	
	return true;
}
bool BigInt_lessThan(struct BigInt *left, struct BigInt *right)
{	
	return true;
}

void BigInt_add(struct BigInt *number, struct BigInt *increment)
{	
	return;
}
void BigInt_subtract(struct BigInt *number, struct BigInt *decrement)
{	
	return;
}
void BigInt_multiply(struct BigInt *number, struct BigInt *multiplier)
{	
	return;
}
void BigInt_divide(struct BigInt *number, struct BigInt *divider)
{	
	return;
}
