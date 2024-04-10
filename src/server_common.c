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
#include "inttypes.h"

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
static btstack_packet_callback_registration_t sm_event_callback_registration;
static TaskHandle_t client_taskHandle = NULL;
static void handle_hci_event(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);
static void sm_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);
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
	 

uint8_t adv_data[] = {
	    // Flags: 0x02: General Discoverable Mode, 0x04:BR/EDR Not Supported
	    0x02, BLUETOOTH_DATA_TYPE_FLAGS, 0x06,
	    // Local Name
	    0x09, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME, 'P', 'i', 'c', 'o', 'W', '-', 'H','1', 
	    0x11, BLUETOOTH_DATA_TYPE_COMPLETE_LIST_OF_128_BIT_SERVICE_CLASS_UUIDS,
	    0x40, 0x88,0x12,0x7D,0x32,0x69,0x92,0x95, 0x5D,0x4E, 0xE4,0x37,0x50, 0x06,0x00, 0x00,
	};

static const uint8_t adv_data_len = sizeof(adv_data);

static uint16_t att_read_callback(hci_con_handle_t connection_handle, uint16_t att_handle, uint16_t offset, uint8_t * buffer, uint16_t buffer_size){
   
    if (att_handle == ATT_CHARACTERISTIC_00000651_37E4_4E5D_9592_69327D128840_01_VALUE_HANDLE){      
            att_server_request_can_send_now_event(connection_handle);
            return att_read_callback_handle_little_endian_16(temp_i, offset, buffer, buffer_size);

    }
    if (att_handle == ATT_CHARACTERISTIC_00000652_37E4_4E5D_9592_69327D128840_01_VALUE_HANDLE){          
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
    
    if (att_handle == ATT_CHARACTERISTIC_00000651_37E4_4E5D_9592_69327D128840_01_CLIENT_CONFIGURATION_HANDLE
        || att_handle == ATT_CHARACTERISTIC_00000652_37E4_4E5D_9592_69327D128840_01_CLIENT_CONFIGURATION_HANDLE) {
            le_notification_enabled = little_endian_read_16(buffer, 0) == GATT_CLIENT_CHARACTERISTICS_CONFIGURATION_NOTIFICATION;
            con_handler = connection_handle;
        }

        
    if (att_handle == ATT_CHARACTERISTIC_00000651_37E4_4E5D_9592_69327D128840_01_VALUE_HANDLE) {
	        led_brightness_scale = little_endian_read_16(buffer, 0);
            //cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_brightness_scale);
            xQueueSend(RxQueue, ( void * ) &led_brightness_scale, ( TickType_t ) 0);
	        printf("led_brightness_scale:%d\n", led_brightness_scale);
}
    return 0;
}
static void heartbeat_handler(struct btstack_timer_source *ts) {
    if (le_notification_enabled && (uxQueueMessagesWaiting(TxQueue) != 0)) {
        xQueueReceive(TxQueue, &uISentValue, (TickType_t)10);
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
                    printf("my client state is %d\n",connection_handler);
                    break; // Exit the loop once the value is added
        }}}
            else{
            con_handler = hci_subevent_le_connection_complete_get_connection_handle(packet);
            for (i = 0; i < 7; i++) {
                if (handle_type[i].con_handle_value == 0) {
                     // Add the value to the first zero element found
                    handle_type[i].con_handle_value = con_handler;
                    handle_type[i].state = SERVER;
                    break; // Exit the loop once the value is added
        }}

            sm_request_pairing(con_handler);
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
            att_server_notify(con_handler, ATT_CHARACTERISTIC_00000651_37E4_4E5D_9592_69327D128840_01_VALUE_HANDLE, (uint8_t*)&uISentValue, sizeof(uISentValue));
            break;
        default:
            break;
    }
    
}

	 
static void sm_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
	    UNUSED(channel);
	    UNUSED(size);
	 
	    if (packet_type != HCI_EVENT_PACKET) return;
	    bd_addr_t addr;
	    bd_addr_type_t addr_type;
	 
	    switch (hci_event_packet_get_type(packet)) {
	        case SM_EVENT_JUST_WORKS_REQUEST:
	            printf("Just works requested\n");
	            sm_just_works_confirm(sm_event_just_works_request_get_handle(packet));
	            break;
	        case SM_EVENT_NUMERIC_COMPARISON_REQUEST:
	            printf("Confirming numeric comparison: %"PRIu32"\n", sm_event_numeric_comparison_request_get_passkey(packet));
	            sm_numeric_comparison_confirm(sm_event_passkey_display_number_get_handle(packet));
	            break;
	        case SM_EVENT_PASSKEY_DISPLAY_NUMBER:
	            printf("Display Passkey: %"PRIu32"\n", sm_event_passkey_display_number_get_passkey(packet));
	            break;
	        case SM_EVENT_PASSKEY_INPUT_NUMBER:
	            printf("Passkey Input requested\n");
	            uint32_t passkey;
	            passkey = 123456;
	            printf("Sending fixed passkey %"PRIu32"\n", passkey);
	            sm_passkey_input(sm_event_passkey_input_number_get_handle(packet), passkey);
	            break;
	        case SM_EVENT_PAIRING_STARTED:
	            printf("Pairing started\n");
	            break;
	        case SM_EVENT_PAIRING_COMPLETE:
	            switch (sm_event_pairing_complete_get_status(packet)){
	                case ERROR_CODE_SUCCESS:
	                    printf("Pairing complete, success\n");
	                    break;
	                case ERROR_CODE_CONNECTION_TIMEOUT:
	                    printf("Pairing failed, timeout\n");
	                    break;
	                case ERROR_CODE_REMOTE_USER_TERMINATED_CONNECTION:
	                    printf("Pairing failed, disconnected\n");
	                    break;
	                case ERROR_CODE_AUTHENTICATION_FAILURE:
	                    printf("Pairing failed, authentication failure with reason = %u\n", sm_event_pairing_complete_get_reason(packet));
	                    break;
	                default:
	                    break;
	            }
	            break;
	        case SM_EVENT_REENCRYPTION_STARTED:
	            sm_event_reencryption_complete_get_address(packet, addr);
	            printf("Bonding information exists for addr type %u, identity addr %s -> start re-encryption\n",
	                   sm_event_reencryption_started_get_addr_type(packet), bd_addr_to_str(addr));
	            break;
	        case SM_EVENT_REENCRYPTION_COMPLETE:
	            switch (sm_event_reencryption_complete_get_status(packet)){
	                case ERROR_CODE_SUCCESS:
	                    printf("Re-encryption complete, success\n");
	                    break;
	                case ERROR_CODE_CONNECTION_TIMEOUT:
	                    printf("Re-encryption failed, timeout\n");
	                    break;
	                case ERROR_CODE_REMOTE_USER_TERMINATED_CONNECTION:
	                    printf("Re-encryption failed, disconnected\n");
	                    sm_event_reencryption_complete_get_address(packet, addr);
	                    addr_type = sm_event_reencryption_started_get_addr_type(packet);
	                    gap_delete_bonding(addr_type, addr);
	                    sm_request_pairing(sm_event_reencryption_complete_get_handle(packet));
	                    break;
	                case ERROR_CODE_PIN_OR_KEY_MISSING:
	                    printf("Re-encryption failed, bonding information missing\n\n");
	                    printf("Assuming remote lost bonding information\n");
	                    printf("Deleting local bonding information and start new pairing...\n");
	                    sm_event_reencryption_complete_get_address(packet, addr);
	                    addr_type = sm_event_reencryption_started_get_addr_type(packet);
	                    gap_delete_bonding(addr_type, addr);
	                    sm_request_pairing(sm_event_reencryption_complete_get_handle(packet));
	                    break;
	                default:
	                    break;
	            }
	            break;
	        default:
	            break;
	    }
	}
	 

