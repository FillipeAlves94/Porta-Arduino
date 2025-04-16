// Definições de pinos e notas
#define redLedPin 12
#define greenLedPin 11
#define buzzerPin 10
#define smokePin A5
#define NOTE 1000

int sensorThres = 200;

void setup()
{
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(smokePin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int analogSensor = analogRead(smokePin);
  Serial.print("Valor do sensor: ");
  Serial.println(analogSensor);

  if (analogSensor > sensorThres)
  {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    alertaSonoro();
  }
  else
  {
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
  }

  delay(100);
}

// Função Alerta

void alertaSonoro()
{
  for (int i = 0; i < 6; i++)
  {
    tone(buzzerPin, NOTE);
    delay(100);
    noTone(buzzerPin);
    delay(200);
  }
}
