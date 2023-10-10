#define BLINKER_PRINT Serial
#define BLINKER_WIFI

#include <Blinker.h>
#include "SoftwareSerial.h"

SoftwareSerial mySerial(2,15);

/*******此处修改*******/
char auth[] = "4ae476906b86";//秘钥
char ssid[] = "LAPTOP-GKSAFFD4 7609";//WiFi名称
char pswd[] = "363488120...";//WiFi密码

// 新建组件对象
BlinkerButton Button1("key");
BlinkerNumber Number1("num-abc");

int counter = 0;
String str1 = "";
String strnum1 = "";
int num1;
bool com1 = false;

// 按下按键即会执行该函数
void button1_callback(const String & state)
{
  BLINKER_LOG("get button state: ", state);
  // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if (state=="on") {
    mySerial.print('1');
    digitalWrite(LED_BUILTIN, LOW);
    // 反馈开关状态
    Button1.print("on");
  } else if(state=="off"){
    mySerial.print('0');
    digitalWrite(LED_BUILTIN, HIGH);
    // 反馈开关状态
    Button1.print("off");
  }
}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
  BLINKER_LOG("Blinker readString: ", data);
  counter++;
  Number1.print(counter);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);
  mySerial.listen();

  #if defined(BLINKER_PRINT)
    BLINKER_DEBUG.stream(BLINKER_PRINT);
  #endif

  // 初始化有LED的IO
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // 初始化blinker
  Blinker.begin(auth, ssid, pswd);
  Blinker.attachData(dataRead);
  Button1.attach(button1_callback);//注册按键回调函数
}

void loop() {
  Blinker.run();
  if(com1){
    Serial.print("str1:");
    Serial.println(str1);
    Serial.print("num1:");
    Serial.println(num1);
    //清除数据
    str1 = "";
    strnum1 = "";
    num1 = 0;
    com1 = false;
  }
}

void serialEvent() {
  while (mySerial.available()) {
    char inchar = (char)mySerial.read();
    if(isDigit(inchar)){
      strnum1 += inchar; 
    }
    else if (inchar == '\n') {
      com1 = true;
      num1 = strnum1.toInt();
    }
    else {
      str1 += inchar;
    }
  }
}



