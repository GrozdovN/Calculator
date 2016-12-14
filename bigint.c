//#pragma once
#include "bigint.h"



const digit_t BigInt_base = 1000000000;




struct BigInt* BigInt_new()
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
	bool leadingZero = true;
	
	c = getc(stdin);
	if (c == '-')
	{
		number->isNegative = 1;
	}
	else 
	{
		ungetc(c, stdin);
	}
	
	
	do
	{
		bool digitFinded = false;
		for (i = 0 ; i < 9 && !isspace(c); )
		{
			buf[i] = c = getc(stdin);
			if (!digitFinded && isdigit(c))
			{
				digitFinded = true;
			}
			i = ((!isdigit(c) || (leadingZero && c == '0')) ? i : i + 1);
			if (leadingZero && isdigit(c) && c != '0')
			{
				leadingZero = false;
			}
		}
		if (isspace(buf[0]))
		{
			if (digitFinded)
			{
				buf[0] = '0';
				i = 2;
			}
			else 
			{
				return;
			}
		}
		//i = ((i < 9) ? i - 1 : i);
		buf[i] = '\0';
				
		char *p;
		digit_t digit = strtol(buf, &p, 10);		
		
		struct BigInt_Node *node = (struct BigInt_Node *) malloc(sizeof(struct BigInt_Node));
		node->digit = digit;
		node->next = NULL;
		if (number->length == 0)
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
		if(number->isNegative && number->head->digit != 0)
		{
			putc('-', stdout);
		}
		for (struct BigInt_Node *node = number->head; node != NULL; )
		{
			printf("%lu ", node->digit);
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