void server_task(void *pvParameters){  
    l2cap_init();

    sm_init();

    att_server_init(profile_data, att_read_callback, att_write_callback);

    hci_add_event_handler(&hci_event_callback_registration);

    hci_event_callback_registration.callback = &handle_hci_event;
    hci_add_event_handler(&hci_event_callback_registration);

    // register for ATT event
    att_server_register_packet_handler(handle_hci_event);

    // set one-shot btstack timer
    heartbeat.process = &heartbeat_handler;
    btstack_run_loop_set_timer(&heartbeat, HEARTBEAT_PERIOD_MS);

    btstack_run_loop_add_timer(&heartbeat);

    sm_event_callback_registration.callback = &sm_packet_handler;
	sm_add_event_handler(&sm_event_callback_registration);
	 
	// enable LE Secure Connections Only mode - disables Legacy pairing
	sm_set_secure_connections_only_mode(true);
    sm_set_io_capabilities(IO_CAPABILITY_NO_INPUT_NO_OUTPUT);
	sm_set_authentication_requirements(SM_AUTHREQ_SECURE_CONNECTION|SM_AUTHREQ_MITM_PROTECTION |SM_AUTHREQ_BONDING);
	 
    // turn on bluetooth!
    hci_power_control(HCI_POWER_ON);

    vTaskDelete(NULL);
}

void network_task(void *pvParameters) {
    while (1) {
        if (uxQueueMessagesWaiting(RxQueue) != 0) {
            do {
                //printf("ANA GOWA");
                xQueueReceive(RxQueue, &uIReceivedValue, (TickType_t)10);
                cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, uIReceivedValue);
            } while (uxQueueMessagesWaiting(RxQueue) != 0);
        }

        else{
        }

        vTaskDelay(51); // Delay for a short time to avoid busy-waiting
    }
}

void data_task(void *pvParameters){
uint uIValueToSend = 0;
while(1){
    if(handle_type[0].state = SERVER){
    uIValueToSend = 1;
    xQueueSend(TxQueue, ( void * ) &uIValueToSend, ( TickType_t ) 0);
    //cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    vTaskDelay(1000);
    uIValueToSend = 0;
    xQueueSend(TxQueue, ( void * ) &uIValueToSend, ( TickType_t ) 0);
    //cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    vTaskDelay(1000);
    }}}

void BleServerClient_Init(){
TxQueue = xQueueCreate(10, sizeof(uint));    
RxQueue = xQueueCreate(10, sizeof(uint));
xTaskCreate(server_task, "server_task", 256, NULL, 1, &server_taskHandle);
xTaskCreate(network_task, "network_task",256, NULL, 1, NULL);
xTaskCreate(data_task, "data_task",256, NULL, 1, NULL);
return;
}

