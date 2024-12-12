#include "esp_heap_caps.h" //library check bo nho
TaskHandle_t Task1;
TaskHandle_t Task2;

int myLed = 5;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize LED pin
  pinMode(myLed, OUTPUT);

  // Create two tasks, each assigned to a different core
  xTaskCreatePinnedToCore(
    Task1Code,     // Task function
    "Task 1",      // Name of the task
    2000,          // Stack size (in words, not bytes)
    NULL,          // Task input parameter
    2,             // Priority of the task (higher priority)
    &Task1,        // Task handle
    0);            // Core to run the task on (Core 0)

  xTaskCreatePinnedToCore(
    Task2Code,     // Task function
    "Task 2",      // Name of the task
    2000,          // Stack size (in words, not bytes)
    NULL,          // Task input parameter
    2,             // Priority of the task (higher priority)
    &Task2,        // Task handle
    1);            // Core to run the task on (Core 1)

  //#############----------------#############
  //Free heap: Tổng số RAM còn lại mà bạn có thể dùng.
  //Largest free block: Kích thước lớn nhất bạn có thể cấp phát cho stack của một task (trong điều kiện tối ưu).
  //Luu ý đặt sau chương trình task để xem bộ nhớ còn lại
  size_t freeHeap = heap_caps_get_free_size(MALLOC_CAP_8BIT);
  Serial.printf("Free heap: %d bytes\n", freeHeap);

  size_t largestBlock = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
  Serial.printf("Largest free block: %d bytes\n", largestBlock);
  //############----------------#############
}

void loop() {
  // Empty loop as tasks run independently
}

// Task 1: Blinks the LED (Runs on Core 0)
void Task1Code(void * pvParameters) {
  for (;;) {
    digitalWrite(myLed, HIGH);
    delay(500);
    digitalWrite(myLed, LOW);
    delay(500);
  }
}

// Task 2: Prints message to Serial Monitor (Runs on Core 1)
void Task2Code(void * pvParameters) {
  for (;;) {
    Serial.println("vinh cao");
    delay(1000);  // Delay between messages
  }
}