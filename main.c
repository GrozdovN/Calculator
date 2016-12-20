#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
	
	int ch;
	char isNegative;
	val_t *first, second;
	do
	{
		ch = getc(stdin);
		switch (ch) 
		{
			case '+' :	if((first = getArgs(&s, &second)) != NULL)
						{
							//*first += second;
							BigInt_add(*first, second);
							BigInt_delete(second);
						}
						break;
			
			case '*' :	if((first = getArgs(&s, &second)) != NULL)
						{
							//*first *= second;
							BigInt_multiply(*first, second);
							BigInt_delete(second);
						}
						break;
			
			case '/' :	if((first = getArgs(&s, &second)) != NULL)
						{
							//*first /= second;
							BigInt_divide(*first, second);
							BigInt_delete(second);
						}
						break;
			
			case '=' :	if (!Stack_empty(&s))
						{
							//printf("%d\n", *Stack_top(&s));
							BigInt_write(*Stack_top(&s));
						}
						break;
			
			case '-' :	ch = getc(stdin);
						if(!isdigit(ch))
						{
							ungetc(ch, stdin);
							if ((first = getArgs(&s, &second)) != NULL)
							{
								//*first -= second;
								BigInt_subtract(*first, second);
								BigInt_delete(second);
							}
						}
						else
						{
							isNegative = 1;
						}
			
			default :	if (isdigit(ch))
						{
							ungetc(ch, stdin);
							struct BigInt *num = BigInt_new();
							BigInt_read(num);
							num->isNegative = isNegative;
							isNegative = 0;
							Stack_push(&s, num);
						}
		}
	}
	while (ch != EOF);
	
	
	while (!Stack_empty(&s))
	{
		BigInt_delete(*Stack_top(&s));
		Stack_pop(&s);
	}
	
		
	return 0;
}






