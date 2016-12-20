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
		struct BigInt_Node *node = number->head->next;
		for ( ; node != NULL; node = node->next)
		{
			free(node->prev);
		}
		free(number->tail);
	}
	free(number);
	return;
}


void BigInt_copy(struct BigInt *from, struct BigInt *to)
{
	to->length = 0;
	to->isNegative = from->isNegative; 
	to->head = NULL;
	to->tail = NULL;
	
	struct BigInt_Node *node = from->head;
	for ( ; node != NULL; node = node->next)
	{
		BigInt_pushBack(to, node->digit);
	}
	
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
		struct BigInt_Node *node = number->tail->prev;
		for ( ; node != NULL; node = node->prev)
		{
			digit_t pow10i = 1;
			for(int j = 0; j < i; ++j)
			{
				pow10i *= 10;
			}
			node->next->digit += (node->digit % (BigInt_base / pow10i)) * pow10i;
			node->digit /= (BigInt_base / pow10i);
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
		struct BigInt_Node *node = number->head;
		for ( ; node != NULL; node = node->next)
		{
			printf("%.9ld ", node->digit);
		}
	}
	putc('\n', stdout);
	return;
}







bool BigInt_equals(struct BigInt *left, struct BigInt *right)
{	
	if (left->length != right->length 
		|| left->isNegative != right->isNegative)
	{
		return false;
	}
	struct BigInt_Node	*lNode = left->head,
						*rNode = right->head;
	while (lNode != NULL && rNode != NULL)
	{
		if (lNode->digit != rNode->digit)
		{
			return false;
		}
		lNode = lNode->next;
		rNode = rNode->next;
	}
	
	return true;
}
bool BigInt_lessThan(struct BigInt *left, struct BigInt *right)
{	
	if (left->length < right->length 
		|| (left->isNegative && !right->isNegative))
	{
		return true;
	}
	if (left->length > right->length
		|| (!left->isNegative && right->isNegative))
	{
		return false;
	}
	
	struct BigInt_Node	*lNode = left->head,
						*rNode = right->head;
	bool t = true, f = false;
	if (left->isNegative && right->isNegative)
	{
		t = false;
		f = true;
	}
	
	while (lNode != NULL && rNode != NULL)
	{
		if (lNode->digit < rNode->digit)
		{
			return t;
		}
		if (lNode->digit > rNode->digit)
		{
			return f;
		}
		lNode = lNode->next;
		rNode = rNode->next;
	}

	return false;
}







void BigInt_inc(struct BigInt *number, struct BigInt *increment, long long coefficient)
{	
	long long	res = 0, carry = 0, 
				signN = (number->isNegative) ? -1 : 1, 
				signI = (increment->isNegative) ? -1 : 1;
	if (coefficient < -1)
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
	return;
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
	char isNegative = 0, m_isNegative = 0;	
			
	if (!(number->length == 1 && number->head->digit == 0)
		&& !(multiplier->length == 1 && multiplier->head->digit == 0))
	{
		//printf("mdeeeeeeeems\n");
		isNegative = ((number->isNegative) ^ (multiplier->isNegative));
		m_isNegative = multiplier->isNegative;
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
	
	multiplier->isNegative = m_isNegative;

	result->tail = tail;
	result->isNegative = isNegative;
	BigInt_delete(number);
	number = BigInt_new();
	*number = *result;
	
	return;
}







void BigInt_divide(struct BigInt *number, struct BigInt *divider)
{	
	if (divider->length == 1)
	{
		if (divider->head->digit == 0)
		{
			fprintf(stderr, "err: divide by 0.\n");	
		}
		if (divider->head->digit <= 1)
		{
			return;
		}
	}
	
	char isNegative = ((number->isNegative) ^ (divider->isNegative)),
		d_isNegative = divider->isNegative;
	number->isNegative = false;
	divider->isNegative = false;

	struct BigInt	*quotient = BigInt_new(),
					*residual = BigInt_new(),
					*dShifted = BigInt_new(),
					*_1       = BigInt_new(),
					*tmp      = BigInt_new();
	BigInt_pushBack(_1, 1);
	BigInt_pushBack(tmp, 0);
	BigInt_copy(divider, dShifted);	
	
	
	struct BigInt_Node *node = number->head;
	for ( ; node != NULL; node = node->next)
	{
		BigInt_pushBack(quotient, 0);
		BigInt_pushBack(residual, 0);
		tmp->head->digit = node->digit;
		BigInt_add(residual, tmp);
		
		long long	coef = 0, 
					pow_10_i = BigInt_base;
		BigInt_pushBack(dShifted, 0);

		for (int i = 8; i >= 0; --i)
		{
			pow_10_i /= 10;
			//dShifted /= 10;
			dShifted->tail->digit /= 10;
			long long _b = BigInt_base / 10; // = 100 000 000
			struct BigInt_Node *dS_node = dShifted->tail->prev;
			for ( ; dS_node != NULL; dS_node = dS_node->prev)
			{
				dS_node->next->digit += (dS_node->digit % 10) * _b;
				dS_node->digit /= 10;
			}
			if (dShifted->head->digit == 0)
			{
				--(dShifted->length);
				dShifted->head = dShifted->head->next;
				free(dShifted->head->prev);
				dShifted->head->prev = NULL;
			}			
			
			while (!BigInt_lessThan(residual, dShifted))
			{
				coef += pow_10_i;
				BigInt_subtract(residual, dShifted);
			}
		}
		
		BigInt_inc(quotient, _1, coef);
	}
	
	
	quotient->isNegative = isNegative;
	divider->isNegative = d_isNegative;
	
	BigInt_delete(number);
	number = BigInt_new();
	*number = *quotient;
	
	BigInt_delete(residual);
	BigInt_delete(_1);
	BigInt_delete(tmp);
	BigInt_delete(dShifted);
	
	return;
}	
