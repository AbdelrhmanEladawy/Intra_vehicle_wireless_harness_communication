#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "queue.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

static QueueHandle_t xQueue = NULL;

void led_task()
{       
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return;
    }
    while (true) {
        uint uIValueToSend = 0;
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        uIValueToSend = 1;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(500);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        uIValueToSend = 0;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(500);
    }
}

void usb_task(void *pvParameters){
    uint uIReceivedValue;

    while(1){
        xQueueReceive(xQueue, &uIReceivedValue, portMAX_DELAY);
        if (uIReceivedValue == 1){
            printf("The LED is ON! \n");
        }
        else{
            printf("The LED is OFF! \n");
        }
    }
}

int main()
{
    stdio_init_all();
    xQueue = xQueueCreate(1, sizeof(uint));

    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    xTaskCreate(usb_task, "USB_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1){};
}