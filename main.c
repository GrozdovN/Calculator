#include <stdio.h>
#include "stack.h"


int main()
{
	struct stack s = stack_new();	
	for (int i = 0; i < 10; ++i)
	{
		stack_push(&s, i);
		printf("%d\n", stack_top(&s));
	}
	
	stack_pop(&s);
	printf("%d\n", stack_top(&s));
	
	
	stack_delete(&s);	
	printf("%d\n", s.top);
	
	return 0;
}
