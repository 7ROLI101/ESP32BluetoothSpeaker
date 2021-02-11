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
* FUNCTION ---> creates a queue for bluetooth tasks (the adding of tasks to the queue will be handled by the 
  scheduler, and the removing of tasks to perform them will be handled by the dispatcher)
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

/*this function will be used for implementing tasks and passing them 
  into the dispatcher for dispatching the messages
* ASSUME ---> the bluetooth stack is active, and there is a bt queue and a bt task active 
* PARAMETERS ---> N/A
* FUNCTION ---> receives messages that were sent to the queue and prepares them for dispatching. 
The dispatcher would gives the process you are dispatching control of the CPU/resources.
* RETURNS ---> N/A
*/
void bt_task_handler()
{
	bt_task_message message;
	while(1)
	{
		//check to see if we received any messages onto the bt tasks queue
		if(xQueueReceive(bt_task_handle,&message,portMAX_DELAY)==pdTRUE)
		{
			//if we have received any messages from the queue, then pass them into the dispatcher for completion


		}
	}
}

/*this function would be used for setting up all of the profiles(GAP, A2DP and AVRC)
* ASSUME ---> the bluetooth stack is active, bt queue and bt task needs to be active 
* PARAMETERS ---> N/A
* FUNCTION ---> sets up the profiles for use later on
* RETURNS ---> N/A
*/
void bt_profiles_set_up()
{
	//setting up name of the device for easy finding when pairing up
	esp_bt_dev_set_device_name("LoudMouth");
	//now register the callback function to get back in case an event occurs for the GAP profile
	esp_bt_gap_register_callback(bt_gap_callback);

	//set it up as discoverable
	esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE,ESP_BT_GENERAL_DISCOVERABLE);
}


/*this function would be used as the callback function for the GAP profile
* ASSUME ---> the bluetooth stack is active, bt queue and bt task needs to be active 
* PARAMETERS ---> events from the possible list of events in enum esp_bt_gap_cb_event_t,
 			      parameter from the possible list of structures in esp_bt_gap_cb_param_t 
* FUNCTION ---> callback function is used in order to get back to this function and perform
				functions related to the event that we are performing 
* RETURNS ---> N/A
*/
void bt_gap_callback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t* parameter)
{
	//here is where we account for the states that we are interested in 
	switch(event)
	{
		case ESP_BT_GAP_AUTH_CMPL_EVT:
		{
			//in case the authentication was successfully completed 
			if(parameter->auth_cmpl.stat  == ESP_BT_STATUS_SUCCESS)
			{
				ESP_LOGI(BT_GAP_TAG,"Bluetooth authentification completed successfully!");
			}
			else
			{
				ESP_LOGE(BT_GAP_TAG,"Bluetooth authentification failed with error # %d",parameter->auth_cmpl.stat);
			}
			break;
		}
		default:
		ESP_LOGE(BT_GAP_TAG,"Unhandled event # %d inside of ",parameter->auth_cmpl.stat);

	}
}

