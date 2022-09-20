int LEDS[] = {2, 3, 4, 5};
int NB_LEDS = 4;
int currentLed = 0;

byte sensorPin = A5;
byte buttonPin = 6;

byte lastButtonState = LOW;
byte doAnimation = LOW;

unsigned long toggledTime = 0;

void ledAnimation(int time) {
  unsigned long timeElapsedSinceLastToggle = millis() - toggledTime;

  digitalWrite(LEDS[currentLed], HIGH);
  if (timeElapsedSinceLastToggle >= time) {
    digitalWrite(LEDS[currentLed], LOW);
    toggledTime = millis();
    currentLed += 1;
  }

  if (currentLed >= NB_LEDS) {
    currentLed = 0;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  for (int i = 0; i < NB_LEDS; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
}

void loop() {
  int sensorValue = 0;
  int timeValue = 0;
  int buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
    if (buttonState == LOW) {
      doAnimation = (doAnimation == HIGH) ? LOW: HIGH;
    }
  }
  if (doAnimation == HIGH) {
    sensorValue = analogRead(sensorPin);
    timeValue = map(sensorValue, 0, 1023, 50, 1000);
    ledAnimation(timeValue);
  }
  delay(1);
}
