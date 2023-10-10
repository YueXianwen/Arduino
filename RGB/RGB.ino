/*
*Blinker控制RGB三色灯程序
*小功率三色灯珠共阴极接GND, 阳极极经限流电阻接IO口；IO口状态为高时，灯亮。
*根据LED共阴共阳，自己调整程序。
*大功率LED可以根据功率选择相应的放大器，如MOS管
*硬件ESP8266
*/
 
#define BLINKER_WIFI     
#define BLINKER_ESP_SMARTCONFIG //定义EspTouch/SmartConfig模式进行配网，也可以微信扫码配网
 
#include <Blinker.h>
 
//重定义引脚
#define PIN_RLED D1
#define PIN_GLED D2
#define PIN_BLED D3
 
char auth[] = "4ae476906b86";        //设备密钥
//代码配网用这段
//char ssid[] = "WIFI SSID";        //自己wifi名称
//char pswd[] = "WIFI PSWD";        //自己wifi密码
 
// 新建组件对象
BlinkerSlider SliderR("Rval"); //红灯亮度滑条
BlinkerSlider SliderG("Gval"); //绿灯亮度滑条
BlinkerSlider SliderB("Bval"); //蓝灯亮度滑条
 
 
//红色输出
void sliderR_callback(int32_t value)    //滑条回调函数，滑条值范围0~1023，在APP中范围设为0~1023
{
  if(value<20)                          //如果滑条值小于20（0~20关灯)，输出低电平
  {
    analogWrite(PIN_RLED,LOW);          //输出低电平
  }
  else                                  //滑条值≥20，
  {
    analogWrite(PIN_RLED,value);  
    BLINKER_LOG("get slider value: ", value);  //在APP端调试窗口输出led亮度值
  }
}
 
//绿色输出
void sliderG_callback(int32_t value)    //滑条回调函数，滑条值范围0~1023
{
  if(value<20)                          //如果滑条值小于20（0~20关灯)，输出低电平
  {
    analogWrite(PIN_GLED,LOW);          //输出低电平
  }
  else                                  //滑条值≥20，
  {
    analogWrite(PIN_GLED,value);  
    BLINKER_LOG("get slider value: ", value);  //在APP端调试窗口输出led亮度值
  }
}
 
void sliderB_callback(int32_t value)    //滑条回调函数，滑条值范围0~1023
{
  if(value<20)                          //如果滑条值小于20（0~20关灯)，输出低电平
  {
    analogWrite(PIN_BLED,LOW);          //输出低电平
  }
  else                                  //滑条值≥20，
  {
    analogWrite(PIN_BLED,value);  
    BLINKER_LOG("get slider value: ", value);  //在APP端调试窗口输出led亮度值
  }
}
 
 
void setup()
{
    // 初始化串口
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    BLINKER_DEBUG.debugAll();  //打开全部调试信息
 
    // 初始化有LED的IO
    pinMode(PIN_RLED, OUTPUT);
    pinMode(PIN_GLED, OUTPUT);
    pinMode(PIN_BLED, OUTPUT);
    digitalWrite(PIN_RLED, LOW);
    digitalWrite(PIN_GLED, LOW);
    digitalWrite(PIN_BLED, LOW);
 
    // 初始化blinker
    // Blinker.begin(auth, ssid, pswd);  
    Blinker.begin(auth);     //SMARTCONFIG配网函数
    //注册回调函数
    SliderR.attach(sliderR_callback);
    SliderG.attach(sliderG_callback);
    SliderB.attach(sliderB_callback);   
}
 
void loop() {
    Blinker.run();
}

