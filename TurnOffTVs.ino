#include <IRremote.h>

// Definovanie IR vysielacieho pinu
const int IR_PIN = 3;

// IR kódy pre vypnutie televízorov
// Samsung (HEX: E0E040BF)
const unsigned long SAMSUNG_OFF = 0xE0E040BF; 

// Panasonic (HEX: 40040100)
const unsigned long PANASONIC_OFF = 0x40040100;

// Sony (HEX: A90) - Sony používa protokol NEC, 12-bitový
const unsigned long SONY_OFF = 0xA90; 

// Delay medzi jednotlivými kódmi (30 ms)
const int DELAY_MS = 30;

IRsend irsend;

void setup() {
  // Inicializácia IR vysielača
  IrSender.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  // Odoslanie Samsung vypínacieho kódu (32-bitový)
  irsend.sendSamsung(SAMSUNG_OFF, 32);
  delay(DELAY_MS);

  // Odoslanie Panasonic vypínacieho kódu (32-bitový)
  irsend.sendPanasonic(0x4004, PANASONIC_OFF);
  delay(DELAY_MS);

  // Odoslanie Sony vypínacieho kódu (12-bitový)
  irsend.sendSony(SONY_OFF, 12);
  delay(DELAY_MS);

  // Opakovanie cyklu
}