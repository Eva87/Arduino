#include <Servo.h>

Servo servo_base;
Servo servo_muelle;
Servo servo_pelota;
Servo servo_lanza;
int posicionbase=0;
int preparado=0;
int boton_der=7;
int boton_izq=8;
int interruptor=12;
int boton_disparo=4;
const int ledpreparado=13;
int automatico=0;
int distancia_detectada=0;
int pintrigger=11;
int pinecho=3;

void setup() {
  Serial.begin(9600);
  servo_base.attach(5);
  servo_muelle.attach(6);
  servo_pelota.attach(9);
  servo_lanza.attach(10);
  //attachInterrupt(0, mover_derecha,LOW);
  //attachInterrupt(1, mover_izquierda,LOW);
  pinMode(ledpreparado,OUTPUT);
  pinMode(pinecho,INPUT);
  pinMode(pintrigger,OUTPUT);
}

void loop() {
   if(preparado==0){
     //preparar la catapulta
     preparado=prepararcatapulta(); 
    }
    
   if(digitalRead(interruptor)==LOW){
    //modo manual, con mando
    if(digitalRead(boton_der)==HIGH){
      posicionbase=moverderecha();
    }
    if(digitalRead(boton_izq)==HIGH){ 
      posicionbase=moverizquierda();
    }
    servo_base.write(posicionbase);
    delay(10);
    
    if(digitalRead(boton_disparo)==HIGH){
      //disparar la catapulta
      preparado=dispararcatapulta();
    }
   }
   else{
    //modo automatico
    if(automatico==0){
      moverizquierda();
    }
    else{
      moverderecha();
    }
    servo_base.write(posicionbase);
    distancia_detectada=leerUltrasonidos();
    if(distancia_detectada<=35 && distancia_detectada >=18){
      preparado=dispararcatapulta();
   }
   delay(50);
   }
}
 int prepararcatapulta(){
      servo_lanza.write(0);
      delay(500);
      servo_muelle.write(0);//bajar la catapulta
      delay(500);
      servo_lanza.write(90);
      delay(500);
      servo_pelota.write(45);
      delay(115);
      servo_pelota.write(0);
      delay(500);
      servo_muelle.write(180);//extender muelle
      delay(500);
      digitalWrite(ledpreparado,HIGH);
      delay(100);
      preparado=1;
      return preparado;
}
int dispararcatapulta(){
  servo_lanza.write(180);
      delay(500);
      digitalWrite(ledpreparado,LOW);
      delay(100);
      preparado=0;
      return preparado;
}
int moverizquierda(){
      posicionbase--;
      if(posicionbase<=0){
        posicionbase=0;
        automatico=1;
      }
      return posicionbase;
}
int moverderecha(){
      posicionbase++;
      if(posicionbase>=180){
        posicionbase=180;
        automatico=0;
      }
      return posicionbase;
}
int leerUltrasonidos(){
  digitalWrite(pintrigger,LOW);
  delayMicroseconds(2);
  digitalWrite(pintrigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(pintrigger,LOW);
  int tiempo=pulseIn(pinecho,HIGH);
  int distancia=tiempo/58;
  return distancia;
}
