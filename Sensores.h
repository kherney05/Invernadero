#ifndef _Sensores_h_
#define _Sensores_h_

#include "DHT.h"

#define DHTPIN 14 //leemos la temperatura y la humedad a travez del pin 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

extern const int lightPin = 34;
extern const int humeFloorPin = 12;

extern int lightValue = 0;
extern int humeFloor = 0;
extern float hume = 0;
extern float temp = 0;


void readLight(void);
void readHumeFloor(void);
void readTemp(void);

#endif