#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_system.h"
//ESP32 logging system
#include "esp_log.h"

//using the controller &VHCI API
#include "esp_bt.h"

//using the bluetooth common device and main functions
#include "esp_bt_main.h"
#include "esp_bt_device.h"

//using the profiles that we need from bluetooth
//GAP, A2DP and AVRC
//GAP will be used to control connections and advertising in Bluetooth
#include "esp_gap_bt_api.h"

//A2DP will be used for streaming of audio data from the phone to the
//device (ESP32)
#include "esp_a2dp_api.h"

//AVRC will be used to have the phone send commands to the speaker(play, pause,etc)
#include "esp_avrc_api.h"

//i2s will be used as a communication protocol to output audio data from bluetooth to
// a Class D amplifier I will build on my own
#include "driver/i2s.h"

//Tags for debugging 
#define BT_CONTROLLER_TAG "BT_CONTROLLER"

//this will be the example structure of the message that we will be using
//it should contain a callback function, events and parameters that would allow
//us to use the callback function within the bt_task_handler
typedef struct
{

}bt_task_message;

//this will be used for the creation of the bluetooth application task and queue
//the queue will be used to hold messages (aka the callback functions that need to be completed) 
//and let the dispatcher know that the message will need to be processed 
static xQueueHandle bt_task_queue = NULL;
//this task will contain the while loop that would receive messages from the queue, process the 
//messages and then free any space that would need to be freed (space used by the message, for example) 
static xTaskHandle bt_task_handle = NULL;


//this function will be used to create a bt queue and a bt task 
void bt_task_init()
{
	bt_task_queue = xQueueCreate(10, sizeof(bt_task_message));
}



void app_main()
{
	//PART 1: Initializing the bluetooth controller and host
	//-----------------------------------------------------------------------------------
	//since we use Classic Bluetooth, no need of
	//using BLE, so free BLE controller memory
	//ESP_ERROR_CHECK is an assert, and if it fails, abort the program
	//and print the error information to serial output
	ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

	//in case there is no problem releasing the controller memory,
	//enable controller memory for Classic Bluetooth
	esp_bt_controller_config_t controller_configuration = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

	//check to see if the controller initializing went okay
	int error_code;
	if((error_code = esp_bt_controller_init(&controller_configuration))!=ESP_OK)
	{
		ESP_LOGE(BT_CONTROLLER_TAG,"Bluetooth controller initialization failed,%s",esp_err_to_name(error_code));
	}
	else
	{
		ESP_LOGI(BT_CONTROLLER_TAG,"Bluetooth controller initialized successfully!\n");
	}
	//check to see if the controller enabling goes okay
		if((error_code = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT))!=ESP_OK)
	{
		ESP_LOGE(BT_CONTROLLER_TAG,"Bluetooth controller could not be enabled,%s",esp_err_to_name(error_code));
	}
	else
	{
		ESP_LOGI(BT_CONTROLLER_TAG,"Bluetooth controller was enabled successfully!\n");
	}

	//check to see if the host (Bluedroid) initializing goes okay
		if((error_code = esp_bluedroid_init())!=ESP_OK)
	{
		ESP_LOGE(BT_CONTROLLER_TAG,"Bluedroid initialization failed,%s",esp_err_to_name(error_code));
	}
	else
	{
		ESP_LOGI(BT_CONTROLLER_TAG,"Bluedroid initialized successfully!\n");
	}

	//check to see if Bluedroid enabling goes okay
		if((error_code = esp_bluedroid_enable())!=ESP_OK)
	{
		ESP_LOGE(BT_CONTROLLER_TAG,"Bluedroid could not be enabled,%s",esp_err_to_name(error_code));
	}
	else
	{
		ESP_LOGI(BT_CONTROLLER_TAG,"Bluedroid was enabled successfully!\n");
	}
	
	//----------------------------------------------------------------------------------------------
	//PART 2:Setting up the profiles (GAP, A2DP and AVRC)
	//first start by creating a bluetooth task
	bt_task_init();
	
}

