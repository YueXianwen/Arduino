const int R = D1;//红色
const int G = D2;//绿色
const int B = D3;//蓝色

void setup() {
  Serial.begin(115200);//打开串口波特率设置成115200
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
}

void loop() {
     int Hong=random(0, 1024);//函数生成伪随机数0-255
     int Lv=random(0, 1024);//函数生成伪随机数0-255
     int Lan=random(0, 1024);//函数生成伪随机数0-255
     /*
     Hong = constrain(Hong, 0, 4096);//将接收到的数字限制在一个范围内
     Lv =constrain(Lv, 0, 4096);//将接收到的数字限制在一个范围内
     Lan =constrain(Lan, 0, 4096);//将接收到的数字限制在一个范围内
     */
     analogWrite(R,Hong);//将接收到的对应值送给PWM，控制对应LED的亮度
     analogWrite(G,Lv);////将接收到的对应值送给PWM，控制对应LED的亮度
     analogWrite(B,Lan);////将接收到的对应值送给PWM，控制对应LED的亮度
     // 串口输出数据，方面我们查看，随机生成的数字
      Serial.print(Hong);
      Serial.print(",");
      Serial.print(Lv);
      Serial.print(",");
      Serial.println(Lan);
      delay(200);//延时50毫秒
}
