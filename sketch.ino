#include <Keypad.h>
#include <LiquidCrystal.h>

#define RELAY_PIN 7  // Pino que controla o relé
#define LED_PIN 13   // Pino do LED externo

// Configuração do LCD (modo paralelo)
LiquidCrystal lcd(12, 11, 10, 9, 8, 6);

// Configuração do teclado matricial
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {A3, A2, A1, A0};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String senhaCorreta = "1234";
String senhaDigitada = "";

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Relé começa desligado
  digitalWrite(LED_PIN, LOW);   // LED começa apagado

  lcd.begin(16, 2);
  lcd.print("Digite a senha:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {  // Confirmar senha
      if (senhaDigitada == senhaCorreta) {
        lcd.clear();
        lcd.print("Acesso Liberado");
        digitalWrite(RELAY_PIN, HIGH); // Ativa o relé
        digitalWrite(LED_PIN, HIGH);   // Acende o LED
        delay(5000);                   // Mantém a trava aberta por 5s
        digitalWrite(RELAY_PIN, LOW);  // Desativa o relé
        digitalWrite(LED_PIN, LOW);    // Apaga o LED
        lcd.clear();
        lcd.print("Digite a senha:");
      } else {
        lcd.clear();
        lcd.print("Senha Errada!");
        delay(2000);
        lcd.clear();
        lcd.print("Digite a senha:");
      }
      senhaDigitada = "";  // Limpa a senha digitada
    } else if (key == '*') {
      senhaDigitada = "";  // Apagar senha
      lcd.clear();
      lcd.print("Digite a senha:");
    } else {
      senhaDigitada += key;
      lcd.setCursor(senhaDigitada.length() - 1, 1);
      lcd.print('*'); // Mostra "*" no lugar dos números
    }
  }
}

