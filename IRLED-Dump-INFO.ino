#include <IRremote.h>

// Nastavenie signálového pinu
const int IR_RECEIVE_PIN = 11;

void setup() {
  Serial.begin(9600);
  // Inicializácia IR prijímača
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR prijímač inicializovaný. Čakám na signály...");
}

void loop() {
  // Ak bol prijatý IR signál
  if (IrReceiver.decode()) {
    Serial.println("IR signál prijatý!");
    
    // Vypíše typ protokolu
    Serial.print("Protokol: ");
    switch (IrReceiver.decodedIRData.protocol) {
      case UNKNOWN:
        Serial.println("Neznámy");
        break;
      case NEC:
        Serial.println("NEC");
        break;
      case SONY:
        Serial.println("Sony");
        break;
      case PANASONIC:
        Serial.println("Panasonic");
        break;
      case LG:
        Serial.println("LG");
        break;
      case JVC:
        Serial.println("JVC");
        break;
      case SAMSUNG:
        Serial.println("Samsung");
        break;
      case RC5:
        Serial.println("RC5");
        break;
      case RC6:
        Serial.println("RC6");
        break;
      default:
        Serial.println("Iný alebo neznámy protokol");
        break;
    }

    // Vypíše IR kód (HEX forma)
    Serial.print("Kód: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    // Vypíše počet bitov
    Serial.print("Počet bitov: ");
    Serial.println(IrReceiver.decodedIRData.numberOfBits);

    // Vypíše časť RAW dát (pre detailné analýzy)
    Serial.println("RAW Data:");
    IrReceiver.printIRResultRawFormatted(&Serial);
    
    Serial.println("----------------------");

    // Pripraví prijímač na ďalší signál
    IrReceiver.resume();
  }
}
