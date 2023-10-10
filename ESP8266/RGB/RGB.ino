#define R 5
#define G 4
#define B 2

int i;    //PWM的值
String inString = ""; //输入的字符串
boolean com = false;
char LED = ' '; //判断引脚

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(com){
    Serial.print(inString);
    if(LED == 'R'){
      analogWrite(R, i);
    }
    else if(LED == 'G'){
      analogWrite(G, i);
    }
    else if(LED == 'B'){
      analogWrite(B, i);
    }
    //接受完之后清除
    com = false;
    inString = "";
    LED = ' ';
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inchar = (char)Serial.read();
    if(isDigit(inchar)){
      inString += inchar; 
    }
    else if (inchar == '\n') {
      com = true;
      i = inString.toInt();
    }
    else {
      LED = inchar;
    }
  }
}












