/**
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "queue.h"
#include "btstack.h"
#include "temp_sensor.h"
#include "server_common.h"
#include "pico/cyw43_arch.h"

#define SERVER_DEVICE_NAME "PicoW-HT"
uint uIReceivedValue = 10;
uint uISentValue = 2;
static QueueHandle_t TxQueue;
static QueueHandle_t RxQueue;
uint16_t led_brightness_scale = 0;
typedef enum {
    CLIENT_STOP=0,
    QUERY_SERVICE,
    QUERY_CHARACTERISTIC_TEMPERATURE,
    QUERY_CHARACTERISTIC_HUMIDITY,
    ENABLE_NOTIFICATION,
    ENABLE_COMPLETE
} client_event_query_t;

typedef enum {
    SERVER_STOP=0

} server_event_query_t;

typedef enum {
    SERVER=1,
    CLIENT

} ble_state_t;

typedef struct {
    hci_con_handle_t con_handle_value;
    ble_state_t state;

} handle_type_t;
int x;
handle_type_t handle_type[7] = {0};
ble_state_t ble_state = SERVER;
client_event_query_t client_event_query;
server_event_query_t server_event_query;
gatt_client_notification_t notification_listener_temp, notification_listener_humi;
static hci_con_handle_t connection_handler;
gatt_client_service_t environmental_sensing;
gatt_client_characteristic_t temperature, humidity;
static btstack_packet_callback_registration_t hci_event_callback_registration;
static TaskHandle_t client_taskHandle = NULL;
static void handle_hci_event(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);
static void handle_gatt_client_event(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);
static hci_con_handle_t con_handler;
int connection_type;
uint16_t temp_i, humi_i;
static int le_notification_enabled;
static uint16_t current_temp;
uint8_t const profile_data[];
static btstack_timer_source_t heartbeat;
static TaskHandle_t server_taskHandle = NULL;
int i;
#define APP_AD_FLAGS 0x06

uint8_t service_uuid128[]={
	    0x00,0x00,0x06,0x50,0x37,0xE4,0x4E,0x5D,0x95,0x92,0x69,0x32,0x7D,0x12,0x88,0x40
};
uint8_t char_led_brightness_uuid128[]={
	    0x00,0x00,0x06,0x51,0x37,0xE4,0x4E,0x5D,0x95,0x92,0x69,0x32,0x7D,0x12,0x88,0x40
};
uint8_t char_set_led_brightness_uuid128[]={
	    0x00,0x00,0x06,0x52,0x37,0xE4,0x4E,0x5D,0x95,0x92,0x69,0x32,0x7D,0x12,0x88,0x40
};
	 

uint8_t adv_data[] = {
	    // Flags: 0x02: General Discoverable Mode, 0x04:BR/EDR Not Supported
	    0x02, BLUETOOTH_DATA_TYPE_FLAGS, 0x06,
	    // Local Name
	    0x09, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME, 'P', 'i', 'c', 'o', 'W', '-', 'H','1', 
	    0x11, BLUETOOTH_DATA_TYPE_COMPLETE_LIST_OF_128_BIT_SERVICE_CLASS_UUIDS,
	    0x40, 0x88,0x12,0x7D,0x32,0x69,0x92,0x95, 0x5D,0x4E, 0xE4,0x37,0x60, 0x06,0x00, 0x00,
	};

static const uint8_t adv_data_len = sizeof(adv_data);

static uint16_t att_read_callback(hci_con_handle_t connection_handle, uint16_t att_handle, uint16_t offset, uint8_t * buffer, uint16_t buffer_size){
   
    if (att_handle == ATT_CHARACTERISTIC_00000661_37E4_4E5D_9592_69327D128840_01_VALUE_HANDLE){      
            att_server_request_can_send_now_event(connection_handle);
            return att_read_callback_handle_little_endian_16(temp_i, offset, buffer, buffer_size);

    }
    if (att_handle == ATT_CHARACTERISTIC_00000662_37E4_4E5D_9592_69327D128840_01_VALUE_HANDLE){          
            uint16_t ret = att_read_callback_handle_little_endian_16(humi_i, offset, buffer, buffer_size);
            att_server_request_can_send_now_event(connection_handle);
            return ret;
    }
    
    return 0;
}


static int att_write_callback(hci_con_handle_t connection_handle, uint16_t att_handle, uint16_t transaction_mode, uint16_t offset, uint8_t *buffer, uint16_t buffer_size){
    UNUSED(transaction_mode);
    UNUSED(offset);
    UNUSED(buffer_size);
    
    if (att_handle == ATT_CHARACTERISTIC_00000661_37E4_4E5D_9592_69327D128840_01_CLIENT_CONFIGURATION_HANDLE
        || att_handle == ATT_CHARACTERISTIC_00000662_37E4_4E5D_9592_69327D128840_01_CLIENT_CONFIGURATION_HANDLE) {
            le_notification_enabled = little_endian_read_16(buffer, 0) == GATT_CLIENT_CHARACTERISTICS_CONFIGURATION_NOTIFICATION;
            con_handler = connection_handle;
        }

        
    if (att_handle == ATT_CHARACTERISTIC_00000661_37E4_4E5D_9592_69327D128840_01_VALUE_HANDLE) {
	        led_brightness_scale = little_endian_read_16(buffer, 0);
            //cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_brightness_scale);
            xQueueSend(TxQueue, ( void * ) &led_brightness_scale, ( TickType_t ) 0);
	        printf("led_brightness_scale:%d\n", led_brightness_scale);
}
    

    return 0;
}
static void heartbeat_handler(struct btstack_timer_source *ts) {
    //printf("aloo");
    if (le_notification_enabled && (uxQueueMessagesWaiting(RxQueue) != 0)) {
        xQueueReceive(RxQueue, &uISentValue, (TickType_t)10);
        printf("Sending value from server:%d", uISentValue);
        att_server_request_can_send_now_event(con_handler);
    }

    btstack_run_loop_set_timer(ts, HEARTBEAT_PERIOD_MS);
    btstack_run_loop_add_timer(ts);
}


static void handle_hci_event(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
    UNUSED(channel);
    UNUSED(size);
    bd_addr_t addr;
    bd_addr_type_t addr_type; 
    if (packet_type != HCI_EVENT_PACKET) return;
    
    uint8_t event = hci_event_packet_get_type(packet);
    switch (event) {
        case BTSTACK_EVENT_STATE:
            if (btstack_event_state_get_state(packet) != HCI_STATE_WORKING) return;
            // setup advertisements
            uint16_t adv_int_min = 800;
            uint16_t adv_int_max = 800;
            uint8_t adv_type = 0;
            bd_addr_t null_addr;
            memset(null_addr, 0, 6);
            gap_advertisements_set_params(adv_int_min, adv_int_max, adv_type, 0, null_addr, 0x07, 0x00);
            assert(adv_data_len <= 31); // ble limitation
            gap_advertisements_set_data(adv_data_len, (uint8_t*) adv_data);
            // BTstack activated, get started
            gap_set_scan_parameters(0,0x0030, 0x0030);
            gap_advertisements_enable(1);
            gap_start_scan();
            break;
        case GAP_EVENT_ADVERTISING_REPORT:
            //printf("Scan Device...");
            if(1){
            const uint8_t * adv_data = gap_event_advertising_report_get_data(packet);
            uint8_t adv_len  = gap_event_advertising_report_get_data_length(packet);
            if (ad_data_contains_uuid128(adv_len, adv_data, service_uuid128)) {
                gap_event_advertising_report_get_address(packet, addr);
                addr_type = gap_event_advertising_report_get_address_type(packet);
                //gap_stop_scan();
                //ble_state = CLIENT;
                gap_connect(addr, addr_type);}
            }
            break;
        case HCI_EVENT_LE_META:
            // wait for connection complete
            if (hci_event_le_meta_get_subevent_code(packet) !=  HCI_SUBEVENT_LE_CONNECTION_COMPLETE) break;
            //printf("I'm Now Connected to a");
            connection_type = hci_subevent_le_connection_complete_get_role(packet);
            if(!connection_type){
            connection_handler = hci_subevent_le_connection_complete_get_connection_handle(packet);
            // query primary services
            client_event_query=QUERY_SERVICE;
             for (i = 0; i < 7; i++) {
                if (handle_type[i].con_handle_value == 0) {
                     // Add the value to the first zero element found
                    handle_type[i].con_handle_value = connection_handler;
                    handle_type[i].state = CLIENT;
                    break; // Exit the loop once the value is added
        }}
            printf("my client state is %d\n",connection_handler);
            gatt_client_discover_primary_services_by_uuid128(handle_gatt_client_event, connection_handler,
                        service_uuid128);}
            else{
            con_handler = hci_subevent_le_connection_complete_get_connection_handle(packet);
            for (i = 0; i < 7; i++) {
                if (handle_type[i].con_handle_value == 0) {
                     // Add the value to the first zero element found
                    handle_type[i].con_handle_value = con_handler;
                    handle_type[i].state = SERVER;
                    break; // Exit the loop once the value is added
        }}
            printf("my server state is %d\n",con_handler);
            }
            break;
        case HCI_EVENT_DISCONNECTION_COMPLETE:
            //printf("Device Disconn");
            x = hci_event_disconnection_complete_get_connection_handle(packet);
            for(i = 0; i<7; i++){
                if(handle_type[i].con_handle_value == x){
                    handle_type[i].con_handle_value = 0;
                    if(handle_type[i].state == CLIENT){
                        printf("\n\n%d\n\n",handle_type[i].state);
                        printf("fasalt client");
                        handle_type[i].state = 0;
                    }
                    else{
                        printf("fasalat server");
                        le_notification_enabled = 0;
                        handle_type[i].state = 0;
                    }
                }
            }
            //printf("my client state is %d\n",hci_event_disconnection_complete_get_connection_handle(packet));
            //gap_start_scan();
         break;
        case ATT_EVENT_CAN_SEND_NOW:
            att_server_notify(con_handler, ATT_CHARACTERISTIC_00000661_37E4_4E5D_9592_69327D128840_01_VALUE_HANDLE, (uint8_t*)&uISentValue, sizeof(uISentValue));
            break;
        default:
            break;
    }
    
}
static void handle_gatt_client_event(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
    UNUSED(packet_type);
    UNUSED(channel);
    UNUSED(size);
    uint16_t temp;

    switch(hci_event_packet_get_type(packet)){
        case GATT_EVENT_SERVICE_QUERY_RESULT:

            gatt_event_service_query_result_get_service(packet, &environmental_sensing);
        break;
        case GATT_EVENT_CHARACTERISTIC_QUERY_RESULT:

            if (client_event_query == QUERY_CHARACTERISTIC_TEMPERATURE) { 

                gatt_event_characteristic_query_result_get_characteristic(packet, &temperature);

            }
            if (client_event_query == QUERY_CHARACTERISTIC_HUMIDITY) { 

                gatt_event_characteristic_query_result_get_characteristic(packet, &humidity);

            }
        break;
        case GATT_EVENT_QUERY_COMPLETE:

            switch(client_event_query) {
                case QUERY_SERVICE:
                    client_event_query = QUERY_CHARACTERISTIC_TEMPERATURE;
                    gatt_client_discover_characteristics_for_service_by_uuid128(handle_gatt_client_event, connection_handler, 
                        &environmental_sensing, char_led_brightness_uuid128);                
                break;
                case QUERY_CHARACTERISTIC_HUMIDITY:
                    client_event_query = ENABLE_NOTIFICATION;
                    gatt_client_listen_for_characteristic_value_updates(&notification_listener_temp, handle_gatt_client_event, 
                        connection_handler, &temperature);
                    gatt_client_listen_for_characteristic_value_updates(&notification_listener_humi, handle_gatt_client_event, 
                       connection_handler, &humidity);
                    // enable notifications
                    gatt_client_write_client_characteristic_configuration(handle_gatt_client_event, connection_handler,
                        &temperature, GATT_CLIENT_CHARACTERISTICS_CONFIGURATION_NOTIFICATION);
                    //gatt_client_write_client_characteristic_configuration(handle_gatt_client_event, connection_handler,
                     //   &humidity, GATT_CLIENT_CHARACTERISTICS_CONFIGURATION_NOTIFICATION);

                break;
                case QUERY_CHARACTERISTIC_TEMPERATURE:
                    client_event_query = QUERY_CHARACTERISTIC_HUMIDITY;
                    gatt_client_discover_characteristics_for_service_by_uuid128(handle_gatt_client_event, connection_handler, 
                        &environmental_sensing,char_set_led_brightness_uuid128);
                break;
                case ENABLE_NOTIFICATION:
                client_event_query = ENABLE_COMPLETE;
                            
                break;
            }
            break;
            case GATT_EVENT_CHARACTERISTIC_VALUE_QUERY_RESULT:
                if (humidity.value_handle == gatt_event_characteristic_value_query_result_get_value_handle(packet)) { 
                    temp = little_endian_read_16(gatt_event_characteristic_value_query_result_get_value(packet), 0);
                    printf("humidity read:%.02f%c\n", temp, '%');
                }
                if (temperature.value_handle == gatt_event_characteristic_value_query_result_get_value_handle(packet)) { 
                    temp = little_endian_read_16(gatt_event_characteristic_value_query_result_get_value(packet), 0);
                    printf("temperature read:%.02f C\n", temp);
                }

                 
            break;
            case GATT_EVENT_NOTIFICATION:
                if (temperature.value_handle == gatt_event_notification_get_value_handle(packet)) { 
                            uIReceivedValue = little_endian_read_16(gatt_event_notification_get_value(packet), 0);
                    printf("\nRecieved value from first characteristic:%d\n", little_endian_read_16(gatt_event_notification_get_value(packet), 0));
                    xQueueSend(RxQueue, ( void * ) &uIReceivedValue, ( TickType_t ) 0);
                }

                if (humidity.value_handle == gatt_event_notification_get_value_handle(packet)) { 
                    printf("\nRecieved value from second characteristic:%d\n", little_endian_read_16(gatt_event_notification_get_value(packet), 0));
                }
            break;
        default:
            break;
    }
}

void server_task(void *pvParameters){  
    l2cap_init();

    sm_init();
    sm_set_io_capabilities(IO_CAPABILITY_NO_INPUT_NO_OUTPUT);

    att_server_init(profile_data, att_read_callback, att_write_callback);

    hci_add_event_handler(&hci_event_callback_registration);

    hci_event_callback_registration.callback = &handle_hci_event;
    hci_add_event_handler(&hci_event_callback_registration);

    gatt_client_init();
    // register for ATT event
    att_server_register_packet_handler(handle_hci_event);

    // set one-shot btstack timer
    heartbeat.process = &heartbeat_handler;
    btstack_run_loop_set_timer(&heartbeat, HEARTBEAT_PERIOD_MS);

    btstack_run_loop_add_timer(&heartbeat);

    
    // turn on bluetooth!
    hci_power_control(HCI_POWER_ON);

    vTaskDelete(NULL);
}

void network_task(void *pvParameters) {
    while (1) {
        if (uxQueueMessagesWaiting(TxQueue) != 0) {
            while (client_event_query != ENABLE_COMPLETE);
            do {
                //printf("ANA GOWA");
                xQueueReceive(TxQueue, &uISentValue, (TickType_t)10);
                gatt_client_write_value_of_characteristic(handle_gatt_client_event, connection_handler, temperature.value_handle, 2, (uint8_t*)&uISentValue);
            } while (uxQueueMessagesWaiting(TxQueue) != 0 && client_event_query == ENABLE_COMPLETE);
        }
        vTaskDelay(50); // Delay for a short time to avoid busy-waiting
    }
}



void BleServerClient_Init(){
TxQueue = xQueueCreate(10, sizeof(uint));    
RxQueue = xQueueCreate(10, sizeof(uint));
xTaskCreate(server_task, "server_task", 256, NULL, 1, &server_taskHandle);
xTaskCreate(network_task, "network_task",256, NULL, 1, NULL);
return;
}

