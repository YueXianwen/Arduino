#define BLINKER_MIOT_OUTLET
#define BLINKER_PRINT Serial
#define BLINKER_WIFI

#include <Blinker.h>

#define Socket1 2

char auth[] = "71ead6eedfc4";/****秘钥****/
int count=0;
bool WIFI_Status = true;
int counter=0;

// 新建组件对象
BlinkerButton Button1("key");     //设置blinkerapp内数据键名
BlinkerNumber Number1("num-abc");

void smartConfig()//配网函数
{
  WiFi.mode(WIFI_STA);
  Serial.println("\r\nWait for Smartconfig...");
  WiFi.beginSmartConfig();//等待手机端发出的用户名与密码
  while (1)
  {
    Serial.print(".");
    digitalWrite(LED_BUILTIN, HIGH);  
    delay(1000);                      
    digitalWrite(LED_BUILTIN, LOW);    
    delay(1000);                      
    if (WiFi.smartConfigDone())//退出等待
    {
      Serial.println("SmartConfig Success");
      Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
      Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
      break;
    }
  }
}

void WIFI_Set()//自动链接
{
    Serial.println("\r\n正在连接:");
    Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
    Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
    while(WiFi.status()!=WL_CONNECTED)
    {
        if(WIFI_Status)
        {
            Serial.print(".");
            digitalWrite(LED_BUILTIN, HIGH);  
            delay(100);                       
            digitalWrite(LED_BUILTIN, LOW);    
            delay(100);                 
            count++;
            if(count>=100)
            {
                WIFI_Status = false;
                Serial.println("\nWiFi连接失败,请配网!!"); 
            }
        }
        else
        {
            smartConfig();  //微信智能配网
        }
     }  
    Serial.println("连接成功");  
    Serial.print("IP:");
    Serial.println(WiFi.localIP());
}

void WIFI_Again()//断网重连
{
    while(WiFi.status()!=WL_CONNECTED)
    {
      WIFI_Set();
    }
    digitalWrite(LED_BUILTIN, HIGH);
}

void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {
        digitalWrite(Socket1, HIGH);
        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_OFF) {
        digitalWrite(Socket1, LOW);
        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
}

// 按下按键即会执行该函数
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    digitalWrite(Socket1, !digitalRead(Socket1));
}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}

void setup() {
  // 初始化串口
  Serial.begin(115200);
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);

#if defined(BLINKER_PRINT)
  BLINKER_DEBUG.stream(BLINKER_PRINT);
#endif

  // 初始化有LED的IO
  pinMode(Socket1, OUTPUT);
  digitalWrite(Socket1, HIGH);
  // 初始化blinker
  Blinker.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());
  WIFI_Set();
  Blinker.attachData(dataRead);
  Button1.attach(button1_callback);//注册按键回调函数
  BlinkerMIOT.attachPowerState(miotPowerState);
  digitalWrite(LED_BUILTIN, HIGH);  
}

void loop() {
  Blinker.run();  
  WIFI_Again();
}
