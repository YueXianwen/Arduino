#include <RCSwitch.h>//调用RC开关函数库
RCSwitch mySwitch = RCSwitch();//增加一个RC开关并设置名称
const int FRT=D1;//设置433MHz无线模块的发送管脚
const int key1=D5;//定义GPIO4接口
const int key2=D6;//定义GPIO4接口
byte kx1=0;//定义变量用于存放按键状态值
byte kx2=0;//定义变量用于存放按键状态值
const unsigned long  AKEY=5592320;//遥控器的A值
const unsigned long  BKEY=5592323;//遥控器的B值
void setup() {
  Serial.begin(115200);//打开串口设置波特率115200
  mySwitch.enableTransmit(FRT);//设置启用发送并设置接收管脚  
  pinMode(key1, INPUT);//设置GPIO2为输入模式
  pinMode(key2, INPUT);//设置GPIO2为输入模式
}
void loop() {
  kx1 = digitalRead(key1);//读取GPIO4接口的状态并送个变量kx
  kx2 = digitalRead(key2);//读取GPIO4接口的状态并送个变量kx
  if(kx1==0){//判断按键是否按下0代表已经按下
    mySwitch.send(AKEY, 24);//发送24位遥控器A值
    // delay(50);//延时500毫秒
  }
  if(kx2==0){//判断按键是否按下0代表已经按下
    mySwitch.send(BKEY, 24);//发送24位遥控器B值
    // delay(500);//延时500毫秒
  }
}
