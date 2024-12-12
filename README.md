# RTOSESP32
Example RTOS Dual Core ESP32
ESP32 có 2 lõi CPU: Core 0 và Core 1.
Core 0 thường dành cho WiFi stack và hệ điều hành.
Core 1 thường được sử dụng cho các task người dùng.

Một số lệnh:

*Bạn có thể kiểm tra dung lượng heap còn lại (RAM động) để tính kích thước stack tối đa có thể cấp phát:*
```bash
#include "esp_heap_caps.h"

void setup() {
    Serial.begin(115200);

    size_t freeHeap = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    Serial.printf("Free heap: %d bytes\n", freeHeap);

    size_t largestBlock = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
    Serial.printf("Largest free block: %d bytes\n", largestBlock);
}

void loop() {}
```

Free heap: Tổng số RAM còn lại mà bạn có thể dùng.

Largest free block: Kích thước lớn nhất bạn có thể cấp phát cho stack của một task (trong điều kiện tối ưu).

*Lưu ý quan trọng:*
Không nên cấp phát quá lớn cho một task:

Hãy cấp phát stack vừa đủ cho mỗi task. Nếu cần, sử dụng hàm uxTaskGetStackHighWaterMark() để theo dõi stack usage.
Phân phối hợp lý giữa các task:

Nếu bạn có nhiều task, hãy phân chia bộ nhớ hợp lý để không vượt quá RAM khả dụng.
Task watchdog và stack overflow:

Nếu cấp phát stack quá nhỏ, bạn có thể gặp lỗi stack overflow. Bật configCHECK_FOR_STACK_OVERFLOW để dễ dàng phát hiện.

Độ ưu tiên của task.
Task có độ ưu tiên cao hơn (giá trị lớn hơn) sẽ được CPU ưu tiên thực hiện trước.
configMAX_PRIORITIES (thường là 25) định nghĩa độ ưu tiên tối đa mà bạn có thể sử dụng.

*Hàm vTaskDelay() trong FreeRTOS được sử dụng để trì hoãn (delay) một task trong một khoảng thời gian cụ thể. Khi một task gọi vTaskDelay(), nó sẽ nhường CPU cho các task khác và chuyển sang trạng thái blocked trong khoảng thời gian đã định.*
```bash
void vTaskDelay( const TickType_t xTicksToDelay );
```
xTicksToDelay:
Số tick thời gian mà task sẽ bị trì hoãn.
Một "tick" là đơn vị thời gian do configTICK_RATE_HZ định nghĩa trong file cấu hình FreeRTOS (FreeRTOSConfig.h).
Ví dụ:
Nếu configTICK_RATE_HZ = 1000, một tick tương đương 1ms.
Nếu configTICK_RATE_HZ = 100, một tick tương đương 10ms.

```bash
void Task1(void *pvParameters) {
    for (;;) {
        printf("Task 1 is running\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay 1000ms
    }
}
```
vTaskDelay(1000 / portTICK_PERIOD_MS) sẽ trì hoãn task trong 1000ms (1 giây).
portTICK_PERIOD_MS là macro tính khoảng thời gian 1 tick bằng mili giây, thường là (1000 / configTICK_RATE_HZ).

*Tại sao không dùng delay mà dùng vTaskDelay?*
Khi bạn sử dụng delay(ms), CPU sẽ bận rộn chờ đợi (busy-wait) trong khoảng thời gian đó. Nó không thực hiện bất kỳ công việc nào khác ngoài việc đếm thời gian.
Điều này dẫn đến lãng phí tài nguyên, đặc biệt là trong hệ thống đa nhiệm như FreeRTOS, nơi các task khác có thể sử dụng CPU trong thời gian chờ.
```bash
void Task1() {
    for (;;) {
        printf("Task 1 is running\n");
        delay(1000); // CPU bị "đóng băng" trong 1 giây.
    }
}

```

vTaskDelay() giúp chia sẻ CPU
FreeRTOS là một hệ điều hành thời gian thực hỗ trợ đa nhiệm, vì vậy việc chia sẻ CPU giữa các task là rất quan trọng.
Khi gọi vTaskDelay(), task sẽ nhường CPU cho các task khác trong thời gian trì hoãn.

*Tóm lại*
delay(): Chặn toàn bộ hệ thống, không chia sẻ CPU.
vTaskDelay(): Nhường CPU, giúp các task khác hoạt động trong thời gian chờ, tận dụng hiệu quả tài nguyên trong hệ thống FreeRTOS.
Vì vậy, trong FreeRTOS, vTaskDelay() luôn là lựa chọn tốt hơn.

## 🚀 About Me
Hello 👋I am Vinh. I'm studying HCMC University of Technology and Education

**Major:** Electronics and Telecommunication

**Skill:** 

*- Microcontroller:* ESP32/8266 - ARDUINO - PIC - Raspberry Pi

*- Programming languages:* C/C++/HTML/CSS/PHP/SQL and
related Frameworks (Bootstrap)

*- Communication Protocols:* SPI, I2C, UART, CAN

*- Data Trasmissions:* HTTP, TCP/IP, MQTT
## Authors

- [@my_fb](https://www.facebook.com/vcao.vn)
- [@my_email](contact@vinhcaodatabase.com)





