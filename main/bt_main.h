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
#include "driver/i2s.h"
#include "freertos/ringbuf.h"


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

//this function will be used for implementing tasks
void bt_task_handler();



#endif /*end of __BT_MAIN_H*/


