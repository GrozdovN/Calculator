//#pragma once
#include "bigint.h"

const digit_t BigInt_base = 1000000000;







struct BigInt_Node * BigInt_pushFront(struct BigInt *number, digit_t digit)
{
	struct BigInt_Node	*node = (struct BigInt_Node *) malloc(sizeof(struct BigInt_Node));	
	node->digit = digit;
	node->prev = NULL;
	
	if (number->head == NULL)
	{
		node->next = NULL;
		number->head = node;
		number->tail = node;
	}
	else
	{
		node->next = number->head;
		number->head->prev = node;
		number->head = node;
	}
	
	++(number->length);	
	return node;
}

struct BigInt_Node * BigInt_pushBack(struct BigInt *number, digit_t digit)
{
	struct BigInt_Node	*node = (struct BigInt_Node *) malloc(sizeof(struct BigInt_Node));	
	node->digit = digit;
	node->next = NULL;
	
	if (number->head == NULL)
	{
		node->prev = NULL;
		number->head = node;
		number->tail = node;
	}
	else
	{
		node->prev = number->tail;
		number->tail->next = node;
		number->tail = node;
	}
	
	++(number->length);	
	return node;
}







struct BigInt * BigInt_new()
{
	struct BigInt *num = (struct BigInt *) malloc(sizeof(struct BigInt)); 
	num->isNegative = 0; 
	num->length = 0;
	num->head = NULL;
	num->tail = NULL;
	return num;
}

void BigInt_delete(struct BigInt *number)
{
	if (number->tail != NULL)
	{
		for (struct BigInt_Node *node = number->head->next; node != NULL; )
		{
			free(node->prev);
			node = node->next;
		}
		free(number->tail);
	}
	free(number);
	return;
}







void BigInt_read(struct BigInt *number)
{	
	number->isNegative = 0; 
	number->length = 0;
	number->head = NULL;
	number->tail = NULL;
	
	char buf[10], c = 'a';
	int i = 0;
	
	c = getc(stdin);
	if (c == '-')
	{
		number->isNegative = 1;
	}
	else if (isspace(c))
	{
		return;
	}
	else
	{
		ungetc(c, stdin);
	}
	
	do
	{
		c = getc(stdin);
	}
	while (c == '0');
	if (isspace(c))
	{
		BigInt_pushBack(number, 0);
		return;
	}
	ungetc(c, stdin);
	
	do
	{
		i = 0;
		do
		{
			buf[i++] = c = getc(stdin);
		}
		while (i < 9 && !isspace(c));
		if (isspace(c))
		{
			--i;
		}
		if (i == 0)
		{
			return;
		}
		buf[i] = '\0';
				
		char *p;
		digit_t digit = strtol(buf, &p, 10);		
		
		BigInt_pushBack(number, digit);
	} 
	while (!isspace(c));
	
	
	if (0 < i && i < 9 && number->length > 1)
	{
		for (struct BigInt_Node *node = number->tail->prev; node != NULL; )
		{
			digit_t pow10i = 1;
			for(int j = 0; j < i; ++j)
			{
				pow10i *= 10;
			}
			node->next->digit += (node->digit % (BigInt_base / pow10i)) * pow10i;
			node->digit /= (BigInt_base / pow10i);
			node = node->prev;
		}
	}
	
	return;
}

void BigInt_write(struct BigInt *number)
{	
	if (number->head != NULL)
	{
		if(number->isNegative && !(number->head->digit == 0 && number->length == 1))
		{
			putc('-', stdout);
		}
		for (struct BigInt_Node *node = number->head; node != NULL; )
		{
			printf("%.9ld ", node->digit);
			node = node->next;
		}
	}
	putc('\n', stdout);
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







void BigInt_inc(struct BigInt *number, struct BigInt *increment, digit_t coefficient)
{	
	long long	res = 0, carry = 0, 
				signN = (number->isNegative) ? -1 : 1, 
				signI = (increment->isNegative) ? -1 : 1;
	if (coefficient*signI <= 0)
	{
		return;
	} 
	if (signN * signI == 1)
	{
		signN = signI = 1;
	}
	struct BigInt_Node	*number_node = number->tail, 
						*increment_node = increment->tail;
	struct BigInt *nullNumber = BigInt_new();
	BigInt_pushBack(nullNumber, 0);
	
	while (number_node != NULL || increment_node != NULL || carry > 0)
	{
		if (increment_node == NULL)
		{
			increment_node = nullNumber->head;
		}
		if (number_node == NULL)
		{
			number_node = BigInt_pushFront(number, 0);
		}
		res = signN*(number_node->digit) + coefficient*signI*(increment_node->digit) + carry;
		carry = (res + BigInt_base) / BigInt_base - 1;
		number_node->digit = (res + BigInt_base) % BigInt_base;
		
		number_node = number_node->prev;
		increment_node = increment_node->prev;
	}
	
	if (carry == -1)
	{
		number_node = number->head;
		for ( ;number_node != NULL; number_node = number_node->next)
		{
			number_node->digit = BigInt_base - 1 - number_node->digit;
		}
		nullNumber->head->digit = 1;
		number->isNegative = false;
		BigInt_inc(number, nullNumber, 1);
		number->isNegative = true;
	}
	else if (signN * signI == -1)
	{
		number->isNegative = false;		
	}
	
	number_node = number->head;
	while(number->length > 1 && number_node->digit == 0)
	{
		number_node = number_node->next;
		free(number_node->prev);
		--(number->length);
	}
	number->head = number_node;
	number->head->prev = NULL;
	
	BigInt_delete(nullNumber);
	return;


}
void BigInt_add(struct BigInt *number, struct BigInt *increment)
{	
	BigInt_inc(number, increment, 1);
}

void BigInt_subtract(struct BigInt *number, struct BigInt *decrement)
{	
	decrement->isNegative = !decrement->isNegative;
	BigInt_inc(number, decrement, 1);
	decrement->isNegative = !decrement->isNegative;
	return;
}







void BigInt_multiply(struct BigInt *number, struct BigInt *multiplier)
{	
	struct BigInt *result = BigInt_new();	
	BigInt_pushBack(result, 0);	
	struct BigInt_Node *tail = result->tail;
	char isNegative = 0;	
			
	if (!(number->length == 1 && number->head->digit == 0)
		&& !(multiplier->length == 1 && multiplier->head->digit == 0))
	{
		//printf("mdeeeeeeeems\n");
		isNegative = ((number->isNegative) ^ (multiplier->isNegative));
		number->isNegative = false;
		multiplier->isNegative = false;
			
		struct BigInt_Node	*curNode = multiplier->tail;
		for ( ; curNode != NULL; curNode = curNode->prev)
		{
			if (result->tail == NULL)
			{
				BigInt_pushFront(result, 0);
				result->tail = result->head;
			}
			BigInt_inc(result, number, curNode->digit);
			result->tail = result->tail->prev;
		}
	}

	result->tail = tail;
	result->isNegative = isNegative;
	BigInt_delete(number);
	number = BigInt_new();
	*number = *result;
	
	return;
}
void BigInt_divide(struct BigInt *number, struct BigInt *divider)
{	
	return;
}	
