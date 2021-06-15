int leds[] = {3, 4, 5, 6};
int valor_boton = 0;
int cociente, resto;
int contador = 0;
int j;
long T0 = 0;

void setup() {
  int i = 0;
  for(i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
  //pinMode(boton, INPUT);
  attachInterrupt(0, servicioBoton, RISING); 
}

void loop() {
  if(valor_boton == 1) {
    contador = (contador + 1) % 16;
    if(contador == 0) {
      for(j = 0; j < 4; j++) {
        digitalWrite(leds[j], LOW);
      }
    } else if(contador == 1) {
      digitalWrite(leds[0], HIGH);
      for(j = 1; j < 4; j++) {
        digitalWrite(leds[j], LOW);
      }
    } else {
      imprimirBinario(contador, 0);
    }
    valor_boton = 0;
  }
}

void imprimirBinario(int num, int i) {
   int aux; 
   if(num == 0) {
    int v;
    for(v = i; v < 4; v++) {
      digitalWrite(leds[v], LOW);
    }
    return;
   }
   aux=num%2; 
   num=num/2;
   imprimirBinario(num, i + 1);
   if(aux == 1) {
    digitalWrite(leds[i], HIGH);
   } else {
    digitalWrite(leds[i], LOW);
   }
}

void servicioBoton() {
  if(millis() > T0 + 250) {
    valor_boton = 1;
    T0 = millis();
  }
}
