#include<stdlib.h>
#include<stdio.h>

struct node
{
	int data;
	struct node *next;
};

struct list
{
	struct node *head;
};

struct list *list_create()
{
	struct list *sl = malloc(sizeof(struct list));
	
	sl->head = malloc(sizeof(struct node));
	sl->head->next = NULL;
	 
	return sl;
} 

int main()
{
	
	return 0; 
}
