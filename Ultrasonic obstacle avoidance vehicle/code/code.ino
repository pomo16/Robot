#define SERVO 3
#define IN1M 7
#define IN2M 6
#define IN3M 13
#define IN4M 12
#define PWMA 9
#define PWMB 10
#define STBY 8

const int encoder_L = 2;
boolean encoderALast = LOW;  // remembers the previous pin state
int encoderPos = 0;

const int TrigPin = 16; 
const int EchoPin = 17; 
float distance = 0;

float Read_distance();
void Go(int speed);
void Turn_left(int speed);
void Turn_right(int speed);
void Servopulse(int angle);
void Scan();

void setup()
{
  Serial.begin(9600); 
  pinMode(SERVO, OUTPUT);
  
  // TB6612FNGN驱动模块控制信号初始化
  pinMode(IN1M, OUTPUT);                         //控制电机1的方向，01为正转，10为反转
  pinMode(IN2M, OUTPUT);
  pinMode(IN3M, OUTPUT);                        //控制电机2的方向，01为正转，10为反转
  pinMode(IN4M, OUTPUT);
  pinMode(PWMA, OUTPUT);                        //左电机PWM
  pinMode(PWMB, OUTPUT);                        //右电机PWM
  pinMode(STBY, OUTPUT);                        //TB6612FNG使能

  //初始化电机驱动模块
  digitalWrite(IN1M, 0);
  digitalWrite(IN2M, 1);
  digitalWrite(IN3M, 1);
  digitalWrite(IN4M, 0);
  digitalWrite(STBY, 1);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);

  pinMode(encoder_L, INPUT);  //测速码盘输入
  digitalWrite(encoder_L, HIGH);

  pinMode(TrigPin, OUTPUT); 
  pinMode(EchoPin, INPUT); 
  
}


void loop()
{ 
  Servopulse(90);        
  while(Read_distance() > 35)
  {
    Go(100);
  }
  
  while(Read_distance() < 50)
  {
    Turn_right(75);
  }
  while(Read_distance() > 25)
  {
    Go(100);
  }
  
  while(Read_distance() < 50)
  {
    Turn_right(75);
  }
  while(1)
  {
    Scan();
  }
      
}

float Read_distance()
{
  float distance;
  digitalWrite(TrigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW); 
  distance = pulseIn(EchoPin, HIGH) / 58.00;
  Serial.print(distance); 
  Serial.print("cm"); 
  Serial.println(); 
  delay(10); 
  return distance;
}

void Go(int speed)
{
  digitalWrite(IN1M, 1);
  digitalWrite(IN2M, 0);
  digitalWrite(IN3M, 1);
  digitalWrite(IN4M, 0);
  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed); 
}

void Turn_left(int speed)
{
  digitalWrite(IN1M, 1);
  digitalWrite(IN2M, 0);
  digitalWrite(IN3M, 0);
  digitalWrite(IN4M, 1);
  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed); 
}

void Turn_right(int speed)
{
  digitalWrite(IN1M, 0);
  digitalWrite(IN2M, 1);
  digitalWrite(IN3M, 1);
  digitalWrite(IN4M, 0);
  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed); 
}
void Stop()
{
  digitalWrite(IN1M, 0);
  digitalWrite(IN2M, 0);
  digitalWrite(IN3M, 0);
  digitalWrite(IN4M, 0);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0); 
}


void Servopulse(int angle)
{
  int pulsewidth=(angle*11)+500;  //将角度转化为500-2480的脉宽值
  digitalWrite(SERVO,HIGH);    //将舵机接口电平至高
  delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
  digitalWrite(SERVO,LOW);     //将舵机接口电平至低
  delayMicroseconds(20000-pulsewidth);
}

void Scan()
{
  int pos = 0;
  for(pos = 0; pos <= 90; pos += 10) 
  {                                  
    Servopulse(pos);
    if(Read_distance()<22)
    {
        while(Read_distance()<27)
        {
          Turn_left(50);
        }
    }
    else
   {
      Go(50);
    }
   
    delay(5);                       
  } 
  for(pos = 90; pos<=180; pos+=10)   
  {                                
    Servopulse(pos);
    if(Read_distance()<18)
    {
        while(Read_distance()<23)
        {
          Turn_right(50);
        }
    }
    else
    {
      Go(50);
    }
    delay(5);                      
  }  
    for(pos = 180; pos>=90; pos-=10)   
  {                                
    Servopulse(pos);
    if(Read_distance()<18)
    {
        while(Read_distance()<23)
        {
          Turn_right(50);
        }
    }
    else
    {
      Go(50);
    }
    delay(5);                      
  }
    for(pos = 90; pos>=0; pos-=10)   
  {                                
    Servopulse(pos);
    if(Read_distance()<22)
    {
        while(Read_distance()<27)
        {
          Turn_left(50);
        }
    }
    else
    {
      Go(50);
    }
    delay(5);                      
  }    
}   
