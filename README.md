	 ________         __            _________          
	/ ______|        |  |          |____    _|         
	| |   _____      |  |               /  /           
	| |  |_   _|     |  |              /  /            
	| |____| |       |  |____       __/  /____         
	\________|       |_______|     |__________|        
 Copyright (C) 2018 - present, liangzhiGuo, <lz_kwok@163.com>, et al 
 msp430_ucOS_II
## Note : ##
### 1. The branch of "master" is the original branch, so you can't upload code at will. You can test your own code in the branch of "develop" and Refer to the following steps: ###
### 2. git clone https://github.com/lz-kwok/msp430_ucOS_II.git ###
### 3. git checkout develop ###
### 4. git branch ###
to check if your local branch is "develop"
=============================================================================================================================================================================
## 1. hal_layer_api.c ##
### 1.1. int Hal_ThreadCreate(void (*func)(void *p_arg), void *funcname,OS_STK *TaskStk, int priority)  ###
Create tasks and set stack pointers, sizes, and priorities for tasks

### 1.2. int Hal_ThreadDestory(int priority)  ###
Destroy tasks, enter parameters as priority of tasks

### 1.3. int Hal_QueueCreate(void **start,int size)  ###
Create a message queue with parameters of array pointer and queue size. The size of array pointer should be no less than queue size.

### 1.4. int Hal_QueueDestory(Queue_t queue)  ###
Destroy message queue with input parameter as queue pointer to destroy

### 1.5. Hal_QueueSend(Queue_t queue, struct hal_message* msg, int timeout)  ###
Send message function. Send message is a structure pointer, which includes message type and message content.

### 1.6 int Hal_QueueNum_Waitfor_Pend(Queue_t queue) ###
query Number of messages waiting in the queue

### 1.7. Hal_QueueRecv(Queue_t queue, struct hal_message* msg, int timeout)  ###
Receiving message function, receiving message is a structure pointer, which includes message type and message content.

### 1.8. Mutex_t Hal_MutexCreate(int priority) ###
Create a mutually exclusive semaphore with input parameters as the priority of the semaphore

### 1.9. Mutex_t Hal_MutexCreate(Mutex_t mutex) ###
Destroy mutually exclusive semaphore and input parameter is the pointer of the semaphore

### 2.0. Mutex_t Hal_MutexLock(Mutex_t mutex) ###
Obtain the right to use semaphores

### 2.1. Mutex_t Hal_MutexUnlock(Mutex_t mutex) ###
Release semaphore usage rights

### 2.2. void Hal_EnterLowPower_Mode(void) ###
Enter Low Power Mode

### 2.3. void Hal_ExitLowPower_Mode(void) ###
Exit Low Power Mode

## 2. app.c ##
There are three threads in the app.c,which are scada task, transmission task and management task.
### 2.1. static  void  ScadaTaskStart (void *p_arg)  ###