#include <IRremote.h>

// Oled Display Connection
// VCC - 5V
// GND - GND
// SCL - A5
// SDA - A4

// Definície pre IR prijímač a vysielač
#define RECV_PIN 11 // Pin, kde je pripojený IR prijímač
#define LED_TX_PIN 3 // Pin, kde je pripojená IR LED dióda (vysielač)

IRrecv irrecv(RECV_PIN); // Vytvorenie objektu pre IR prijímač
IRsend irsend; // Vytvorenie objektu pre IR vysielač
decode_results results; // Objekt pre uloženie výsledkov dekódovania

void setup() {
  Serial.begin(9600); // Inicializácia sériového monitora
  irrecv.enableIRIn(); // Spustenie IR prijímača
  pinMode(LED_TX_PIN, OUTPUT); // Nastavenie LED vysielača ako výstup
  Serial.println("Čakám na IR signál...");
}

void loop() {
  // Kontrola, či bol prijatý IR signál
  if (irrecv.decode(&results)) {
    // Výpis HEX hodnoty prijatého signálu
    Serial.print("HEX kód: 0x");
    Serial.println(results.value, HEX);

    // Výpis binárneho kódu
    Serial.print("BIN kód: ");
    printBinary(results.value);

    // Odoslanie binárneho kódu 2x s 1-sekundovým oneskorením
    Serial.println("Vysielam IR kód...");
    irsend.sendNEC(results.value, 32); // Poslanie kódu (32-bitový NEC protokol)
    delay(1000); // 1 sekunda
    irsend.sendNEC(results.value, 32); // Opätovné poslanie kódu

    // Pripravenie prijímača na ďalší signál
    irrecv.resume();
  }
}

// Funkcia na výpis binárneho kódu
void printBinary(unsigned long value) {
  for (int i = 31; i >= 0; i--) { // Prechádza všetkých 32 bitov
    if (value & (1UL << i)) { // Skontroluje, či je bit nastavený
      Serial.print("1");
    } else {
      Serial.print("0");
    }
  }
  Serial.println(); // Nový riadok na konci
}
