// Definições de pinos e notas
#define buzzerPin 13       // D13 Pino Arduino Digital

// LEDs de Alerta
#define yellowLedPin_A 12     // D12 Pino Arduino Digital
#define yellowLedPin_B 11     // D11 Pino Arduino Digital

// LEDs de Guia
#define redLedPin_A 10  // D10 Pino Arduino Digital
#define redLedPin_B 9   // D9 Pino Arduino Digital
#define redLedPin_C 8   // D8 Pino Arduino Digital
#define redLedPin_D 7   // D7 Pino Arduino Digital
#define redLedPin_E 6   // D6 Pino Arduino Digital


#define smokePin A5        // A5 Pino Arduino Analogico
#define buttonPin A0       // A0 Pino Arduino Analogico
#define NOTE 1000          //  1000 Hz

// Variáveis globais
int sensorThres = 200;
bool alarmeAtivo = false;

void setup() {
  
  pinMode(yellowLedPin_A, OUTPUT);
  pinMode(yellowLedPin_B, OUTPUT);

  // Led de Guia
  pinMode(redLedPin_A, OUTPUT);
  pinMode(redLedPin_B, OUTPUT);
  pinMode(redLedPin_C, OUTPUT);
  pinMode(redLedPin_D, OUTPUT);
  pinMode(redLedPin_E, OUTPUT);

  pinMode(buzzerPin, OUTPUT);
  
  pinMode(smokePin, INPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokePin); 
  int buttonState = digitalRead(buttonPin);

  Serial.print("Valor do sensor: ");
  Serial.println(analogSensor);

  // Quando o Sensor Detectar 900
  if (analogSensor >= sensorThres && !alarmeAtivo) {
    alarmeAtivo = true;
  }

  // Função pra Desativar o Alerta - Botão
  if (buttonState == HIGH) {
    alarmeAtivo = false;

    digitalWrite(yellowLedPin_A, LOW);
    digitalWrite(yellowLedPin_B, LOW); 

    digitalWrite(redLedPin_A, LOW);
    digitalWrite(redLedPin_B, LOW);
    digitalWrite(redLedPin_C, LOW);
    digitalWrite(redLedPin_D, LOW);
    digitalWrite(redLedPin_E, LOW);

    noTone(buzzerPin);
  }

  // Ativar o Alarme
  if (alarmeAtivo) {
    digitalWrite(yellowLedPin_A, HIGH);
    digitalWrite(yellowLedPin_B, HIGH);

    tone(buzzerPin, NOTE);

    digitalWrite(redLedPin_A, HIGH);
    digitalWrite(redLedPin_B, HIGH);
    digitalWrite(redLedPin_C, HIGH);
    digitalWrite(redLedPin_D, HIGH);
    digitalWrite(redLedPin_E, HIGH);

    delay(150);

    noTone(buzzerPin);

    digitalWrite(redLedPin_A, LOW);
    digitalWrite(redLedPin_B, LOW);
    digitalWrite(redLedPin_C, LOW);
    digitalWrite(redLedPin_D, LOW);
    digitalWrite(redLedPin_E, LOW);

    delay(150);

  // Função pra Desativar o Alerta
  } else {
    digitalWrite(yellowLedPin_A, LOW);
    digitalWrite(yellowLedPin_B, LOW);

    digitalWrite(redLedPin_A, LOW);
    digitalWrite(redLedPin_B, LOW);
    digitalWrite(redLedPin_C, LOW);
    digitalWrite(redLedPin_D, LOW);
    digitalWrite(redLedPin_E, LOW);

    noTone(buzzerPin);

    delay(100);
    }
}