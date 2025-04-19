// Bibioteca
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

// Definições de pinos e notas
#define greenLedPin 10 // D10 Pino Arduino Digital
#define redLedPin 11   // D11 Pino Arduino Digital
#define buzzerPin 12   // D12 Pino Arduino Digital

#define NOTE_1 1000 // 1000 Hz
#define NOTE_2 400  //  400 Hz

// Variáveis globais de tempo
int horas, minutos, segundos;
int abrePorta = 90;      // posição 90º - Aberto
int fechaPorta = 0;      // posição  0º - Fechado
int duracaoAbreto = 6000 // Duração da Porta Aberta - 6s

    // Senha
    String senhaCorreta = "0000";
String senhaDigitada = "";

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD I2C

// Configuração do Keypad
const byte LINHAS = 4;
const byte COLUNAS = 3;
char KEYS[LINHAS][COLUNAS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

byte pino_linha[LINHAS] = {8, 7, 6, 5}; // D8 - D7 - D6 - D5 (Pino Arduino Digital)
byte pino_coluna[COLUNAS] = {4, 3, 2};  // D4 - D3 - D2 (Pino Arduino Digital)

Keypad keypad = Keypad(makeKeymap(KEYS), pino_linha, pino_coluna, LINHAS, COLUNAS); // A4 - A5 (Pino Arduino Analógica)

Servo servo_9; // D9 (Pino Arduino Pino Digital)

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Digite a senha:");
  lcd.setCursor(0, 1);

  servo_9.attach(9);
  servo_9.write(fechaPorta);

  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
}

void loop()
{
  char key = keypad.getKey();

  // Atualiza o tempo atual
  unsigned long tempo = millis();
  horas = (tempo / 3600000) % 24;
  minutos = (tempo / 60000) % 60;
  segundos = (tempo / 1000) % 60;

  if (key)
  {
    // Acesso Liberado
    if (key == '#')
    {
      if (senhaDigitada == senhaCorreta)
      {
        lcd.clear();
        lcd.print("Acesso Liberado");
        alertaAcerto();
        logLiberado();
        delay(500);
      }
      // Acesso Negado
      else
      {
        lcd.clear();
        lcd.print("Senha Errada!");
        alertaError();
        logNegado();
        delay(3000);
      }
      // Resetar Tela
      senhaDigitada = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Digite a senha:");
      lcd.setCursor(0, 1);
    }
    // Resetar Tela
    else if (key == '*')
    {
      senhaDigitada = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Digite a senha:");
      lcd.setCursor(0, 1);
    }
    else
    {
      senhaDigitada += key; // Entrada dos Digitos
      lcd.setCursor(senhaDigitada.length() - 1, 1);
      lcd.print("*");
    }
  }
}

// Buzzer Acerto
void alertaAcerto()
{
  for (int i = 0; i < 3; i++)
  {
    tone(buzzerPin, NOTE_1);
    digitalWrite(greenLedPin, HIGH);
    delay(200);
    digitalWrite(greenLedPin, LOW);
    noTone(buzzerPin);
    delay(100);
  }

  servo_9.write(abrePorta);
  delay(duracaoAbreto);
  servo_9.write(fechaPorta); // A porta irá durar deacordo com a Variavel "duracaoAbreto"
}

// Buzzer Errado
void alertaError()
{
  for (int i = 0; i < 2; i++)
  {
    tone(buzzerPin, NOTE_2);
    digitalWrite(redLedPin, HIGH);
    delay(200);
    digitalWrite(redLedPin, LOW);
    noTone(buzzerPin);
    delay(200);
  }
}

// Enviar hora para o Python - Acesso Liberado
void logLiberado()
{
  Serial.print("Acesso Liberado às: ");
  Serial.print(horas);
  Serial.print(":");
  Serial.print(minutos);
  Serial.print(":");
  Serial.println(segundos);
}

// Enviar hora para o Python - Acesso Negado
void logNegado()
{
  Serial.print("Acesso Negado às: ");
  Serial.print(horas);
  Serial.print(":");
  Serial.print(minutos);
  Serial.print(":");
  Serial.println(segundos);
}
