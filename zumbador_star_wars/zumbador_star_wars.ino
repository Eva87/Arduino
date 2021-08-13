#define c3 7634
#define d3 6803
#define f3 5714
#define g3 5102
#define a3 4545
#define b3 4049
#define c4 3816 //261 Hz
#define d4 3401 //294 Hz
#define e4 3030 //329 Hz
#define f4 2865 //349 Hz
#define g4 2551 //392 Hz
#define a4 2272 //440 Hz
#define a4s 2146
#define b4 2028 //493 Hz
#define c5 1912 //523 HZ
#define d5 1706
#define d5s 1608
#define e5 1517 //659 Hz
#define f5 1433 //698 Hz
#define g5 1276
#define a5 1136
#define a5s 1073
#define b5 1012
#define c6 955

#define R 0 //Define una nota especial, 'R', representa rest

// 1: Marcha imperial sw

int melodia1[]={a4,R,a4,R,a4,R,f4,R,c5,R,a4,R,f4,R,c5,R,a4,R,e5,R,e5,R,e5,R,f5,R,c5,R,a4,R,f4,R,c5,R,a4,R};
int ritmo1[]={50,20,50,20,50,20,40,5,20,5,60,10,40,5,20,5,60,80,50,20,50,20,50,20,40,5,20,5,60,10,40,5,20,5,60,40};

int MAX_COUNT =sizeof(melodia1)/2;
long tempo=10000;
int pause =1000;
int rest_count=50;
int toneM=0;
int beat=0;
long duration=0;
int potVal=0;
int speakerOut=9;
int led=6;

void setup() {
  pinMode(speakerOut,OUTPUT);

  pinMode(led,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  //Melodia 1
  for (int i=0;i<MAX_COUNT;i++){
    toneM=melodia1[i];
    beat=ritmo1[i];
    duration=beat*tempo;
    playTone();
    delayMicroseconds(pause);
  }
}
void playTone(){
  long elapsed_time=0;
  if (toneM>0){
    digitalWrite(led,HIGH);
    while(elapsed_time<duration) {
      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(toneM/2);
      digitalWrite(speakerOut,LOW);
      delayMicroseconds(toneM/2);
      elapsed_time+=(toneM);
    }
    digitalWrite(led,LOW);
  }
  else{
    for (int j=0;j<rest_count;j++){
      delayMicroseconds(duration);
    }
  }
}
