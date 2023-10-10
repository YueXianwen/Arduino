#define BLINKER_WIFI

#include <Blinker.h>
#include "SoftwareSerial.h"

SoftwareSerial mySerial(4,5);

/*******此处修改*******/
char auth[] = "1cff54980023";//秘钥
char ssid[] = "LAPTOP-GKSAFFD4 7609";//WiFi名称
char pswd[] = "363488120...";//WiFi密码

/* 新建组件对象 */
BlinkerNumber Number1("temp");//数据_温度
BlinkerNumber Number2("humi");//数据_空气湿度
BlinkerNumber Number3("soil");//数据_土壤湿度
BlinkerNumber Number4("light");//数据_土壤湿度

BlinkerSlider Slider1("ra");//滑动条_风扇风速

BlinkerButton Button1("cool");//开关按键-风扇
BlinkerButton Button2("beep");//开关按键-报警
BlinkerButton Button3("led");//开关按键-补光灯
BlinkerButton Button4("water");//开关按键-水泵
BlinkerButton Button5("pw");//开关按键-待机

#define Rx_Buffer_Len      13
#define Tx_Buffer_Len      9         

int counter = 0;

int Real_time_data = 0;//定义数据实时传输
int temp = 0;
int humi = 0;
int soil = 0;
int light = 0;

/*串口收发数据结构体*/
struct USART_DataStruct{		
  int Data[20]; //接收数据存储区
  int RxBuf;     //接收缓冲区
  int Count;
  int Flag;
};

struct USART_DataStruct Rx_Buffer;
struct USART_DataStruct Tx_Buffer = {0x55,0xAA,0x00,0x00,0x00,0x00,0x00,0x00,0x66};

/* 滑动滑动条即会执行该函数 */
void slider1_callback(int32_t value)
{
  Tx_Buffer.Data[2] = value;
  Write_STM32_Data(Tx_Buffer_Len);//发送给STM32数据包
}

/* 按下按键1即会执行该函数 */
void button1_callback(const String & state)
{
  // BLINKER_LOG("get button1 state: ", state);
  if (state == BLINKER_CMD_ON) {
      Button1.print("on");
      Tx_Buffer.Data[3] = 1;
  }
  else if (state == BLINKER_CMD_OFF) {
      Button1.print("off");
      Tx_Buffer.Data[3] = 0;
  }
  Write_STM32_Data(Tx_Buffer_Len);//发送给STM32数据包
}
/* 按下按键2即会执行该函数 */
void button2_callback(const String & state)
{
  if (state == BLINKER_CMD_ON) {
    Button2.print("on");
    Tx_Buffer.Data[4] = 1;
  }
  else if (state == BLINKER_CMD_OFF) {
    Button2.print("off");
    Tx_Buffer.Data[4] = 0;
  }
  Write_STM32_Data(Tx_Buffer_Len);//发送给STM32数据包
}
/* 按下按键3即会执行该函数 */
void button3_callback(const String & state)
{
  if (state == BLINKER_CMD_ON) {
    Button3.print("on");
    Tx_Buffer.Data[5] = 1;
  }
  else if (state == BLINKER_CMD_OFF) {
    Button3.print("off");
    Tx_Buffer.Data[5] = 0;
  }
  Write_STM32_Data(Tx_Buffer_Len);//发送给STM32数据包
}
/* 按下按键4即会执行该函数 */
void button4_callback(const String & state)
{
  if (state == BLINKER_CMD_ON) {
    Button4.print("on");
    Tx_Buffer.Data[6] = 1;
  }
  else if (state == BLINKER_CMD_OFF) {
    Button4.print("off");
    Tx_Buffer.Data[6] = 0;
  }
  Write_STM32_Data(Tx_Buffer_Len);//发送给STM32数据包
}
/* 按下按键5即会执行该函数 */
void button5_callback(const String & state)
{
  if (state == "tap") {
    Tx_Buffer.Data[7] = 1;
  }
  Write_STM32_Data(Tx_Buffer_Len);//发送给STM32数据包
}

