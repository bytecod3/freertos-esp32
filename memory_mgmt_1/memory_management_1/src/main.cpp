/**
 * Free RTOS heap demo 
 * 
 * One task reads from serial, constructs a message buffer
 * and the second prints the message to serial 
 */

#include <Arduino.h>

static const uint8_t buf_len = 255;
static char * msg_pointer = NULL;
static volatile uint8_t msg_flag = 0;

/* read messages from serial buffer */
void read_serial_Task(void* parameters) {
  char c;
  char buf[buf_len];
  uint8_t idx = 0;

  while(1) {
    if(Serial.available() > 0) {
      c = Serial.read();

      // store received characters to buffer if not over buffer limit
      if(idx < buf_len - 1) {
        buf[idx] = c;
        idx++;
      }

      /* create a message buffer for print task */
      if(c == '\n') {
        buf[idx - 1] = '\0';      /* nul terminate */

        if(msg_flag == 0) {
          msg_pointer = (char*) pvPortMalloc(idx * sizeof(char));
          configASSERT(msg_pointer);  /* throw error if system out of memory */

          memcpy(msg_pointer, buf, idx);

          msg_flag = 1;
        }

        memset(buf, 0, buf_len);
        idx = 0;
        
      }
    }
  }
}


void print_msg_task(void* params) {
  while(1) {
    if (msg_flag == 1) {
      Serial.println(msg_pointer);

      uint32_t free_hp = xPortGetFreeHeapSize();
      float free_hp_kb = (float)free_hp / 1024.0; /* TODO: put den in const */
      Serial.printf("Free heap (bytes): %.2f ", free_hp_kb);

      uint32_t min_ev_hp = xPortGetMinimumEverFreeHeapSize();
      float min_ever_kb = (float)min_ev_hp / 1024.0;
      Serial.printf("Min ever free heap (bytes): %.2f ", min_ever_kb);

      vPortFree(msg_pointer); /* free the memory after using it*/
      msg_pointer = NULL;
      msg_flag = 0;
    }
  }
}

int led_pin = 2;
void blinkLED(void* pv_params) {
  /* copy number into a local variable */
  int num = *(int*) pv_params;

  Serial.print("Received: ");
  Serial.println(num);

  // configure LED pin 
  pinMode(led_pin, OUTPUT);

  // blink
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(num / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(num/ portTICK_PERIOD_MS);
  }

}

void setup() {
  Serial.begin(115200);

  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("-------- Heap analysis ----------");
  Serial.println("Enter a string");

  xTaskCreatePinnedToCore(
    read_serial_Task,
    "read serial",
    1024,
    NULL,
    1,
    NULL,
    0
  );

  xTaskCreatePinnedToCore(
    print_msg_task,
    "print message",
    2000,
    NULL,
    1, 
    NULL,
    0
  );
  
  vTaskDelete(NULL);
}

void loop() {
  
}

