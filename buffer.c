#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"


const int SIZE = 20;
const int INIT_VAL = 0;
struct ring_buffer *ring_buf = NULL;

long init_buffer(void)
{
	int i;
	
	// Buffer already exists
	if(ring_buf){
		printf("Error: Cannot reinitialize a buffer. Exiting...\n");
		return -1;
	}
	
	ring_buf = malloc(sizeof(ring_buffer_t));
	
	// Allocation error
	if (!ring_buf){
		printf("Error: Allocation error. Exiting...");
		return -1;
	}
		
	node_t *node = malloc(sizeof(node_t));
	node->data = 0;
	node->next = NULL;
	ring_buf->read = node;
	ring_buf->write = ring_buf->read;
	
	// Start populating all remaining 19 nodes
	for (i = 1; i < SIZE; i++){
		node_t *new = malloc(sizeof(node_t));
		new->data = INIT_VAL;
		new->next = NULL;
		ring_buf->write->next = new;
		ring_buf->write = new;
	}
	
	//Make it circular
	ring_buf->write->next = ring_buf->read;	
	ring_buf->length = 0;
	return 0;
}

long delete_buffer(void)
{
	if(ring_buf){
		int i;
	
		// Free individual nodes
		for (i = 0; i < SIZE; i++){
			node_t *temp = ring_buf->read;
			ring_buf->read = ring_buf->read->next;
			free(temp);
		}
		// Free buffer itself
		free(ring_buf);
		ring_buf = NULL;
		return 0;
	}
	printf("Error: Cannot delete non-existant buffer. Exiting...\n");
	return -1;
}



long insert_buffer(int i)
{
	int index = 0;
	
	// Buffer doesn't exist or full
	if(!ring_buf){
		printf("Error: Cannot insert into non-existant buffer. Exiting...\n");
		return -1;
	}
	
	if(ring_buf->length == SIZE){
		printf("Error: Buffer is full - insert failed. Exiting...\n");
		return -1;
	}
	
	ring_buf->write->data = i;
	ring_buf->write = ring_buf->write->next;
	++(ring_buf->length);
	return 0;
}

long print_buffer(void)
{
	
	if (!ring_buf){
		printf("Error: Cannot print non-existant buffer. Exiting...\n");
		return -1;
	}
	
	int i;
	node_t *temp = ring_buf->read;
	
	for (i = 0; i < SIZE; i++){
		printf("Address is %p  ||| Value is %d\n", temp, temp->data);
		temp = temp->next;
	}	
	return 0;
}

int main(void)
{	

	int insert_int = 300, increment = 50;
	init_buffer();
	init_buffer(); // Already initialized, shouldn't allow
	delete_buffer();
}