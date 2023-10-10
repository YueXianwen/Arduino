#include <IRremoteESP8266.h>  //调用ESP8266/ESP32的函数库
#include <IRrecv.h>           //调用红外接收库
#include <IRutils.h>          //红外实用程序库
const int IR_RX = 0;          //设置红外接收管脚
IRrecv IRR(IR_RX);            //定义一个红外接收头名称并设置管脚
decode_results results;       //设置解码结果(解码类型)
void setup() {
  Serial.begin(115200);  //打开串口波特率设置115200
  IRR.enableIRIn();      //启动红外接收器
  delay(50);             //短延时让接收更稳定
}
void loop() {
  if (IRR.decode(&results)) {               //判断红外解码结果
    serialPrintUint64(results.value, HEX);  //串口输出接收到的红外值以16进制方式输出
    Serial.println("");                     //串口输出换行符
    IRR.resume();                           //红外接收下一个值
  }
  delay(100);  //间隔100MS读取一次
}
