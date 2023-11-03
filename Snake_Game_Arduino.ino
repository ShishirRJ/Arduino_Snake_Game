#include<LedControl.h>
#include<TM1637Display.h>

/* line 5-7 related to joystick */
#define VRx A1 
#define VRy A2
#define SW 2
/* line 9-11 related to 8x8 Matrix */
#define CS 6 // pwm
#define DIN 7
#define CLK_MAT 5 // pwm
/* line 13&14 related 7-segment 4 digit display with TM01637 IC driver */ 
#define DIO 11 // pwm
#define CLK_SEG 12
/* line 16 related Buzzer */
#define Buzzer 10 // pwm
 /* line 18 related to potentiometer */
#define Pot A0

LedControl mat=LedControl(DIN,CLK_MAT,CS,1);    //(dataPin,clockPin,csPin,numDevices)

TM1637Display display(CLK_SEG,DIO);             //(clockPin,DataI/OPin)

int x,y,i=0,snakeHeadX,snakeHeadY,tailX[64],tailY[64],snakeSize;
int foodX,foodY,score,highScore=0,gameOver,tens=0,ones=0;
int snakeSpeed, initSnakeSpeed;

void setup()
{
  initAllDevices();              //Line 74
  initSnakePosn();               //Line 38
  foodPosn();                   //Line 157
  Serial.begin(9600);           
  refresh();                    //Line 301
  display.showNumberDec(score);
}

void loop()
{
  checkGameOver();
  if(gameOver==1)
  {
    unrollSnake();            //Line 206
    delay(100);               
    displayGameOverScreen();  //Line 329
    checkHighScore();         //Line 238
    checkSwitch();            //Line 255
  }
  else
  {
    controlSnakeSpeed();      //Line 231
    readInput();              //Line 88
    manageSnakeOutOfBounds(); //Line 145
    manageEatenFood();        //Line 176
    incSnakeSpeed();          //Line 286
    manageCoord();            //Line 133
    Display();                //Line 124
  }
}


void initSnakePosn()
{
  snakeHeadX=3;
  snakeHeadY=3;
  tailX[0]=3;
  tailY[0]=3;
  tailX[1]=4;
  tailY[1]=3;
  score=0;
  snakeSize=2;
  gameOver=0;
}

void initAllDevices()
{
  mat.shutdown(0,false);      //Power saving is turned off
  mat.setIntensity(0,8);      //Intensity of Led Matrix 0-15
  mat.clearDisplay(0);        //Clear display of Led Matrix
   
  pinMode(VRx, INPUT);        //Taking input for X and y directions from Joystick 
  pinMode(VRy, INPUT);
  pinMode(SW, OUTPUT);
  digitalWrite(SW,HIGH);
  
  display.setBrightness(4);   //Clear display of 7-Segment Display
}

void readInput()
{
  x=analogRead(VRx);
  y=analogRead(VRy);

  if (tailX[1]==tailX[0]-1||tailX[1]==tailX[0]+1||tailX[1]==tailX[0]+7||tailX[1]==tailX[0]-7)
  {
    if(y>900)
    snakeHeadY--;
    else if(y<150)
    snakeHeadY++;
    else 
    {
      if(tailX[1]==tailX[0]-1||tailX[1]==tailX[0]+7)
      snakeHeadX++;
      else if (tailX[1]==tailX[0]+1||tailX[1]==tailX[0]-7)
      snakeHeadX--;
    }
  }
  else if (tailY[1]==tailY[0]-1||tailY[1]==tailY[0]+1||tailY[1]==tailY[0]+7||tailY[1]==tailY[0]-7)
  {
  if(x>900)
  snakeHeadX++;
  else if(x<150)
  snakeHeadX--;
    else 
    {
      if(tailY[1]==tailY[0]-1||tailY[1]==tailY[0]+7)
      snakeHeadY++;
      else if (tailY[1]==tailY[0]+1||tailY[1]==tailY[0]-7)
      snakeHeadY--;
    }
  }

}

void Display()
{
  mat.clearDisplay(0);
  mat.setLed(0,foodX,foodY,1);
  for(i=0;i<snakeSize;i++)
    mat.setLed(0,tailX[i],tailY[i],1);
  delay(snakeSpeed);
}

void manageCoord()
{
  for(i=snakeSize-1;i>0;i--)
  {
    tailX[i]=tailX[i-1];
    tailY[i]=tailY[i-1];
  }

  tailX[0]=snakeHeadX;
  tailY[0]=snakeHeadY;
}

void manageSnakeOutOfBounds()
{
  if(snakeHeadX > 7) 
    snakeHeadX = 0;
  else if(snakeHeadX < 0) 
    snakeHeadX = 7;
  if(snakeHeadY > 7)
    snakeHeadY = 0;
  else if(snakeHeadY < 0)
    snakeHeadY = 7;
}

void foodPosn()
{
int regeneratePosition;
  regeneratePosition=1;
  while(regeneratePosition==1)
  {
  foodX=rand()%8;
  foodY=rand()%8;
  regeneratePosition=0;
  if(snakeHeadX==foodX && snakeHeadY==foodY)
    regeneratePosition=1; 
  for(int i=0;i<snakeSize;i++)
   {
   if(tailX[i]==foodX && tailY[i]==foodY)
    regeneratePosition=1;
   }
  } 
}

