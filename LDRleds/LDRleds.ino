const int LDR = A0;
int verde = 3;
int amarillo = 5;
int rojo = 6;
int azul = 9;
int val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(verde, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(rojo, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(LDR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(LDR);
  if (val <= 5){ // Muy poca luz (ningún led encendido)
     digitalWrite(verde, HIGH);
     digitalWrite(amarillo, LOW); // apaga led verde
     digitalWrite(rojo, LOW); // apaga led amarillo
     digitalWrite(azul, LOW); // apaga led rojo
   } else if (val > 5 && val <= 40){ // Poca luz (led verde
   // encendido)
     digitalWrite(verde, HIGH);
     digitalWrite(amarillo, HIGH); // enciende led verde
     digitalWrite(rojo, LOW); // apaga led amarillo
     digitalWrite(azul, LOW); // apaga led rojo
   } else if (val > 40 && val < 80){ // Bastante luz (leds verde
   // y amarillo encendidos)
     digitalWrite(verde, LOW);
     digitalWrite(amarillo, HIGH); // enciende led verde
     digitalWrite(rojo, HIGH); // enciende led amarillo
     digitalWrite(azul, LOW); // apaga led rojo
   } else if (val > 80 && val < 120) { // Mucha luz (todos los leds encendidos)
     digitalWrite(verde, LOW);
     digitalWrite(amarillo, LOW); // enciende led verde
     digitalWrite(rojo, HIGH); // enciende led amarillo
     digitalWrite(azul, HIGH); // enciende led rojo
   } else {
     digitalWrite(verde, LOW);
     digitalWrite(amarillo, LOW); // enciende led verde
     digitalWrite(rojo, LOW  ); // enciende led amarillo
     digitalWrite(azul, HIGH); // enciende led rojo
   }
   Serial.println(val);
}
