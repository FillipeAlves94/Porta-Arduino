#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define SERVO_PIN 7   // Pino que controla o servo motor
#define TRIG_PIN A3   // Pino TRIG conectado ao pino analogico A3
#define ECHO_PIN A4   // Pino ECHO conectado ao pino analogico A4

#define NOTE_1  350  // Definindo a nota musical (em Hz)
#define NOTE_2  200  // Definindo a nota musical (em Hz)
int BUZZER_PIN = 13;  // Buzzer conectado ao pino 13

Servo portaServo;

// Configuração do LCD (modo paralelo)
LiquidCrystal lcd(12, 11, 10, 9, 8, 6);

// Configuração do teclado matricial
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {A2, A1, A0};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String senhaCorreta = "0000";
String senhaDigitada = "";

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);

  portaServo.attach(SERVO_PIN);
  portaServo.write(0);  // Porta começa fechada (posição 0°)

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
        tocarNotaRepetida();
        portaServo.write(90); // Abre a porta (posição 90°)
        delay(2000);           // Aguarda 2 segundos
        portaServo.write(0);  // Fecha a porta (posição 0°)

        lcd.clear();
        lcd.print("Digite a senha:");
      } else {
        lcd.clear();
        lcd.print("Senha Errada!");
        tocarNotaRepetidaErrada();
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
      lcd.print('*');  // Exibe '*' no lugar dos números
    }
  }
}


void tocarNotaRepetida() {
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, NOTE_1);  // Emite a nota C4
    delay(150);                  // Aguarda 150 ms (duração curta)
    noTone(BUZZER_PIN);         // Desliga o som da nota
    delay(100);                  // Pequeno intervalo entre as repetições
  }
}

void tocarNotaRepetidaErrada() {
  for (int i = 0; i < 2; i++) {
    tone(BUZZER_PIN, NOTE_2);  // Emite a nota C4
    delay(150);                // Aguarda 200 ms (duração curta)
    noTone(BUZZER_PIN);         // Desliga o som da nota
    delay(100);                // Pequeno intervalo entre as repetições
  }
}