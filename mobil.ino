// For Motor Driver L298N
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // TX,RX
int in1 = 8;  // IN1 
int in2 = 9; // IN2 
int in3 = 10;  // IN4 
int in4 = 11; // IN3 

int data=0;
int Speed=0;
boolean maju=true;
int kec[11]={1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,11000}; //array kecepatan

void setup(){
  mySerial.begin(9600); 
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
}

void motorOut(unsigned char lpwm, unsigned char rpwm, boolean arrow){

  if(arrow==false){
    digitalWrite(in1,HIGH);
    digitalWrite(in3,LOW);
    analogWrite(in2,11000-lpwm);
    analogWrite(in4,rpwm);
    }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in3,HIGH);
    analogWrite(in2,lpwm);
    analogWrite(in4,11000-rpwm);
    }
}

void loop(){
  
  /* Commands/Characters sent from APP Bluetooth RC Controller (ANDROID)
  Forward ->F
  Back  -> B
  Left  -> L
  Right -> R
  Forward Left  -> G
  Forward Righ  -> I
  BackLeft -> H
  Back Right  -> J
  Stop  -> S
  Speed 10  -> 1
  Speed 20  -> 2
  Speed 30  -> 3
  Speed 40  -> 4
  Speed 50  -> 5
  Speed 60  -> 6
  Speed 70  -> 7
  Speed 80  -> 8
  Speed 90  -> 9
  Speed 100 -> q
  Stop All  -> D */
  
  if(mySerial.available()>0){
    data=mySerial.read();
    Serial.println(data);
    
    //penyimpan data kecepatan
    if (data =='0') { Speed=0; }
    else if (data =='1') { Speed=1;}
    else if (data =='2') { Speed=2;}
    else if (data =='3') { Speed=3;}
    else if (data =='4') { Speed=4;}
    else if (data =='5') { Speed=5;}
    else if (data =='6') { Speed=6;}
    else if (data =='7') { Speed=7;}
    else if (data =='8') { Speed=8;}
    else if (data =='9') { Speed=9;}
    else if (data =='q') { Speed=10;}

    //pergerakan
    if (data=='S')
    {
      motorOut(0,0,false);
    } // S=Stop
    
    if (data=='F')
    {
      motorOut(kec[Speed],kec[Speed],true);
    } // F=Maju
    
    if (data=='G')
    {
      motorOut(kec[Speed],((kec[Speed])/2),true);
    } // I=Maju sambil belok kanan
    
    if (data=='I')
    {
      motorOut(((kec[Speed])/2),kec[Speed],true);
    } // G=Maju sambil belok kiri
    
    if (data=='L')
    {
      motorOut(kec[Speed],0,true);
    } // R=Belok kanan
    
    if (data=='R')
    {
      motorOut(0,kec[Speed],true);
    } // L=Belok kiri
    
    if (data=='B')
    {
      motorOut(kec[Speed],kec[Speed],false);
    } // B=Mundur
    
    if (data=='J')
    {
      motorOut(((kec[Speed])/2),kec[Speed],false);
    } // H=Mundur sambil belok kiri
    
    if (data=='H')
    {
      motorOut(kec[Speed],((kec[Speed])/2),false);
    } // J=Mundur sambil belok kanan
  }
}
