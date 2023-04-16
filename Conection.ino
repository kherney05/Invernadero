#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>



#include "DHT.h"
#include <math.h>

// Wifi network station credentials
#define WIFI_SSID "Milagros_Rangel_5G"
#define WIFI_PASSWORD "milagros14"


// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "5894039918:AAEOr-rNYwHBe5_ryyRM0H1yzUuUrqRoF48"

const unsigned long BOT_MTBS = 1000;  // mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;  // last time messages' scan has been done


void ConectionWifi() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Add root certificate for api.telegram.org

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org");  // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

void handleNewMessages(int numNewMessages) {
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    /*
    if (text == "/ledoff") {
      digitalWrite(ledPin, LOW);  // turn the LED on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led is OFF", "");
    }

    if (text == "/ledon") {
      ledStatus = 0;
      digitalWrite(ledPin, HIGH);  // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led is ON", "");
    }

    if (text == "/status") {
      if (ledStatus) {
        bot.sendMessage(chat_id, "Led is ON", "");
      } else {
        bot.sendMessage(chat_id, "Led is OFF", "");
      }
    }
    */

    if (text == "/temp") {
      temp = dht.readTemperature();
      round(temp);
      char cadenaTemp[50];
      sprintf(cadenaTemp, "La temperatura es de: %0.2f°C", temp);
      bot.sendMessage(chat_id, cadenaTemp);
    }

    if (text == "/hume") {
      hume = dht.readHumidity();
      round(hume);
      char cadenaHume[50];
      sprintf(cadenaHume, "La humedad es del: %0.2f", hume);
      bot.sendMessage(chat_id, cadenaHume);
    }

    if (text == "/luz") {
      lightValue = analogRead(lightPin);
      round(lightValue);
      char cadenaLuz[50];
      sprintf(cadenaLuz, "La luz es de: %0.2f", lightValue);
      bot.sendMessage(chat_id, cadenaLuz);
    }

    if (text == "/humesuelo") {
      humeFloor = analogRead(humeFloorPin);
      round(humeFloor);
      char cadenaHumeFloor[50];
      sprintf(cadenaHumeFloor, "La humedad del suelo es de: %0.2f", humeFloor);
      bot.sendMessage(chat_id, cadenaHumeFloor);
    }

    if (text == "/info") {
      //temperature
      temp = dht.readTemperature();
      round(temp);
      char cadenaTemp[50];
      sprintf(cadenaTemp, "La temperatura es de: %0.2f°C", temp);
      bot.sendMessage(chat_id, cadenaTemp);

      //humidity
      hume = dht.readHumidity();
      round(hume);
      char cadenaHume[50];
      sprintf(cadenaHume, "La humedad es del: %0.2f", hume);
      bot.sendMessage(chat_id, cadenaHume);

      //ligth
      lightValue = analogRead(lightPin);
      round(lightValue);
      char cadenaLuz[50];
      sprintf(cadenaLuz, "La luz es de: %0.2f", lightValue);
      bot.sendMessage(chat_id, cadenaLuz);
      
      //humeFloor
      humeFloor = analogRead(humeFloorPin);
      round(humeFloor);
      char cadenaHumeFloor[50];
      sprintf(cadenaHumeFloor, "La humedad del suelo es de: %0.2f", humeFloor);
      bot.sendMessage(chat_id, cadenaHumeFloor);
    }

    if (text == "/start") {
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Flash Led Bot example.\n\n";
      welcome += "/ledon : to switch the Led ON\n";
      welcome += "/ledoff : to switch the Led OFF\n";
      welcome += "/temp : to switch the Led OFF\n";
      welcome += "/hume : to switch the Led OFF\n";
      welcome += "/luz : to switch the Led OFF\n";
      welcome += "/humesuelo : to switch the Led OFF\n";
      welcome += "/info : to switch the Led OFF\n";
      welcome += "/status : Returns current status of LED\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}

void ifTelegramLoop() {

  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
