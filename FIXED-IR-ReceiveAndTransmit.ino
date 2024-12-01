#include <IRremote.h>

// Nastavenie pinov pre prijímač a vysielač
#define IR_RECEIVE_PIN 11  // Pin pre IR prijímač
#define IR_SEND_PIN 3      // Pin pre IR LED

// Vytvorenie objektov pre prijímač a vysielač
IRrecv IrReceiver(IR_RECEIVE_PIN);
IRsend IrSender;
decode_results results;

void setup() {
  Serial.begin(9600);

  // Inicializácia IR prijímača
  IrReceiver.enableIRIn(); // Aktivuje prijímanie IR signálu
  Serial.println("IR prijímač inicializovaný. Čakám na signály...");

  // Nie je potrebné explicitne inicializovať vysielač pre verziu 2.x
  Serial.println("IR vysielač pripravený.");
}

void loop() {
  if (IrReceiver.decode(&results)) { // Ak bol prijatý signál
    Serial.println("IR signál prijatý!");

    // Vypíše detekovaný protokol
    Serial.print("Protokol: ");
    switch (results.decode_type) {
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

    // Vypíše prijatý IR kód v HEX formáte
    Serial.print("Kód: 0x");
    Serial.println(results.value, HEX);

    // Vypíše počet bitov
    Serial.print("Počet bitov: ");
    Serial.println(results.bits);

    for (int i =0; i < 77; i++) {
      Serial.println("Odosielam prijatý kód...");
      IrSender.sendNEC(results.value, results.bits);

      Serial.println("Kód bol odoslaný.");
      Serial.println("----------------------");
      delay(1000);
      // Pripraví prijímač na prijatie ďalšieho signálu
      IrReceiver.resume();
      delay(1000);
    }
  }
}