/* 如果未绑定的组件被触发，则会执行其中内容 */
void dataRead(const String & data)
{
  BLINKER_LOG("未绑定的组件被触发:", data);
}

/* 心跳包函数 */
void heartbeat() {
  /* 反馈的内容 */
  Number1.print(temp);
  Number2.print(humi);
  Number3.print(soil);
  Number4.print(light);
}

/* 接收STM32串口发送来的数据包 */
void Read_STM32_Data(void)       
{
  if(mySerial.available() > 0) // 如果缓冲区中有数据，则读取并输出
  {
    Rx_Buffer.Data[Rx_Buffer.Count] = mySerial.read();//读取传入或到达的数据字节
    Rx_Buffer.Count ++; //计数自增
    /*进行包头校验*/
    if(Rx_Buffer.Flag == 0)//置位接收开始标志
    {
      if(1 == Rx_Buffer.Count)
      {
        if(0xAA != Rx_Buffer.Data[0])//0xAA数据包头1
          Rx_Buffer.Count = 0;
      }
      else if(2 == Rx_Buffer.Count)
      {
        if(0xAA == Rx_Buffer.Data[1])//0xAA数据包头1
          Rx_Buffer.Count = 1;
        else if(0x55 != Rx_Buffer.Data[1])//0x55数据包头2
          Rx_Buffer.Count = 0;
      }
      else
      { /*进行包尾校验*/
        if(0x66 == Rx_Buffer.Data[Rx_Buffer_Len - 1])//0x66数据包尾
        {
          Rx_Buffer.Count = 0;//计数清零
          Rx_Buffer.Flag = 1;//置位接收完成标志          
        }
      }
    }         
  }
}

/* 发送ESP8266的数据包给STM32 */
void Write_STM32_Data(int Data_Len)
{
  for(int i = 0;i < Data_Len;i ++)
  {
    mySerial.write(Tx_Buffer.Data[i]);
  }  
}

void setup()
{
  // 初始化串口
  Serial.begin(115200);
  mySerial.begin(115200);
  mySerial.listen();
  BLINKER_DEBUG.stream(Serial);    
  // 初始化有LED的IO
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // 初始化blinker
  Blinker.begin(auth, ssid, pswd); 

  Blinker.attachData(dataRead); 
  Blinker.attachHeartbeat(heartbeat);  //注册一个心跳包

  /* 注册按键 */
  Button1.attach(button1_callback);
  Button2.attach(button2_callback);   
  Button3.attach(button3_callback);
  Button4.attach(button4_callback);
  Button5.attach(button5_callback);

  Slider1.attach(slider1_callback);//注册滑块控件
}

void loop() {
  Blinker.run();

  Read_STM32_Data(); 
  if(Rx_Buffer.Flag == 1)//接收完成标志
  {
    Rx_Buffer.Flag = 0;//接收完成标志清零
    /*获取接收到的数据包中的重要信息*/
    temp = Rx_Buffer.Data[2];//获取温度数据
    humi = Rx_Buffer.Data[3];//获取湿度数据
    soil = Rx_Buffer.Data[4];//获取土壤湿度数据
    light = Rx_Buffer.Data[5];//获取光照数据
    Number1.print(temp);
    Number2.print(humi);
    Number3.print(soil);
    Number4.print(light);
    //校验数据
    Slider1.print(Rx_Buffer.Data[6]);//注册滑块控件
    Button1.print(Rx_Buffer.Data[7]==0?"off":"on");
    Button2.print(Rx_Buffer.Data[8]==0?"off":"on");   
    Button3.print(Rx_Buffer.Data[9]==0?"off":"on");
    Button4.print(Rx_Buffer.Data[10]==0?"off":"on");

    for(int i = 0;i < Rx_Buffer_Len;i ++)Rx_Buffer.Data[i] = 0;//清空数组，这很重要
  } 
}
