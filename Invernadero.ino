/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#include "Conection.h"
#include "AsyncTaskLib.h"
#include "Sensores.h"
// Wifi network station credentials
#define DEBUG(a) \
  Serial.print(millis()); \
  Serial.print(": "); \
  Serial.println(a);

/*
  @ Medimos la temperatura cado 3 minutos = 180000 milisecunds.
  @ Medimos la luz cada 2 sgundos.
*/
AsyncTask asyncTaskTemp(180000, true, readTemp);
AsyncTask asyncTaskLight(2000, true, readLight);
AsyncTask asyncTaskHumeFloor(60000, true, readHumeFloor);



void setup() {
  ConectionWifi();
  asyncTaskTemp.Start();
  asyncTaskLight.Start();
  asyncTaskHumeFloor.Start();
}

void loop() {
  asyncTaskLight.Update();
  asyncTaskTemp.Update();
  asyncTaskHumeFloor.Update();
  ifTelegramLoop ();
}
