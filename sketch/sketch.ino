#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define TRIG_PIN A3   // Pino TRIG conectado ao A3
#define ECHO_PIN A4   // Pino ECHO conectado ao A4
#define SERVO_PIN 7   // Pino do servo motor

#define NOTE_1  350  // Nota de som para acesso
#define NOTE_2  200  // Nota de som para erro
int BUZZER_PIN = 13;  // Pino do buzzer

long tempoOpen = 0;
long timeDistance10cm = 0;
bool statesOpen = false;

Servo portaServo;
LiquidCrystal lcd(12, 11, 10, 9, 8, 6);

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
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  portaServo.attach(SERVO_PIN);
  portaServo.write(0);

  lcd.begin(16, 2);
  lcd.print("Digite a senha:");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {  // Confirmação da senha
      if (senhaDigitada == senhaCorreta) {
        lcd.clear();
        lcd.print("Acesso Liberado");
        tocarNotaRepetida();
        portaServo.write(90);
        statesOpen = true;
        tempoOpen = millis();
      } else {
        lcd.clear();
        lcd.print("Senha Errada!");
        tocarNotaRepetidaErrada();
        delay(2000);
        lcd.clear();
        lcd.print("Digite a senha:");
      }
      senhaDigitada = "";
    } else if (key == '*') {
      senhaDigitada = "";
      lcd.clear();
      lcd.print("Digite a senha:");
    } else {
      senhaDigitada += key;
      lcd.setCursor(senhaDigitada.length() - 1, 1);
      lcd.print('*');
    }
  }

  float distanciaCM = medirDistancia();
  controlarPorta(distanciaCM);
}

float medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);
  return duracao * 0.0344 / 2;
}

void controlarPorta(float distanciaCM) {
  if (distanciaCM <= 10) {
    if (!statesOpen) {
      timeDistance10cm = millis();
    }

    if (millis() - timeDistance10cm >= 5000) {
      if (statesOpen) {
        lcd.clear();
        lcd.print("Porta Fechada!");
        tocarNotaFechado();
        portaServo.write(0);
        statesOpen = false;
        delay(1500);
        lcd.clear();
        lcd.print("Digite a senha:");
      }
    }
  } else {
    timeDistance10cm = 0;
    if (!statesOpen) {
      portaServo.write(90);
      statesOpen = true;
      tempoOpen = millis();
    }
    if (millis() - tempoOpen >= 10000) {
      tocarAlerta();
    }
  }
}

void tocarAlerta() {
  tone(BUZZER_PIN, NOTE_1);
  lcd.clear();
  lcd.print("ALERTA - PORTA ABERTA");
  delay(150);
  noTone(BUZZER_PIN);
  delay(100);
  lcd.clear();
  lcd.print("Digite a senha:");
}

void tocarNotaRepetida() {
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, NOTE_1);
    delay(150);
    noTone(BUZZER_PIN);
    delay(100);
  }
}

void tocarNotaFechado(){
    tone(BUZZER_PIN, NOTE_2);
    delay(150);
    noTone(BUZZER_PIN);
    delay(100);
}

void tocarNotaRepetidaErrada() {
  for (int i = 0; i < 2; i++) {
    tone(BUZZER_PIN, NOTE_2);
    delay(150);
    noTone(BUZZER_PIN);
    delay(100);
  }
}