# Ring Buffer in Kernel Space

The ring buffer comprises of a singly linked list with twenty initialized nodes. Test cases in kernel space are located in ```/tests/kernel_space_test```. The source code and test cases for user space counter-part is located at ```/tests/user_space_test```. For each application under ```/tests/``` you will find instructions on how to run them. This README covers the *implementation* of each syscall.
## Initializing the buffer

Before initializing the buffer, we run some security checks. First we check if a buffer already exists. If so, log a message to dmsg and return -1.

We proceed to initialize the buffer. We first initialize the ring buffer structure and allocate memory for it.
```c
ring_buf = malloc(sizeof(ring_buffer_421_t));
```

We check if an allocation error occurred. If it did, we log a message to dmsg and return -1.

If everything is ok we can proceed to initialize the buffer.

First step is to allocate memory for a single node. This single node's data is initialized to 0, and its ```next``` pointer is set to NULL. 

Now we can start using ```ring_buf```'s ```read``` and ```write``` pointers. We point ```read``` to the newly created node, and point ```write``` to ```read```. 

We are now ready to initialize the remaining 19 nodes and link them together. We'll to do with a for loop starting at 1 and finishing at 19. In each loop, we initialize a single node
```c
node_421_t *new = malloc(sizeof(node_421_t));
```
set its data to 0 and its next pointer to NULL. 

We now link the list by
```c
ring_buf->write->next = new;
ring_buf->write = new;
```

Finally, we make it circular
```c
ring_buf->write->next = ring_buf->read;	
```
The last step is to set the length of the buffer to 0 and return 0.

## Deleting the Buffer

If buffer does not exist we return -1. Else, we proceed to delete it. We'll do so with a loop starting at index 0 up to 19. In each iteration, we point a new node, ```temp```, to ```ring_buf->read```, then point ```ring_buf->read``` to ```ring_buf->read->next```. We can now 
```c
free(temp);
```
Once this is done, we free the memory allocated to the buffer itself, then set it to NULL.
```c
free(ring_buf);
ring_buf = NULL;
```

## Inserting to the Buffer

We first run some safety checks. If the buffer doesn't exist or if it's already full, we'll return -1 and print the appropriate error message to the kernel's log. 

Otherwise we're free to insert the integer. By design, ```ring_buf->write``` will be free to be written. We'll use it to write the integer passed. 

Now we must set 
```c
ring_buf->write = ring_buf->write->next;
```
And increase the buffer's length. 

## Printing the Buffer

We first check if the buffer actually exists. If it doesn't we print an error to the kernel's log and return -1. If it does we can proceed. 

We set a new node ```temp``` and point it to ```ring_buf->read```.

Now with a loop, we iterate over each node printing its content and after printing it, we set ```temp = temp->next```.
