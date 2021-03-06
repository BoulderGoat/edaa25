#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define DEBUG(message) printf("Line [%d] - %s\n", __LINE__, message);

typedef struct stack_node stack_node;

struct stack_node
{
	int data;
	stack_node *prev;
};

/*
struct stack {
	int stack_size = 0;
	stack_node *head;
};
*/

// void print_list(stack_node *stack_ptr)
// {
// 	 stack_node *tmp = stack_ptr;
// 	 printf("List: \n");
// 	 while(tmp != NULL)
// 	 {
// 		 printf("[%d, %p] -> ", tmp-> data, tmp-> prev);
// 		 tmp = tmp->prev;
// 	 }
// 	 printf("\n");
// }

stack_node *new_stack(int data)
{
	stack_node *first = malloc(sizeof(stack_node));
	first-> prev = NULL;
	first-> data = data;
	return first;
}

void push(stack_node **stack_ptr, int data)
{
	stack_node *new = malloc(sizeof(stack_node));

	new-> prev = *stack_ptr;
	new-> data = data;

	*stack_ptr = new;
}

int pop(stack_node **stack_ptr)
{
	int res;
	stack_node *tmp = *stack_ptr;
	*stack_ptr = (*stack_ptr)->prev;
	res = tmp->data;
	free(tmp);
	return res;
}

int isoperand(int c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

void free_stack(int *size, stack_node **stack_ptr)
{
	while (*size > 1) {
		pop(stack_ptr);
		(*size)--;
	}
}

int main()
{
	int stack_size = 1;
	int c = '\0';
	int count = 0;
	int i = 0;
	int last_digit = 0;
	stack_node *stack = new_stack(0);
	_Bool should_push = false;
	_Bool no_error = true;
	_Bool op_found = false;

	while ((c = getchar()) != EOF) {
		if (isdigit(c)) {
			should_push = true;
			i = i*10 + (c - '0');
			last_digit = c - '0';
		}
		if (!isdigit(c)) {
			if (!isoperand(c) && !isspace(c)) {
				printf("line %d: error at %c\n", ++count,
				(char)c);
				no_error = false;
			} else if (should_push) {
				if (stack_size < 11) {
					push(&stack, i);
					stack_size++;
				} else {
					printf("line %d: error at %d\n",
					++count, last_digit);
					no_error = false;
				}
			}
			i = 0;
			should_push = false;
		}
		if (isoperand(c)) {
			op_found = true;
			char op = (char)c;
			if (stack_size > 2) {
				int res = 0;
				int b = pop(&stack);
				stack_size--;
				int a = pop(&stack);
				stack_size--;
				switch (op) {
					case '*':
						res = a*b;
						break;
					case '/':
						if (b == 0) {
							printf(
				"line %d: error at %c\n", ++count, op);
							no_error = false;
						} else {
							res = a/b;
						}
						break;
					case '+':
						res = a+b;
						break;
					case '-':
						res = a-b;
						break;
				}
				push(&stack, res);
				stack_size++;
			} else {
				if (no_error) {
					printf("line %d: error at %c\n",
					++count, op);
					no_error = false;
				}
			}
		}
		if (c == '\n') {
			if (stack_size > 1 && no_error && op_found) {
				int res = pop(&stack);
				stack_size--;
				printf("line %d: %d\n", ++count, res);
			} else {
				if (no_error) {
					printf("line %d: error at %s\n",
					++count, "\\n");
				}
				if (stack_size > 1) {
					free_stack(&stack_size, &stack);
				}
			}
			no_error = true;
			op_found = false;
		}
	}
	free(stack);
	return 0;
}
