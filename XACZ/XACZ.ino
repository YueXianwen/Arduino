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
BlinkerText Text1("text-123");

int counter = 0;

// 按下按键即会执行该函数
void button1_callback(const String & state)
{
    BLINKER_LOG("get button state: ", state);
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    if (state=="on") {
        digitalWrite(LED_BUILTIN, LOW);
        // 反馈开关状态
        Button1.print("on");
    } else if(state=="off"){
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
    Text1.print("错误！！");
}

void setup() {
    // 初始化串口
    Serial.begin(115200);
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
}
