//ESP 8266 PIN OUTS
#define D0 16
#define D1 5 // I2C Bus SCL (clock)
#define D2 4 // I2C Bus SDA (data)
#define D3 0
#define D4 2 // Same as "LED_BUILTIN", but inverted logic
#define D5 14 // SPI Bus SCK (clock)
#define D6 12 // SPI Bus MISO
#define D7 13 // SPI Bus MOSI
#define D8 15 // SPI Bus SS (CS)
#define D9 3 // RX0 (Serial console)
#define D10 1 // TX0 (Serial console)

int baseline = 0;
int baseline_min = 0;
int baseline_max = 0;

void setup() {
  pinMode(INPUT, A0);
  Serial.begin(9600);
  delay(2000);
  calibrate();
  Serial.println("passed calibration");
}

void loop() {
  Serial.print(getCurrent());
  Serial.println(" mA");
  delay(2000);
}

void calibrate() {
  long current_time = millis();
  int baseline_min = 1024;
  int baseline_max = 0;
  int value = 0;
  while (millis() < current_time + 17) {
    do {
      value = analogRead(A0);
    } while (value < 24 || value > 1000);

    if (value < baseline_min)
      baseline_min = value;
    if (value > baseline_max)
      baseline_max = value;
  }

  baseline = (baseline_min + baseline_max) / 2;
  Serial.println("________baseline values_______");
  Serial.println(baseline_min);
  Serial.println(baseline_max);
  Serial.println(baseline);
  Serial.println("\n\n");
}

int getCurrent() {
  long current_time = millis();
  int current = 0;
  int current_min = 1024;
  int current_max = 0;
  int value = 0;
  while (millis() < current_time + 17) {
    do {
      value = analogRead(A0);
    } while (value < 24 || value > 1000);

    if (value < current_min)
      current_min = value;
    if (value > current_max)
      current_max = value;
  }

  current = (current_min + current_max) / 2;

  Serial.println("________current values_______");
  Serial.println(current_min);
  Serial.println(current_max);
  Serial.println(current);
  Serial.println("\n\n");

  return baseline - current_min;
}

