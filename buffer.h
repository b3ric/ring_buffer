#ifndef BUFFER_H
#define BUFFER_H
#ifdef __cplusplus

extern "C" {
	
#endif
#define SIZE_OF_BUFFER 20

typedef struct node {
struct node *next;
int data;
} node_t;

typedef struct ring_buffer {
int length;
node_t *read;
node_t *write;
} ring_buffer_t;

#ifndef __KERNEL__
long init_buffer(void);
long insert_buffer(int i);
long print_buffer(void);
long delete_buffer(void);

#endif
#ifdef __cplusplus
}

#endif
#endif