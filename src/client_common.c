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
static void handle_gatt_client_event(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);
static void sm_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);
static hci_con_handle_t con_handler;
int connection_type;
uint16_t temp_i, humi_i;
static int le_notification_enabled;
static uint16_t current_temp;
static btstack_timer_source_t heartbeat;
static TaskHandle_t server_taskHandle = NULL;
int i;
#define APP_AD_FLAGS 0x06

uint8_t service_uuid128[]={
	    0x00,0x00,0x06,0x60,0x37,0xE4,0x4E,0x5D,0x95,0x92,0x69,0x32,0x7D,0x12,0x88,0x40
};
uint8_t char_led_brightness_uuid128[]={
	    0x00,0x00,0x06,0x61,0x37,0xE4,0x4E,0x5D,0x95,0x92,0x69,0x32,0x7D,0x12,0x88,0x40
};
uint8_t char_set_led_brightness_uuid128[]={
	    0x00,0x00,0x06,0x62,0x37,0xE4,0x4E,0x5D,0x95,0x92,0x69,0x32,0x7D,0x12,0x88,0x40
};
	 

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
            bd_addr_t null_addr;
            memset(null_addr, 0, 6);
            // BTstack activated, get started
            gap_set_scan_parameters(0,0x0030, 0x0030);
            //gap_advertisements_enable(1);
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

    hci_add_event_handler(&hci_event_callback_registration);

    hci_event_callback_registration.callback = &handle_hci_event;
    hci_add_event_handler(&hci_event_callback_registration);

    gatt_client_init();
    // register for ATT event
    att_server_register_packet_handler(handle_hci_event);
    
    sm_event_callback_registration.callback = &sm_packet_handler;
	sm_add_event_handler(&sm_event_callback_registration);
	    
	// enable LE Secure Connections Only mode - disables Legacy pairing
	sm_set_secure_connections_only_mode(true);
	 
	// LE Secure Connections, Numeric Comparison
	sm_set_io_capabilities(IO_CAPABILITY_NO_INPUT_NO_OUTPUT);
	sm_set_authentication_requirements(SM_AUTHREQ_SECURE_CONNECTION|SM_AUTHREQ_MITM_PROTECTION |SM_AUTHREQ_BONDING);

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

        if(uxQueueMessagesWaiting(RxQueue) != 0){
            xQueueReceive(RxQueue, &uIReceivedValue, (TickType_t)10);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, uIReceivedValue);
        }while (uxQueueMessagesWaiting(RxQueue) != 0);

        vTaskDelay(51); // Delay for a short time to avoid busy-waiting
    }
}



void data_task(void *pvParameters){
uint uIValueToSend = 0;
while(1){
    while (client_event_query != ENABLE_COMPLETE);
    uIValueToSend = 1;
    xQueueSend(TxQueue, ( void * ) &uIValueToSend, ( TickType_t ) 0);
    //cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    vTaskDelay(1000);
    uIValueToSend = 0;
    xQueueSend(TxQueue, ( void * ) &uIValueToSend, ( TickType_t ) 0);
    //cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    vTaskDelay(1000);
    }}

void BleServerClient_Init(){
TxQueue = xQueueCreate(10, sizeof(uint));    
RxQueue = xQueueCreate(10, sizeof(uint));
xTaskCreate(server_task, "server_task", 256, NULL, 1, &server_taskHandle);
xTaskCreate(network_task, "network_task",256, NULL, 1, NULL);
xTaskCreate(data_task, "data_task",256, NULL, 1, NULL);
return;
}

