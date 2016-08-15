#include <Servo.h>
#include <Stepper.h>
#define STEPS 200

#define IN1  11
#define IN2  10
#define IN3  9
#define IN4  8

int steps_left=4095;
boolean Direction = true;
int Steps = 0;                       // Define el paso actual de la secuencia
boolean Change = true;

int Paso [ 8 ][ 4 ] =
   {  {1, 0, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 1},
      {0, 0, 0, 1},
      {1, 0, 0, 1}
   };


Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int angulo1 = 90;
int angulo2 = 90;
int angulo3 = 90;
int angulo4 = 90;
int salto =5;
int Eje_x = A1;
int Eje_y = A2;
int boton = 4, LED = 12 ;
unsigned long p;
unsigned long q;
unsigned long r;
unsigned long s;
int lastButtonState = 0;
int buttonState = 0;
int buttonPin = 2;
int buttonPushCounter = 0;

void setup() 
{
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
 
  pinMode(boton, INPUT_PULLUP);
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
   pinMode(IN2, OUTPUT);
   pinMode(IN3, OUTPUT);
   pinMode(IN4, OUTPUT);
   pinMode(buttonPin, INPUT);
}

void loop() 
{
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState){
 
  if (buttonState == HIGH)
  {
    buttonPushCounter++;
    Serial.println(buttonPushCounter);

  }
  delay(50);
  }

  lastButtonState = buttonState;

  if (buttonPushCounter %2 ==0) {
    Change = true;
  }
  else
  {
    Change = false;
  }
  
if (Change){
 p = analogRead(A3);
 q = analogRead(A4);
 r=500;
 s=500;
}
else {
 r = analogRead(A3);
 s = analogRead(A4);
 p=500;
 q=500;
}



if ( s<200)
{
  angulo1 = angulo1 - salto;
  servo3.write(angulo1);
}
else if (s>1000){
 angulo1 = angulo1 + salto;
 servo3.write(angulo1);
 }

if ( p<200)
{
  angulo1 = angulo1 - salto;
  servo1.write(angulo1);
}
else if (p>1000){
 angulo1 = angulo1 + salto;
 servo1.write(angulo1);
 }

 if ( q<200)
{
  angulo2 = angulo2 - salto;
  servo2.write(angulo2);
}
else if (q>1000)
{
 angulo2 = angulo2 + salto;
 servo2.write(angulo2);
 }

while(r<200)    //Hacia la izquierda
{

    steps_left--;
    Direction = true;
    stepper();
    r = analogRead(A3);
    delay(1);
}

while(r>1000)
{
    steps_left++;
    Direction = false;
    stepper();
    r = analogRead(A3);
    delay(1);
}

delay(50); 
}

void stepper()            //Avanza un paso
   {  digitalWrite( IN1, Paso[Steps][ 0] );
      digitalWrite( IN2, Paso[Steps][ 1] );
      digitalWrite( IN3, Paso[Steps][ 2] );
      digitalWrite( IN4, Paso[Steps][ 3] );

      SetDirection();
   }
      void SetDirection()
   {  
      if(Direction)
         Steps++;
      else
         Steps--;

      Steps = ( Steps + 8 ) % 8 ;
   }
   



