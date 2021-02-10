#include "bt_main.h"

//this will be used for the creation of the bluetooth application task and queue
//the queue will be used to hold messages (aka the callback functions that need to be completed) 
//and let the dispatcher know that the message will need to be processed 
static xQueueHandle bt_task_queue = NULL;
//this task will contain the while loop that would receive messages from the queue, process the 
//messages and then free any space that would need to be freed (space used by the message, for example) 
static xTaskHandle bt_task_handle = NULL;


/*this function will be used to create a bt queue and a bt task that would handle the receiving of messages
* ASSUME ---> BLUETOOTH STACK IS INITIALIZED AND ACTIVE(BLUEDROID AND THE CONTROLLER)
* PARAMETERS ---> N/A
* FUNCTION ---> creates a queue for bluetooth tasks
* RETURNS ---> N/A
*
Queue
 ________________________________________________
|   |   |    |    |    |    |    |    |    |    |
|___|___|____|____|____|____|____|____|____|____| 
  ^                                           ^          
  |                                           | 
  Last Message                              First Message
  to complete                               to complete

The task handler will be used to receive messages(aka the needed functions that need to be completed via 
callback functions)
*/
void bt_task_init()
{
	//this will be the queue that I will use in order to post bt messages 
	bt_task_queue = xQueueCreate(10, sizeof(bt_task_message));

	//this will be the task that I will use to process messages on the bt_task_queue
	xTaskCreate(bt_task_handler,"BluetoothTaskHandler",3072, NULL, configMAX_PRIORITIES - 3, &bt_task_handle);
}

//this function will be used for implementing tasks
void bt_task_handler()
{
	bt_task_message message;
	while(1)
	{
		//check to see if we received any messages onto the bt tasks queue
		if(xQueueReceive(bt_task_handle,&message,))
	}
}