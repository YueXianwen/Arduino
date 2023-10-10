#include <IRremoteESP8266.h>//调用ESP8266/ESP32的函数库
#include <IRrecv.h>//调用红外接收库
#include <IRutils.h>//红外实用程序库
const int IR_RX = D3;//设置红外接收管脚
IRrecv IRR(IR_RX);//定义一个红外接收头名称并设置管脚
decode_results results;//设置解码结果(解码类型)
byte zt;//状态反转变量
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);//设置LED_BUILTIN管脚为输出模式
  Serial.begin(115200);//打开串口波特率设置115200
  IRR.enableIRIn();  //启动红外接收器
  delay(50);//短延时让接收更稳定
}
void loop() {
  if (IRR.decode(&results)) {//判断红外解码结果
    serialPrintUint64(results.value, HEX);//串口输出接收到的红外值以16进制方式输出
    Serial.println("");//串口输出换行符
   switch(results.value){//判断变量中的值
          case 0xFFA25D: LED_BUILTINzt();break;//判断是否0xFFA25D是的话LED_BUILTIN状态反转一次，然后跳出Switch判断函数
          default : break;//默认跳出循环         
        }   
   IRR.resume();//红外接收下一个值
  }
  delay(100);//间隔100MS读取一次
}
void LED_BUILTINzt(){
  zt=!zt;//状态反转
  digitalWrite(LED_BUILTIN,zt);//LED_BUILTIN控制状态在亮灭切换
  }
