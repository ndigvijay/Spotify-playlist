#include "dll.h"
#include <stdio.h>
#include <stdlib.h>
 
list_t* create_list()  // return a newly created empty doubly linked list
{
	// DO NOT MODIFY!!!
	list_t* l = (list_t*) malloc(sizeof(list_t));
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

void insert_front(list_t* list, int data)  // TODO: inserts data to the beginning of the linked list
{
	node_t* temp=malloc(sizeof(node_t));
	temp->next=NULL;
	temp->prev=NULL;
	temp->data=data;
	if(is_empty(list))
	{
		list->head=temp;
		list->tail=temp;
	}
	else
	{
		node_t *first=list->head;
		first->prev=temp;
		temp->next=first;
		list->head=temp;
	}
	list->size++;
}

void insert_back(list_t* list, int data) // TODO: inserts data to the end of the linked list
{
	node_t *temp=malloc(sizeof(node_t));
	temp->data=data;
	temp->next=NULL;
	temp->prev=NULL;
	if(is_empty(list))
	{
		list->head=temp;
		list->tail=temp;
		
	}
	else
	{
	list->tail->next=temp;
	temp->prev=list->tail;
	list->tail=list->tail->next;
	}
	list->size++;
}

void insert_after(list_t* list, int data, int prev) // TODO: inserts data after the node with data “prev”. Do not insert or do anything if prev doesn't exist
{
	node_t *temp=malloc(sizeof(node_t));
	temp->data=data;
	temp->next=temp->prev=NULL;
	node_t *curr=list->head;
	while(curr!=NULL)
	{
		if(curr->data==prev)
		{
			if(curr==list->tail)
			{
				insert_back(list,data);
				return;
			}
		temp->prev=curr;
		temp->next=curr->next;
		curr->next->prev=temp;
		curr->next=temp;
		return;	
		}
		curr=curr->next;
	}
	list->size++;
}

void delete_front(list_t* list) // TODO: delete the start node from the linked list.
{
	list->head=list->head->next;
	free(list->head->prev);
	list->size--;
}

void delete_back(list_t* list) // TODO: delete the end node from the linked list.
{
	node_t *curr=list->head;
	if(is_empty(list))
		return;
	if(list->head->next=NULL)
	{
		free(curr);
		list->head=list->tail=NULL;
	}
	list->tail=list->tail->prev;
	free(list->tail->next);
	list->tail->next=NULL;
	list->size--;
}

void delete_node(list_t* list, int data) // TODO: delete the node with “data” from the linked list.
{
	node_t *curr=list->head;
	if(is_empty(list))
		return;
	if(list->size==1 && curr->data==data)
	{
		free(curr);
		list->head=NULL;
		list->tail=NULL;
		return;
	}	
	while(curr!=NULL)
	{
		if(curr->data==data)
		{
			if(curr==list->head && curr->data==data)
			{
				delete_front(list);
				return;
			}
			if(curr==list->tail && curr->data==data)
			{
				delete_back(list);
				return;
			}
			curr->prev->next=curr->next;
			curr->next->prev=curr->prev;
			free(curr);
			list->size--;
			return;
		}
		curr=curr->next;
	}
}

node_t* search(list_t* list, int data) // TODO: returns the pointer to the node with “data” field. Return NULL if not found.
{
	node_t *curr=list->head;
	while(curr!=NULL)
		{
			if(curr->data==data)
				return(curr);
			curr=curr->next;
		}
	return(NULL);	
}

int is_empty(list_t* list) // return true or 1 if the list is empty; else returns false or 0
{
	// DO NOT MODIFY!!!
	return list->size == 0;
}

int size(list_t* list) // returns the number of nodes in the linked list.  
{
	// DO NOT MODIFY!!!
	return list->size;
}

void delete_nodes(node_t* head) // helper
{
	// DO NOT MODIFY!!!
	if(head == NULL)
		return;
	delete_nodes(head->next);
	free(head);	
}

void delete_list(list_t* list) // free all the contents of the linked list
{
	// DO NOT MODIFY!!!
	delete_nodes(list->head);
	free(list);
}

void display_list(list_t* list) // print the linked list by separating each item by a space and a new line at the end of the linked list.
{
	// DO NOT MODIFY!!!
	node_t* it = list->head;
	while(it != NULL)
	{
		printf("%d ", it->data);
		it = it->next;
	}
	printf("\n");
}

