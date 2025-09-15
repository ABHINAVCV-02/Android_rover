#include <SoftwareSerial.h>

// Motor & LED pins
#define led1 13
#define in1 12
#define in2 11
#define in3 10
#define in4 9

// Bluetooth Serial pins
#define RX_PIN 4
#define TX_PIN 5

// MQ135 sensor pin
#define MQ135_PIN A1   // Analog pin for sensor

// Create SoftwareSerial object
SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX = 4, TX = 5

void setup() {
  mySerial.begin(9600);   // Start Bluetooth
  Serial.begin(9600);     // Debugging via USB

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(led1, OUTPUT);
}

void loop() {
  // 1. Read MQ135 sensor value
  int airQuality = analogRead(MQ135_PIN);
  Serial.print("MQ135 Value: ");
  Serial.println(airQuality);
  mySerial.print("MQ135:");
  mySerial.println(airQuality);

  // 2. Check for Bluetooth commands
  if (mySerial.available() > 0) {
    char inputvalue = char(mySerial.read());
    Serial.print("Received: ");
    Serial.println(inputvalue);

    if (inputvalue == 'F') {          // Forward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    else if (inputvalue == 'B') {     // Backward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }
    else if (inputvalue == 'R') {     // Right
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    else if (inputvalue == 'L') {     // Left
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
    else if (inputvalue == 'O') {     // LED ON
      digitalWrite(led1, HIGH);
    }
    else if (inputvalue == 's') {     // LED OFF
      digitalWrite(led1, LOW);
    }
    else if (inputvalue == 'S') {     // Stop motors
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
  }

  delay(500); // small delay so sensor values don’t spam too fast
}
