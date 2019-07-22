	 ________         __            _________          
	/ ______|        |  |          |____    _|         
	| |   _____      |  |               /  /           
	| |  |_   _|     |  |              /  /            
	| |____| |       |  |____       __/  /____         
	\________|       |_______|     |__________|        
 Copyright (C) 2013 - 2020, liangzhiGuo, <lz_kwok@163.com>, et al 
 msp430_ucOS_II
=====================
## 1. hal_layer_api.c
### 1.1. int Hal_ThreadCreate(void *func, void *funcname,void *TaskStk, int stack_size,int priority)  ###
Create tasks and set stack pointers, sizes, and priorities for tasks

### 1.2. int Hal_ThreadDestory(int priority)  ###
Destroy tasks, enter parameters as priority of tasks

### 1.3. int Hal_QueueCreate(void **start,int size)  ###
Create a message queue with parameters of array pointer and queue size. The size of array pointer should be no less than queue size.

### 1.4. int Hal_QueueDestory(Queue_t queue)  ###
Destroy message queue with input parameter as queue pointer to destroy

### 1.5. Hal_QueueSend(Queue_t queue, struct hal_message* msg, int timeout)  ###
Send message function. Send message is a structure pointer, which includes message type and message content.

### 1.6. Hal_QueueRecv(Queue_t queue, struct hal_message* msg, int timeout)  ###
Receiving message function, receiving message is a structure pointer, which includes message type and message content.

