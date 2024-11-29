#include <IRremote.h>

const int irLedPin = 4;  // Transmit IR LED Pin
IRsend irsend;


unsigned long irCodes[] = {
  0x1FE48B7, // TV Button or else ...
  0x1FE58A7, // Power ON/OFF or else ...
  0x1FE7887  // --- ! ADD HERE MORE CODES ! ---
};

int numCodes = sizeof(irCodes) / sizeof(irCodes[0]);  // Počet kódov v poli

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < numCodes; i++) {
    irsend.sendNEC(irCodes[i], 32);  // NEC formát
    Serial.print("Odosielam kód: ");
    Serial.println(irCodes[i], HEX);  // Vytlačíme odosielaný kód v hex formáte
    delay(1000);  // Čakáme 1 sekundu pred odoslaním ďalšieho kódu
  }
}
