#ifndef __BT_MAIN_H__
#define __BT_MAIN_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "freertos/xtensa_api.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "freertos/ringbuf.h"
//using the profiles that we need from bluetooth
//GAP, A2DP and AVRC
//GAP will be used to control connections and advertising in Bluetooth
#include "esp_gap_bt_api.h"
//using the bluetooth common device and main functions
#include "esp_bt_main.h"
#include "esp_bt_device.h"

//tags used for debugging
#define BT_GAP_TAG "BT_GAP"


//this will be the type of callback function that will be used for the task handler
//according to the API for Bluetooth Classic, there are events(enum type) and
//parameters(union of stuctures, of differing types)
typedef void (*bt_callback_function)(uint16_t event, void* param);

// //this will be the example structure of the message that we will be using
// //it should contain a callback function, events and parameters that would allow
// //us to use the callback function within the bt_task_handler
typedef struct
{
    bt_callback_function        callback_func;  //used by the dispatcher to implement the message
    uint16_t                    event;          //event parameter for the callback function
    void*                       param;          //parameters(union of structures) giving different parameters for the protocol
}bt_task_message;

//this function will be used to create a bt queue and a bt task 
void bt_task_init();

//this function will be used for implementing tasks and passing them 
//into the dispatcher for dispatching the messages
void bt_task_handler();

//this function would be used for setting up all of the profiles(GAP, A2DP and AVRC)
//this will also set up all the callback functions that are necessary for the implementation
//of the bluetooth speaker
void bt_profiles_set_up();

//this function will be used as the GAP callback function for GAP related events
void bt_gap_callback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t* parameter);

#endif /*end of __BT_MAIN_H*/


