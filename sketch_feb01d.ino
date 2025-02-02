#define TRIG_PIN 23  // GPIO pin for the TRIG pin
#define ECHO_PIN 22  // GPIO pin for the ECHO pin

void setup() {+
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);  // Set TRIG pin as output
  pinMode(ECHO_PIN, INPUT);   // Set ECHO pin as input
}

void loop() {
  // Clear the TRIG pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond pulse to TRIG to start measurement
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the duration of the pulse from the ECHO pin
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in centimeters (speed of sound = 0.0343 cm/us)
  float distance = (duration * 0.0343) / 2;  // Divide by 2 because the pulse travels to the object and back

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);  // Wait for 1 second before measuring again
}
