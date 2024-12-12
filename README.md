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





