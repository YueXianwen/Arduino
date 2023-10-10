#include <IRremoteESP8266.h>//调用ESP8266/ESP32的函数库
#include <IRsend.h>//调用红外发送库
IRsend irsend(D1);//设置红外发射管脚
const uint32_t YLJ = 0x1FE48B7;//需要发送红外的代码
void setup() {
  Serial.begin(115200);//打开串口波特率设置115200
  delay(1000);////延时让发送更稳定
  irsend.begin();//启动红外发送器
}
void loop() {
   irsend.sendNEC(YLJ);//发送红外值
   delay(2000);//间隔2秒发送一次
  }

 
