#define BLINKER_PRINT Serial
#define BLINKER_WIFI
 
#include <Blinker.h>
 
/*******此处修改*******/
char auth[] = "4ae476906b86";//秘钥
char ssid[] = "LAPTOP-GKSAFFD4 7609";//WiFi名称
char pswd[] = "363488120...";//WiFi密码

// 新建组件对象
BlinkerButton Button1("key");
BlinkerNumber Number1("num-abc");
BlinkerNumber HUMI("humi"); //对应blinkerapp上的数据名
BlinkerNumber TEMP("temp"); //在blinkerapp下有温度数据名为

#include <DHT.h>
 
#define DHTPIN 2

#define DHTTYPE DHT11   // DHT 11
 
DHT dht(DHTPIN, DHTTYPE);
 
uint32_t read_time = 0;
 
float humi_read, temp_read;
int counter = 0;
 
//发送数据到app
void heartbeat()
{
    HUMI.print(humi_read);        //给blinkerapp湿度数据
    TEMP.print(temp_read);        //给blinkerapp温度数据
}

// 按下按键即会执行该函数
void button1_callback(const String & state)
{
    if (state=="on") {
        Serial.print("on");
        // 反馈开关状态
        Button1.print("on");
    } else if(state=="off"){
        Serial.print("off");
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
 
void setup()
{
    Serial.begin(115200);
    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif
 
    // 初始化有LED的IO
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
 
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    Blinker.attachHeartbeat(heartbeat);//将传感器回调函数加载，回传数据
    Button1.attach(button1_callback);//注册按键回调函数
    
    dht.begin();
}
 
void loop()
{
    Blinker.run();
 
    if (read_time == 0 || (millis() - read_time) >= 2000)
    {
        read_time = millis();
 
        float h = dht.readHumidity();//读取DHT11传感器的湿度 并赋值给h
        float t = dht.readTemperature();        
 
        if (isnan(h) || isnan(t)) {
            BLINKER_LOG("Failed to read from DHT sensor!");
            return;
        }
        else
        {
          humi_read = h;//将读取到的湿度赋值给全局变量humi_read
          temp_read = t;//将读取到的温度赋值给全局变量temp_read
        }
    }
}