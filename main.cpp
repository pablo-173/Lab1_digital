#include <Arduino.h>
#include <driver/gpio.h>
#include <stdio.h>

#define b_1 32
#define b_2 35
#define b_3 34
int s1=0;
int s2=0;
int s3=0;
int l1=0;
int l2=0;
int l3=0;
int stage=0;
int contador_1=0;
int contador_2=0;
int seg=0;
void deca(int valor);
void bina(int valor);
const byte ps[4]={
  5,18,19,21
};
byte dec[5][4]={
  {0,0,0,0},
  {0,0,0,1},
  {0,0,1,0},
  {0,1,0,0},
  {1,0,0,0}
};

byte bin[16][4]={
  {0,0,0,0},
  {0,0,0,1},
  {0,0,1,0},
  {0,0,1,1},
  {0,1,0,0},
  {0,1,0,1},
  {0,1,1,0},
  {0,1,1,1},
  {1,0,0,0},
  {1,0,0,1},
  {1,0,1,0},
  {1,0,1,1},
  {1,1,0,0},
  {1,1,0,1},
  {1,1,1,0},
  {1,1,1,1}
};


void setup() {
  pinMode(b_1,INPUT_PULLDOWN);
  pinMode(b_2,INPUT);
  pinMode(b_3,INPUT);
  for( int i=0; i<4;i++){
    pinMode(ps[i],OUTPUT);
  }

}

void loop() {
  l1=digitalRead(b_1);
  l2=digitalRead(b_2);
  l3=digitalRead(b_3); 
  if (l1==HIGH) {
    s1=1;
  }
  if (s1==1 && l1==LOW){
    delay(10);
    stage++;
    if (stage>2){
      stage=1;
    }
s1=0;
  }
  if (stage==1){
    contador_2=0;
    if (l2==LOW){
      s2=1;
    }
    if (s2==1 && l2==HIGH){
      delay(10);
      contador_1++;
      s2=0;
      if (contador_1>4){
        contador_1=0;
      }

    }
    deca(contador_1);
  }
  else if (stage==2){
    contador_1=0;
    if (l3==HIGH){
      s3=1;
    }
    if (s3==1 && l3==LOW){
      delay(10);
      contador_2++;
      s3=0;
    
      if(contador_2>15){
        contador_2=0;
      }
    }
    else if (l2==LOW){
      s2=1;
    }
    if (s2==1 && l2==HIGH){
      delay(10);
      contador_2--;
      s2=0;
      if(contador_2<0){
        contador_2=15;
      }

    }
    
    bina(contador_2);
  }
}
void deca(int valor){
  for (seg=0;seg<4;seg++){
    digitalWrite(ps[seg],dec[valor][seg]);
  }
}
void bina (int valor){
  for (seg=0;seg<4;seg++){
    digitalWrite(ps[seg],bin[valor][seg]);
  }
}

