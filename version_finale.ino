#define BLYNK_AUTH_TOKEN "cLbGIBaHPYJuWNNAgvdR1M83CT2EpTT8"
#define BLYNK_TEMPLATE_ID "TMPL2Ulzunrja"
#define BLYNK_TEMPLATE_NAME "systeme arrosage"

#include <DHT.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial

char ssid[] = "HUAWEI-2.4G-hC29";
char pass[] = "yaxWc9pG";

// Brochage
const int relayPin = 2;
const int led1Pin = 12;
const int led2Pin = 13;
const int trigPin = 5;
const int echoPin = 18;
const int solPin = 32;

#define DHTPIN 4
#define DHTTYPE DHT11
#define SOUND_SPEED 0.034

DHT dht(DHTPIN, DHTTYPE);

// Seuils et variables
int dryValue = 3000;
int wetValue = 1000;
int modeArrosage = 0;
int relaisEtat = 0;

float distanceCm, airHumidity, temperature;
int soilHumidity;

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(solPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  digitalWrite(relayPin, LOW);
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, LOW);

  Blynk.virtualWrite(V11, 0);
  Blynk.virtualWrite(V9, 1);
  Blynk.virtualWrite(V10, 0);
}

// ----- GESTION DES MODES -----
BLYNK_WRITE(V4) {
  modeArrosage = param.asInt();
  Serial.print("Mode d'arrosage : ");
  Serial.println(modeArrosage == 1 ? "Automatique" : "Manuel");
}

BLYNK_WRITE(V1) {
  relaisEtat = param.asInt();
  Serial.print("Valeur reçue de V1 : ");
  Serial.println(relaisEtat);
}

// ----- MESURES DES CAPTEURS -----
void lireCapteurs() {
  int solValue = analogRead(solPin);
  soilHumidity = map(solValue, wetValue, dryValue, 100, 0);
  soilHumidity = constrain(soilHumidity, 0, 100);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;

  airHumidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(airHumidity) || isnan(temperature)) {
    Serial.println("Erreur capteur DHT.");
    airHumidity = 0;
    temperature = 0;
  }

  Serial.print("Humidité sol : ");
  Serial.print(soilHumidity);
  Serial.print("% | Température : ");
  Serial.print(temperature);
  Serial.print("°C | Humidité air : ");
  Serial.print(airHumidity);
  Serial.print("% | Niveau d'eau : ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  Blynk.virtualWrite(V0, soilHumidity);
  Blynk.virtualWrite(V6, temperature);
  Blynk.virtualWrite(V7, distanceCm);
  Blynk.virtualWrite(V5, airHumidity);
}

// ----- MODE MANUEL -----
void gererModeManuel() {
  if (modeArrosage == 0 && distanceCm < 25) {
    if (relaisEtat == 1) {
      digitalWrite(relayPin, HIGH);
      digitalWrite(led2Pin, HIGH);
      Blynk.virtualWrite(V10, 1);
      Blynk.virtualWrite(V9, 0);
    } else {
      digitalWrite(relayPin, LOW);
      digitalWrite(led2Pin, LOW);
      Blynk.virtualWrite(V10, 0);
      Blynk.virtualWrite(V9, 1);
    }
  } else {
    // si niveau d’eau trop bas
    digitalWrite(relayPin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led1Pin, HIGH);
    Blynk.virtualWrite(V10, 0);
    Blynk.virtualWrite(V9, 1);
  }
}

// ----- MODE AUTOMATIQUE -----
void gererModeAutomatique() {
  bool arrosage = false;
  int delai = 0;

  if (soilHumidity < 60 && temperature < 30 && airHumidity < 40 && distanceCm < 15) {
    arrosage = true;
    delai = 1000;
    Serial.println("Arrosage rapide.");
  } else if (soilHumidity < 60 && distanceCm < 25) {
    arrosage = true;
    delai = 5000;
    Serial.println("Arrosage normal.");
  } else {
    Serial.println("Pas d'arrosage.");
  }

  if (arrosage) {
    digitalWrite(relayPin, HIGH);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led1Pin, LOW);
    Blynk.virtualWrite(V11, 1);
    Blynk.virtualWrite(V10, 1);
    Blynk.virtualWrite(V9, 0);
    delay(delai);
  } else {
    digitalWrite(relayPin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led1Pin, HIGH);
    Blynk.virtualWrite(V11, 0);
    Blynk.virtualWrite(V10, 0);
    Blynk.virtualWrite(V9, 1);
  }
}

// ----- LOOP PRINCIPALE -----
void loop() {
  Blynk.run();
  lireCapteurs();

  if (modeArrosage == 0) {
    gererModeManuel();
  } else {
    gererModeAutomatique();
  }

  Serial.println("--------------");
  delay(1000);
}
