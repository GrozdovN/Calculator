#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef unsigned long digit_t;
typedef unsigned long long length_t;
const digit_t base = 1000000000;


struct BigInt_Node
{
	digit_t dig;
	struct BigInt_Node *prev, *next;
};

struct BigInt
{
	char isPositive;
	length_t length;
	struct BigInt_Node *head, *tail;
};



struct BigInt * BigInt_new();
void BigInt_delete(struct BigInt *);

void BigInt_read(struct BigInt *);
void BigInt_write(struct BigInt *);


bool BigInt_equals(struct BigInt *, struct BigInt *);
bool BigInt_lessThan(struct BigInt *, struct BigInt *);

void BigInt_add(struct BigInt *, struct BigInt *);
void BigInt_subtract(struct BigInt *, struct BigInt *);
void BigInt_multiply(struct BigInt *, struct BigInt *);
void BigInt_divide(struct BigInt *, struct BigInt *);
