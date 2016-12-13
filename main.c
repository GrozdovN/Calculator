#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "bigint.h"


val_t * getArgs(struct Stack *s, val_t *second)
{
	if (!Stack_empty(s))
	{	
		val_t buf = *Stack_top(s);
		Stack_pop(s);
		if (!Stack_empty(s))
		{
			*second = buf;
			return Stack_top(s);
		}
		Stack_push(s, buf);
	}
	fprintf(stderr, "err: empty stack.\n");	
	return NULL;
}


int main()
{
	struct Stack s = Stack_new();	
	
	//struct BigInt *num = BigInt_new();
	//BigInt_delete(num);
	
	
	int oper, sign = 1;
	val_t *first, second;
	do
	{
		oper = getc(stdin);
		switch (oper) 
		{
			case '+' :	if((first = getArgs(&s, &second)) != NULL)
						{
							*first += second;
						}
						break;
			
			case '*' :	if((first = getArgs(&s, &second)) != NULL)
						{
							*first *= second;
						}
						break;
			
			case '/' :	if((first = getArgs(&s, &second)) != NULL)
						{
							*first /= second;
						}
						break;
			
			case '=' :	if (!Stack_empty(&s))
						{
							printf("%d\n", *Stack_top(&s));
						}
						break;
			
			case '-' :	oper = getc(stdin);
						if(!('0' <= oper && oper <= '9'))
						{
							ungetc(oper, stdin);
							if ((first = getArgs(&s, &second)) != NULL)
							{
								*first -= second;
							}
						}
						else
						{
							sign = -1;
						}
			
			default :	if ('0' <= oper && oper <= '9')
						{
							ungetc(oper, stdin);
							int a;
							scanf("%d", &a);
							a *= sign;
							sign = 1;
							Stack_push(&s, a);
						}
		}
	}
	while (oper != EOF);
	
	
	while (!Stack_empty(&s))
	{
		//BigNum_delete(*Stack_top(&s));
		Stack_pop(&s);
	}
	
		
	return 0;
}






