#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/* CREATION FUNCTIONS */
node *create_node(int number)
{
	node *new_node = malloc(sizeof(node));

	if (new_node == NULL)
	{
		exit(EXIT_FAILURE);
	}

	new_node->n = number;
	new_node->next = NULL;

	return new_node;
}

/* LOOKUP FUNCTIONS */
node *find_node(node *head, int number)
{
	node *tmp = head;

	while (tmp != NULL)
	{
		if (tmp->n == number)
		{
			return tmp;
		}

		tmp = tmp->next;
	} 
	
	printf("Error: the value %d does not exist in the linked list passed in as argument\n", number);
	exit(EXIT_FAILURE);
}

/* INSERTION FUNCTIONS */
void insert_node_at_beginning(node **head, node *node_to_insert)
{
	node_to_insert->next = *head;
	*head = node_to_insert;
}

void insert_node_at_end(node **head, node *node_to_insert)
{
	// If list is empty, insert at beginning
	if (*head == NULL)
	{
		insert_node_at_beginning(head, node_to_insert);
	}
	else
	{

		node *tmp = *head;

		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}

		tmp->next = node_to_insert;
	}
}

void insert_node_after_another(node *node_to_insert_after, node *node_to_insert)
{
	node_to_insert->next = node_to_insert_after->next;
	node_to_insert_after->next = node_to_insert;
}

/* DELETION FUNCTIONS */
void delete_first_node(node **head)
{
	if (head == NULL || *head == NULL)
	{
		return;
	}
	
	node *tmp = *head;
	tmp = tmp->next;
	free(*head);
	*head = tmp;
}

void delete_last_node(node *head)
{
	node *tmp = head;

	while (tmp->next->next != NULL)
	{
		tmp = tmp->next;
	}

	node *node_to_delete = tmp->next;
	tmp->next = NULL;
	free(node_to_delete);
}

void delete_node(node *head, node *node_to_delete)
{
	// If node_to_delete is the first node
	if (node_to_delete == head)
	{
		delete_first_node(&head);
		return;
	}

	// If node_to_delete is the last node
	if (node_to_delete->next == NULL)
	{
		delete_last_node(head);
		return;
	}

	// If node_to_delete is in the middle
	node *tmp = head;

	while (tmp != NULL)
	{
		if (tmp->next == node_to_delete)
		{
			tmp->next = node_to_delete->next;
			free(node_to_delete);
			return;
		}

		tmp = tmp->next;
	}

	printf("Error: the node with the value %d does not exist in the list passed in as argument\n", node_to_delete->n);
}

void delete_list(node **head)
{	
	node *tmp = NULL;

	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}

	*head = NULL;
}

/* PRINTING FUNCTIONS */
void print_list(node *head)
{
	if (head == NULL)
	{
		printf("List empty\n");
		return;
	}

	node *tmp = head;

	while (tmp->next != NULL)
	{
		printf("%d - ", tmp->n);
		tmp = tmp->next;
	} 
	printf("%d\n", tmp->n);
}

/* ANALYSIS FUNCTIONS */
int count_nodes(node *head)
{
	node *tmp = head;
	int count = 0;

	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}

	return count;
}

int count_if_nodes(node *head, int value, int (*op)(int, int))
{
	node *tmp = head;
	int count = 0;

	while (tmp != NULL)
	{
		if (op(tmp->n, value))
		{
			count++;
		}

		tmp = tmp->next;
	}

	return count;
}

int sum_nodes(node *head)
{
	node *tmp = head;
	int sum = 0;

	while (tmp != NULL)
	{
		sum += tmp->n;
		tmp = tmp->next;
	}

	return sum;
}

int sum_if_nodes(node *head, int value, int (*op)(int, int))
{
	node *tmp = head;
	int sum = 0;

	while (tmp != NULL)
	{
		if (op(tmp->n, value))
		{
			sum += tmp->n;
		}

		tmp = tmp->next;
	}

	return sum;
}

float average_nodes(node *head)
{
	return (float) sum_nodes(head) / (float) count_nodes(head);
}

float average_if_nodes(node *head, int value, int (*op)(int, int))
{
	return (float) sum_if_nodes(head, value, op) / (float) count_if_nodes(head, value, op);
}

int equal(int a, int b)
{
	return a == b;
}

int greater_than_or_equal(int a, int b)
{
	return a >= b;
}

int greater_than(int a, int b)
{
	return a > b;
}


int less_than_or_equal(int a, int b)
{
	return a <= b;
}

int less_than(int a, int b)
{
	return a < b;
}

/* ORDERING FUNCTIONS */
void sort_list(node **headRef, int (*op)(int, int))
{
	node *head = *headRef;
	node *a, *b;

	// Base case
	if (head == NULL || head->next == NULL)
	{
		return;
	}

	split_list(head, &a, &b);

	sort_list(&a, op);
	sort_list(&b, op);

	*headRef = merge_sort(a, b, op);
}

void split_list(node *head, node **first_half, node **second_half)
{
	node *slow = head;
	node *fast = head->next;

	// 'Fast' moves 2x as fast as 'slow'
	// Before making second move of 'fast' we check if we reached end
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	// 'Slow' is right before the midpoint of the list
	// It 'next' value points to the beginning of the second half of the list
	*first_half = head;
	*second_half = slow->next;
	slow->next = NULL;
}

node *merge_sort(node *a, node *b, int (*op)(int, int))
{
	node *result = NULL;

	// Base case
	if (a == NULL)
	{
		return b;
	}
	else if (b == NULL)
	{
		return a;
	}

	if (op(a->n, b->n))
	{
		result = a;
		result->next = merge_sort(a->next, b, op);
	}
	else
	{
		result = b;
		result->next = merge_sort(a, b->next, op);
	}
	return result;
}
	
int ascending(int a, int b)
{
	return a < b;
}

int descending(int a, int b)
{
	return a > b;
}

void reverse_list(node **head)
{
	node *prev = NULL;
	node *curr = *head;
	node *next = NULL;

	while (curr != NULL)
	{
		// Saving the 'next' value of the curr
		next = curr->next;
		// Point curr to the previous node
		// If first, then point to NULL because it will be the last
		curr->next = prev;

		// Move further down the list
		prev = curr;
		curr = next;
	}

	*head = prev;
}