void manageEatenFood()
{
  if (snakeHeadX==foodX && snakeHeadY==foodY)
  {
    foodEatenSong();
    score++;
    snakeSize++;
    display.showNumberDec(score);
    //Serial.print("Score=");
    //Serial.println(score);
    //Serial.print("Delay=");
    //Serial.println(snakeSpeed);
    foodPosn();
  }
}

void checkGameOver()
{
  for(i=1;i<snakeSize;i++)
  {
    if(tailX[i]==tailX[0]  && tailY[i]==tailY[0])
    {
    gameOver=1;
    break;
    }
  }
}

int songAmplifier1=1;

void unrollSnake()
{
  delay(750);
    for (i=snakeSize-1; i>0; i--)
    { 
      if(i==1){
         tone(Buzzer,5000, 500);
         
         break;
      }
      mat.setLed(0, tailX[i], tailY[i], 0);
      tone(Buzzer,songAmplifier1*1000, 200);
      delay(100);
      songAmplifier1++;
      if(songAmplifier1>5)
      songAmplifier1=1;
      tone(Buzzer,songAmplifier1*1000, 200);
      delay(100);
      songAmplifier1++;
      if(songAmplifier1>5)
      songAmplifier1=1;
    }
    mat.clearDisplay(0);
}

void controlSnakeSpeed()
{
  int potValue=analogRead(Pot);
  int level= map(potValue, 0, 1023, 1, 10);
  initSnakeSpeed= map(level, 1, 10, 600, 100);
}

void checkHighScore(){
  if(score>highScore){
  highScore=score;
  ones = highScore%10;
  tens = highScore/10;
  //Serial.print(tens );
  //Serial.println(ones);
  }
}

uint8_t HS[]=
{
 SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, //H
 SEG_A | SEG_C | SEG_D | SEG_F | SEG_G, //G
 0,
 0
};
void checkSwitch()
{
  while(digitalRead(SW)==1)
  {
    display.showNumberDec(score);
    delay(1000);
    display.clear();
    display.setSegments(HS);
    delay(500);
    display.showNumberDec(highScore,false,2,0);
    delay(1000);
    display.clear();
  }
  if(digitalRead(SW)==0)
  {
    setup();
  }
}

void foodEatenSong()
{
  tone(Buzzer,698,30);
  tone(Buzzer,740,30);
  tone(Buzzer,784,30);
  tone(Buzzer,784,30);
  tone(Buzzer,831,30);
  tone(Buzzer,880,60);
  tone(Buzzer,740,120);
  noTone(11);
 }
 
void incSnakeSpeed()
{
  if (score>15)
  snakeSpeed=initSnakeSpeed*0.6;
  else if (score>12)
  snakeSpeed=initSnakeSpeed*0.7;
  else if (score>8)
  snakeSpeed=initSnakeSpeed*0.8;
  else if (score>4)
  snakeSpeed=initSnakeSpeed*0.9;
  else
  snakeSpeed=initSnakeSpeed;
}

int songAmplifier2=15;
void refresh()
{
  int n,r,c;
  for(n=0;n<15;n++){
    tone(Buzzer,(n+1)*300,160);
   for(r=0;r<8;r++){
    for(c=0;c<8;c++){
     if(c+r==n)
     {
      mat.setLed(0,r,c,true);
      delay(20);
     }}}}
  noTone(Buzzer);
  delay(100);
     
  for(n=0;n<15;n++){
    tone(Buzzer,(songAmplifier2-n)*300,160);
   for(r=0;r<8;r++){
    for(c=0;c<8;c++){
     if(c+r==n)
     {
      mat.setLed(0,r,c,false);
      delay(20);
     }}}}
     noTone(Buzzer);
     delay(20);
}

void displayGameOverScreen()
{
  int n;
  byte g[]=
  {
    B00000000,
    B01111110,
    B11111111,
    B11000011,
    B11010011,
    B11110011,
    B01100010,
    B00000000,
    B11111100,
    B11111110,
    B00110011,
    B00110011,
    B11111110,
    B11111100,
    B00000000,
    B11111111,
    B11111110,
    B00001100,
    B00011000,
    B00011000,
    B00001100,
    B11111110,
    B11111111,
    B00000000,
    B11111111,
    B11111111,
    B11011011,
    B11011011,
    B11011011,
    B00000000,
    B00000000,
    B00111100,
    B01111110,
    B11000011,
    B11000011,
    B11000011,
    B01111110,
    B00111100,
    B00000000,
    B00011111,
    B00111110,
    B01100000,
    B11000000,
    B01100000,
    B00111110,
    B00011111,
    B00000000,
    B11111111,
    B11111111,
    B11011011,
    B11011011,
    B11011011,
    B00000000,
    B11111110,
    B11111111,
    B00110011,
    B01110011,
    B11011110,
    B10001100,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };
  
  n=sizeof(g)/sizeof(g[0]);
  for(i=0;i<n-7;i++)
  {
   for(int j=0;j<8;j++)
   mat.setRow(0,j,g[i+j]) ;
   delay(90);
  }
}
