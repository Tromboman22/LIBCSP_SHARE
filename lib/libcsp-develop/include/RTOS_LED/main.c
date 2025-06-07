#include <atmel_start.h>
#include <stdbool.h>
#include "hal_gpio.h"
#include "hal_delay.h"
#include "timers.h"

// Setup LED Pins
#define LED0 GPIO(GPIO_PORTA, 23)

// Setup Event Bits
#define LED_ON_BIT (EventBits_t)(1<<0) // LED ON
#define LED_OFF_BIT (EventBits_t)(1<<1) // LED OFF

/* Setup Handles */
xTaskHandle control_task_id;
xTaskHandle turn_on_led_id, turn_off_led_id;
EventGroupHandle_t eventGroup; // Event Group Handle

// Debug variable
bool led_state = true;

/* Function Prototypes */
void initializePin();
void controlTask(void *pvParameter);
void turnOnLED(void *pvParameter);
void turnOffLED(void *pvParameter);



int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	initializePin();
	
	/* Replace with your application code */
	controlTask(NULL);
}

void initializePin(void) {
	gpio_set_pin_direction(LED0,GPIO_DIRECTION_OUT);
	gpio_set_pin_pull_mode(LED0,GPIO_PULL_UP);
}

void controlTask(void *pvParameter){	
	// Initialize Event Group
	eventGroup = xEventGroupCreate();  // Create event group
	if (eventGroup == NULL) {
		// Handle error if event group creation fails
		return;
	}
	
	// Initialize the event bits
	xEventGroupSetBits(eventGroup, LED_OFF_BIT);
	
	// Initialize All tasks
	if (xTaskCreate(turnOnLED, "Turn On LED", configMINIMAL_STACK_SIZE, NULL, 2, &turn_on_led_id) != pdPASS) {
		// Handle task creation failure
	}
	if (xTaskCreate(turnOffLED, "Turn Off LED", configMINIMAL_STACK_SIZE, NULL, 1, &turn_off_led_id) != pdPASS) {
		// Handle task creation failure
	}
	
	// Start the scheduler
	vTaskStartScheduler();
}

void turnOnLED(void *pvParameter){
	while(true){
		xEventGroupWaitBits(eventGroup, LED_OFF_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
		gpio_set_pin_level(LED0, false);
		vTaskDelay(pdMS_TO_TICKS(1000)); // Wait 1s
		xEventGroupClearBits(eventGroup, LED_OFF_BIT);
		xEventGroupSetBits(eventGroup, LED_ON_BIT);
	}
}

void turnOffLED(void *pvParameter){
	while(true){
		xEventGroupWaitBits(eventGroup, LED_ON_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
		gpio_set_pin_level(LED0, true);
		vTaskDelay(pdMS_TO_TICKS(1000)); // Wait 1s
		xEventGroupClearBits(eventGroup, LED_ON_BIT);
		xEventGroupSetBits(eventGroup, LED_OFF_BIT);
	}
}
